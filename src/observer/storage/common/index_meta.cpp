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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, std::vector<FieldMeta> fields_array) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for (auto& field : fields_array) {
    fields_.emplace_back(field.name());
  }
  return RC::SUCCESS;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c) {
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length()) {
    v.push_back(s.substr(pos1));
  }
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  // 事实上我们需要把field_中的数据做一个序列化，把数据写入FIELD_FIELD_NAME中
  // TODO:这里我们序列化的过程就是把“;”当作不同field的间隔符号,实际上赌一手field没有;符号
  std::string splicing_field;

  // 至少我们有数据的时候才会去序列化
  assert(fields_.size() > 0);
  splicing_field += fields_[0];
  for (int i = 1; i < fields_.size(); ++i) {
    splicing_field += (";"+fields_[i]);
  }
  json_value[FIELD_FIELD_NAME] = splicing_field;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
              name_value.asCString(), field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  std::vector<FieldMeta> fields_array;
  std::vector<std::string> fields_names;
  SplitString(field_value.asCString(), fields_names, ";");
  for (auto& item : fields_names) {
    const FieldMeta* field = table.field(item.c_str());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields_array.emplace_back(*field);
  }

  return index.init(name_value.asCString(), fields_array);
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const std::vector<std::string>& IndexMeta::field() const {
  return fields_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_;
  for (auto& item : fields_) {
    os << ", field=" << item;
  }
}