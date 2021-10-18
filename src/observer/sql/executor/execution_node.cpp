/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/execution_node.h"
#include "storage/common/table.h"
#include "common/log/log.h"

SelectExeNode::SelectExeNode() : table_(nullptr) {
}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC
SelectExeNode::init(Trx *trx, Table *table, TupleSchema &&tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void *)&converter, record_reader);
}

RC AggregationNode::execute(TupleSet &tuple_set) {
    auto result_set = new TupleSet();
    auto result_schema = new TupleSchema();
    std::string field_name;
    Tuple res;
    int max_index, min_index;
    int count = 0;
    auto attr_index = tuple_schema_.index_of_field(table_name_.c_str(), attr_name_.c_str());
    auto attr_type = tuple_schema_.field(attr_index).type();
    switch (type_) {
        case AGG_T::AGG_COUNT:
            field_name = "count(" + attr_name_ + ")";
            result_schema->add(AttrType::INTS, "", field_name.c_str());
            count = tuple_set.size();
            result_set->set_schema(*result_schema);
            res = Tuple();
            res.add(count);
            tuple_set.clear();
            tuple_set.set_schema(result_set->get_schema());
            tuple_set.add(std::move(res));
            break;
        case AGG_T::AGG_MAX:
            field_name = "max(" + attr_name_ + ")";
            result_schema->add(attr_type, "", field_name.c_str());
            result_set->set_schema(*result_schema);
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            max_index = 0;
            for (int i = 1; i < tuple_set.tuples().size(); i++) {
                if (tuple_set.tuples().at(i).get(attr_index).compare(tuple_set.tuples().at(max_index).get(attr_index)) > 0) {
                    max_index = i;
                }
            }
            res.add(tuple_set.tuples().at(max_index).get_pointer(attr_index));
            tuple_set.clear();
            tuple_set.set_schema(result_set->get_schema());
            tuple_set.add(std::move(res));
            break;
        case AGG_T::AGG_MIN:
            field_name = "min(" + attr_name_ + ")";
            result_schema->add(attr_type, "", field_name.c_str());
            result_set->set_schema(*result_schema);
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            min_index = 0;
            for (int i = 1; i < tuple_set.tuples().size(); i++) {
                if (tuple_set.tuples().at(i).get(attr_index).compare(tuple_set.tuples().at(min_index).get(attr_index)) < 0) {
                    min_index = i;
                }
            }
            res.add(tuple_set.tuples().at(min_index).get_pointer(attr_index));
            tuple_set.clear();
            tuple_set.set_schema(result_set->get_schema());
            tuple_set.add(std::move(res));
            break;
        case AGG_T::AGG_AVG:
            // only support for int / float
            field_name = "avg(" + attr_name_ + ")";
            result_schema->add(FLOATS, "", field_name.c_str());
            result_set->set_schema(*result_schema);
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            auto *sum_int = new IntValue(0);
            auto *sum_float = new FloatValue(0);
            for (int i = 0; i < tuple_set.tuples().size(); i++) {
                auto tuple = tuple_set.tuples().at(i);
                switch (attr_type) {
                    case INTS:
                        sum_int->sum(tuple.get(attr_index));
                        if (i == tuple_set.tuples().size()-1) {
                            res.add(sum_int);
                        }
                        break;
                    case FLOATS:
                        sum_float->sum(tuple.get(attr_index));
                        if (i == tuple_set.tuples().size()-1) {
                            res.add(sum_float);
                        }
                        break;
                    case UNDEFINED:
                    case CHARS:
                    case DATES:
                        LOG_ERROR("unsupported type");
                        break;
                }
            }
            tuple_set.clear();
            tuple_set.set_schema(result_set->get_schema());
            tuple_set.add(std::move(res));
    }
    return SUCCESS;
}

RC AggregationNode::init(TupleSchema &&tuple_schema, std::string &&table_name, std::string &&attr_name) {
    tuple_schema_ = tuple_schema;
    table_name_ = table_name;
    attr_name_ = attr_name;
    return SUCCESS;
}
