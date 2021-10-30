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

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include "common/time/datetime.h"
#include <assert.h>
#include <sstream>
#include <algorithm>

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add_if_not_exists(field_meta->type(), table_name, field_meta->name(), false);
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name, false);
}

void TupleSchema::add_projection(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name, true);
}

bool TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name, bool is_projection) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
        return false;
    }
  }
  if (is_projection) {
    add_projection(type, table_name, field_name);
  } else {
    add(type, table_name, field_name);
  }
  return true;
}

void TupleSchema::erase_projection() {
  for (size_t i = 0; i < fields_.size(); i++) {
    if (fields_[i].get_projection()) {
      fields_.erase(fields_.begin() + i);
      i--;
    }
  }
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];

    if (((!table_name) || (0 == strcmp(field.table_name(), table_name)))
      && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

// 暂时不改是为了兼容性
void TupleSchema::print(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // // 判断有多张表还是只有一张表
  // std::set<std::string> table_names;
  // for (const auto &field: fields_) {
  //   table_names.insert(field.table_name());
  // }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    os << iter->field_name() << " | ";
  }

  // if (table_names.size() > 1) {
  //   os << fields_.back().table_name() << ".";
  // }
  os << fields_.back().field_name() << std::endl;
}

/* select test1.in1 from test1,test2 where test2.in2 < 10; */
void TupleSchema::multi_print(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    // 防止多表聚合时出现的额外"."，原因时table_name是空的
    if (static_cast<std::string>(iter->table_name()) != "") {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }
  if (static_cast<std::string>(fields_.back().table_name()) != "") {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool multi) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  if (multi) {
    schema_.multi_print(os);
  } else {
    schema_.print(os);
  }

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (auto iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

RC TupleSet::add_tupleset(TupleSet&& tuple_set) {
  // 此时我们默认他们的fields是一样的
  auto &tuple_set_ = tuple_set.tuples();

  if (schema_.fields().size() == 0) {
    set_schema(tuple_set.get_schema());
  }
  auto len = tuple_set_.size();
  for (int i = 0; i < len; ++i) {
    add(std::move(const_cast<Tuple&&>(tuple_set_[i])));
  }
  return SUCCESS;
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

void TupleSet::remove(int index) {
    tuples_.erase(tuples_.begin()+index);
}

void TupleSet::orderBy(const OrderBy *orders, size_t order_num) {
    std::sort(tuples_.begin(), tuples_.end(),[&](const Tuple& left, const Tuple& right)->bool {
      int ret = 0;
      for (int i = 0; i < order_num; i++) {
        auto attr_index = schema_.index_of_field(orders[i].order_attr.relation_name, orders[i].order_attr.attribute_name);
        if (attr_index == -1) {
          LOG_ERROR("Unexpected %s:%s", orders[i].order_attr.relation_name, orders[i].order_attr.attribute_name);
        }
        LOG_INFO("%s %s",left.get(attr_index).to_string().c_str(),right.get(attr_index).to_string().c_str());
        ret = left.get(attr_index).compare(right.get(attr_index));
        if (ret) {
          if (orders[i].reverse) {
            return ret > 0;
          } else {
            return ret < 0;
          }
        }
      }
      return 0;
    });
}

OrderBy* group2order(const GroupBy* groups, size_t group_num) {
  // 其实做成智能指针更好
  OrderBy *temp_order = new OrderBy[MAX_NUM];
  for (size_t i = 0; i < group_num; i++) {
    temp_order[i].order_attr = groups[i].group_attr;
    temp_order[i].reverse = false;
  }
  return temp_order;
}

void TupleSet::groupBy(const GroupBy* groups, size_t group_num, std::vector<TupleSet>& result_tupleset) {
  if(0 == group_num) {
    // 不需要group_by的时候把自己放到 result_tupleset 去
    result_tupleset.emplace_back(std::move(*this));
    return;
  }
  result_tupleset.clear();

  // step1: 先排序
  OrderBy* order_ = group2order(groups, group_num);
  orderBy(order_, group_num);

  // step2: 然后把我们需要的那N列相同值的放到一个tupleset放到result_tupleset
  int index = 0;
  while (index < tuples_.size()) {
    TupleSet temp_tuples;
    temp_tuples.set_schema(schema_);
    // 取不同的第一个tuple
    temp_tuples.add(std::move(tuples_[index++]));

    while(index < tuples_.size()) {
      // 取与上一个tuple不一样的下一个tuple
      auto& group_tuple = tuples_[index];
      int ret = 0;
      for (size_t i = 0; i < group_num; i++) {
        int attr_index = schema_.index_of_field(groups[i].group_attr.relation_name, groups[i].group_attr.attribute_name);
        if (attr_index == -1) {
          LOG_ERROR("Unexpected %s:%s", groups[i].group_attr.relation_name, groups[i].group_attr.attribute_name);
        }
        ret = group_tuple.get(attr_index).compare(temp_tuples.get(0).get(attr_index));
        // 有一项field不一样
        if (ret != 0) {
          break;
        }
      }
      // 证明group_num个值都与 temp_tuples 第一项相同
      if (ret == 0) {
        temp_tuples.add(std::move(group_tuple));
        index++;
      } else {
        // 这一项和已有的不相同，应该作为下一次的第一项
        result_tupleset.emplace_back(std::move(temp_tuples));
        break;
      }
    }
    // 3333这种情况需要在跳出上面循环以后把temp_tuples插入result_tupleset
    if (index >= tuples_.size()) {
      result_tupleset.emplace_back(std::move(temp_tuples));
    }
  }
  
  delete[] order_;
  return;
}


void TupleSet::erase_projection() {
  auto schema_fields = schema_.fields();
  std::stringstream ss;
  schema_.print(ss);
  LOG_DEBUG("schema display before : %s", ss.str().c_str());

  if (tuples_.size() > 0) {
    assert(schema_fields.size() == tuples_[0].size());
  }
  LOG_DEBUG("tuple.size(%d)", tuples_[0].size());

  // 💩 满天飞
  for (int i = 0; i < schema_fields.size(); ++i) {
    if(schema_fields[i].get_projection()) {
      LOG_DEBUG("schema_fields[%d] %s", i, schema_fields[i].field_name());
      for (int j = 0; j < tuples_.size(); ++j) {
        std::stringstream output;
        tuples_[j].get_pointer(i)->to_string(output);
        LOG_DEBUG("tuple[%d] %s", j, output.str().c_str());
        tuples_[j].remove(i);
      }
      schema_fields.erase(schema_fields.begin() + i);
      i--;
    }
  }
  schema_.erase_projection();
  ss.str(""); // 清空缓冲区
  schema_.print(ss);
  LOG_DEBUG("schema display after : %s", ss.str().c_str());
}


/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case DATES:
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


