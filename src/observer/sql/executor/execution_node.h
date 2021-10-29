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
// Created by Wangyunlai on 2021/5/13.
//

#ifndef __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
#define __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_

#include <vector>
#include "storage/common/condition_filter.h"
#include "sql/executor/tuple.h"

class Table;
class Trx;

class ExecutionNode {
public:
  ExecutionNode() = default;
  virtual ~ExecutionNode() = default;

  virtual RC execute(TupleSet &tuple_set) = 0;
};

class SelectExeNode : public ExecutionNode {
public:
  SelectExeNode();
  ~SelectExeNode() override;

  RC init(Trx *trx, Table *table, TupleSchema && tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters);

  RC execute(TupleSet &tuple_set) override;

  // debug
  TupleSchema& return_schema() {
    return tuple_schema_;
  }
private:
  Trx *trx_ = nullptr;
  Table  * table_;
  TupleSchema  tuple_schema_;
  std::vector<DefaultConditionFilter *> condition_filters_;
};

class AggregationNode : public ExecutionNode {
public:
    AggregationNode() {
      result_set = new TupleSet;
      result_schema = new TupleSchema;
    }
    ~AggregationNode();

    RC init(TupleSchema && tuple_schema,
                const char *table_name,
                const char *attr_name,
                AGG_T type,
                int need_table_name = 0,
                Value* value = nullptr,
                int need_all = 0
    );

    RC execute(TupleSet &tuple_set) override;
    RC add_field(AttrType type, const char *table_name, const char *field_name);
    void finish();
    void get_result_tuple(TupleSet& tuples);

private:
    int need_table_name_;
    int need_all_;
    TupleValue *value_; /* [TODO] (adlternative) 可能是 之后是 attr_name + value[] 比如 max(id,1,3,4) */
    TupleSchema  tuple_schema_;
    AGG_T type_;
    const char *table_name_;
    const char *attr_name_;

    Tuple tuple;
    TupleSet *result_set;
    TupleSchema *result_schema;
};

class CrossJoinNode : public ExecutionNode {
public:
    CrossJoinNode() : left_child_(nullptr), right_child_(nullptr) {}
    ~CrossJoinNode() override = default;

    RC init(TupleSet *left_child, TupleSet *right_child);

    RC execute(TupleSet &tuple_set) override;
private:
    TupleSet *left_child_;
    TupleSet *right_child_;
};

#endif //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
