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
    std::string field_name;
    Tuple res;
    int max_index, min_index;
    int count = 0;
    int attr_index;
    AttrType attr_type;

    if (attr_name_!= nullptr && !need_all_) {
      attr_index = tuple_schema_.index_of_field(table_name_.c_str(), attr_name_);
      attr_type  = tuple_schema_.field(attr_index).type();
    }

    switch (type_) {
        case AGG_T::AGG_COUNT: {
            field_name = "count(" + (need_table_name_? table_name_ + "." :"") +
              (attr_name_ ? attr_name_ : value_->to_string().c_str())+ ")";
            LOG_DEBUG("agg count field display {%s}", field_name.c_str());
            result_schema->add(AttrType::INTS, "", field_name.c_str());
            count = tuple_set.size();
            res = Tuple();
            res.add(count);
            tuple.add(res.get_pointer(0));
            break;
        }
        case AGG_T::AGG_MAX: {
            /* assert !need_all */
            field_name = "max(" + (need_table_name_? table_name_ + "." :"") +
              (attr_name_ ? attr_name_ : value_->to_string().c_str())+ ")";
            result_schema->add(attr_type, "", field_name.c_str());
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            if (value_) {
                res.add(value_);
            } else if (need_all_) {
                LOG_ERROR("Unsupported \"*\" for max");
                return INVALID_ARGUMENT;
            } else {
                max_index = 0;
                for (int i = 1; i < tuple_set.tuples().size(); i++) {
                    if (tuple_set.tuples().at(i).get(attr_index).compare(tuple_set.tuples().at(max_index).get(attr_index)) > 0) {
                        max_index = i;
                    }
                }
                res.add(tuple_set.tuples().at(max_index).get_pointer(attr_index));
            }
            tuple.add(res.get_pointer(0));
            break;
        }
        case AGG_T::AGG_MIN: {
            field_name = "min(" + (need_table_name_? table_name_ + "." :"") +
              (attr_name_ ? attr_name_ : value_->to_string().c_str())+ ")";
            result_schema->add(attr_type, "", field_name.c_str());
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            if (value_) {
                res.add(value_);
            } else if (need_all_) {
                LOG_ERROR("Unsupported \"*\" for min");
                return INVALID_ARGUMENT;
            } else {
                min_index = 0;
                LOG_DEBUG("tuple_set.tuples().size() -> {%d}", tuple_set.tuples().size());
                for (int i = 1; i < tuple_set.tuples().size(); i++) {
                    if (tuple_set.tuples().at(i).get(attr_index).compare(tuple_set.tuples().at(min_index).get(attr_index)) < 0) {
                        min_index = i;
                    }
                }
                res.add(tuple_set.tuples().at(min_index).get_pointer(attr_index));
            }
            tuple.add(res.get_pointer(0));
            break;
        }
        case AGG_T::AGG_AVG: {
            // only support for int / float
            field_name = "avg(" + (need_table_name_? table_name_ + "." :"") +
              (attr_name_ ? attr_name_ : value_->to_string().c_str())+ ")";
            result_schema->add(FLOATS, "", field_name.c_str());
            if (tuple_set.is_empty()) {
                tuple_set.clear();
                tuple_set.set_schema(result_set->get_schema());
                break;
            }
            res = Tuple();
            auto *sum = new FloatValue(0);
            if (value_) {
                    res.add(value_);
            } else if (need_all_) {
                delete sum;
                LOG_ERROR("Unsupported \"*\" for avg");
                return INVALID_ARGUMENT;
            } else {
                for (int i = 0; i < tuple_set.tuples().size(); i++) {
                    switch (attr_type) {
                        case INTS:
                            sum->sumInt(tuple_set.tuples().at(i).get(attr_index));
                            if (i == tuple_set.tuples().size()-1) {
                                sum->div(FloatValue(tuple_set.tuples().size()));
                                res.add(sum);
                            }
                            break;
                        case FLOATS:
                            sum->sumFloat(tuple_set.tuples().at(i).get(attr_index));
                            if (i == tuple_set.tuples().size()-1) {
                                sum->div(FloatValue(tuple_set.tuples().size()));
                                res.add(sum);
                            }
                            break;
                        default:
                            LOG_ERROR("unsupported type");
                            delete sum;
                            return INVALID_ARGUMENT;
                    }
                }
            }
            tuple.add(res.get_pointer(0));
            break;
        }
        case AGG_T::AGG_NONE: {
            break;
        }
    }
    return SUCCESS;
}

RC AggregationNode::init(TupleSchema && tuple_schema,
            std::string &&table_name,
            const char *attr_name,
            AGG_T type,
            int need_table_name,
            Value* value,
            int need_all)
{
    tuple_schema_ = tuple_schema;
    table_name_ = table_name;
    attr_name_ = attr_name;
    type_ = type;
    need_table_name_ = need_table_name;
    need_all_ = need_all;
    value_ = ValueToTupleValue(value);

    return SUCCESS;
}

AggregationNode::~AggregationNode() {
    delete result_set;
    delete result_schema;
    delete value_;
}

void AggregationNode::finish() {
    result_set->add(std::move(tuple));
    result_set->set_schema(*result_schema);
}

void AggregationNode::get_result_tuple(TupleSet& tuples) {
    tuples.clear();
    tuples.set_schema(*result_schema);
    for (int i = 0; i < result_set->size(); ++i) {
        tuples.add(const_cast<Tuple &&>(result_set->get(i)));
    }
    return;
}

RC CrossJoinNode::init(TupleSet *left_child, TupleSet *right_child) {
    left_child_ = left_child;
    right_child_ = right_child;
    return SUCCESS;
}

RC CrossJoinNode::execute(TupleSet &tuple_set) {
    auto left_schema = left_child_->get_schema();
    auto right_schema = right_child_->get_schema();
    left_schema.append(right_schema);

    tuple_set.clear();
    tuple_set.set_schema(left_schema);

    for (auto & left_tuple : left_child_->tuples()) {
        for (auto & right_tuple : right_child_->tuples()) {
            Tuple new_tuple = Tuple();
            for (auto & lv : left_tuple.values()) {
                new_tuple.add(lv);
            }
            for (auto & rv : right_tuple.values()) {
                new_tuple.add(rv);
            }
            tuple_set.add(std::move(new_tuple));
        }
    }

    return SUCCESS;
}
