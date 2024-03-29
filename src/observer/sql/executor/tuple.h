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

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>

#include "sql/parser/parse.h"
#include "sql/executor/value.h"

class Table;

class Tuple {
public:

  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept ;
  Tuple & operator=(Tuple &&other) noexcept ;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(const char *s, int len);

  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  int size() const {
    return values_.size();
  }

  const TupleValue &get(int index) const {
    return *values_[index];
  }

  void set(int index, TupleValue *value) {
    values_[index] = std::shared_ptr<TupleValue>(value);
  }

  void remove(int index) {
    values_.erase(values_.begin() + index);
  }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

  void print(std::ostream &os) const;
  void debug() const;

private:
  std::vector<std::shared_ptr<TupleValue>>  values_;
};

class TupleField {
public:
  TupleField(AttrType type, const char *table_name, const char *field_name, bool projection) :
          type_(type), table_name_(table_name), field_name_(field_name), is_projection(projection){
          is_agg = false;
  }

  AttrType  type() const{
    return type_;
  }

  const char *table_name() const {
    return table_name_.c_str();
  }
  const char *field_name() const {
    return field_name_.c_str();
  }

  std::string to_string() const;
  void set_projection() {is_projection = true;}
  bool get_projection() const {return is_projection;}
  void set_agg() {is_agg = true;}
  bool get_agg() const {return is_agg;}
private:
  AttrType  type_;
  std::string table_name_;
  std::string field_name_;
  bool is_projection;       // 用于标记哪些列是可以在最后被过滤的
  bool is_agg;
};

class  TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, const char *table_name, const char *field_name);
  void add_projection(AttrType type, const char *table_name, const char *field_name);
  void add_agg(AttrType type, const char *table_name, const char *field_name);
  bool add_if_not_exists(AttrType type, const char *table_name, const char *field_name, bool is_projection);
  void erase_projection();
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const {
    return fields_;
  }

  int size() const { return fields_.size(); }

  const TupleField &field(int index) const {
    return fields_[index];
  }

  RC set_field(int index, const TupleField &field);

  int index_of_field(const char *table_name, const char *field_name) const;
  void clear() {
    fields_.clear();
  }

  void print(std::ostream &os) const;
  void multi_print(std::ostream &os) const;   // 用于多表的输出
public:
  static void from_table(const Table *table, TupleSchema &schema);
private:
  std::vector<TupleField> fields_;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {
  }
  TupleSet &operator =(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);

  const TupleSchema &get_schema() const;

  void add(Tuple && tuple);
  RC add_tupleset(TupleSet&& tuple_set);
  RC add_tupleset_oneline(TupleSet&& tuple_set);

  void clear();

  bool is_empty() const;
  int size() const;
  const Tuple &get(int index) const;
  void remove(int index);
  const std::vector<Tuple> &tuples() const;
  void erase_projection();

  void print(std::ostream &os, bool multi) const;

  void orderBy(const OrderBy* orders, size_t order_num);
  void groupBy(const GroupBy* groups, size_t group_num ,std::vector<TupleSet>& result_tupleset);

  void debug() const;
  void set_text(const char *db);

public:
  const TupleSchema &schema() const {
    return schema_;
  }
private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;
};

class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  void add_record(const char *record);
private:
  Table *table_;
  TupleSet &tuple_set_;
};

using PageNum = int;
void parsing_text(const char *str, PageNum *pnum1, PageNum *pnum2);

#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
