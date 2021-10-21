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
    explicit AggregationNode(AGG_T type) : type_(type) {}
    ~AggregationNode() override = default;

    RC init(TupleSchema && tuple_schema, std::string &&table_name, std::string && attr_name, int need_table_name = 0);

    RC execute(TupleSet &tuple_set) override;
private:
    int need_table_name_;
    TupleSchema  tuple_schema_;
    AGG_T type_;
    std::string table_name_;
    std::string attr_name_;
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
