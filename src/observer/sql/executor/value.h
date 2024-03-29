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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <string>
#include <iostream>
#include <sstream>
#include "../parser/parse_defs.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;
  virtual const char *to_const_char() const = 0;
  virtual void to_string(std::ostream &os) const = 0;
  virtual void to_string(std::string &s) const = 0;
  virtual std::string to_string() const = 0;
  virtual void* val() = 0;
  virtual const void* val() const = 0;
  virtual int compare(const TupleValue &other) const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value) {
  }

  const char *to_const_char() const override {
        /* Have not implement */
        return nullptr;
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  void to_string(std::string &s) const override{
      std::ostringstream oss;
      to_string(oss);
      s = oss.str();
  }

  std::string to_string() const override {
    std::string s;
    to_string(s);
    return s;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  int value() const {
      return value_;
  }

  void *val() override {
      return &value_;
  }

  const void *val() const override {
      return &value_;
  }

private:
  int value_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
      auto size = std::snprintf(nullptr, 0, "%.2f", value_);
      std::string output(size + 1, '\0');
      std::sprintf(&output[0], "%.2f", value_);
      if (output[output.size()-2] == '0') {
          output[output.size()-2] = '\0';
          if (output[output.size()-3] == '0') {
              output[output.size()-4] = '\0';
          }
      }
      os << output.c_str();
  }

  const char *to_const_char() const override {
        /* Have not implement */
        return nullptr;
  }

  void to_string(std::string &s) const override{
      std::ostringstream oss;
      to_string(oss);
      s = oss.str();
  }

  std::string to_string() const override {
    std::string s;
    to_string(s);
    return s;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

    void sumFloat(const TupleValue &other) {
        auto float_other = (const FloatValue &)other;
        value_ += float_other.value_;
    }

    void sumInt(const TupleValue &other) {
      auto int_other = (const IntValue &)other;
      value_ += int_other.value();
  }

    void div(const TupleValue &other) {
        auto float_other = (const FloatValue &)other;
        value_ /= float_other.value_;
    }

    void *val() override {
        return &value_;
    }

    const void *val() const override {
        return &value_;
    }


private:
  float value_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  void to_string(std::string &s) const override{
      std::ostringstream oss;
      to_string(oss);
      s = oss.str();
  }

  const char *to_const_char() const override {
    return value_.c_str();
  }

  std::string to_string() const override {
    std::string s;
    to_string(s);
    return s;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  void *val() override {
      return &value_;
  }

  const void *val() const override {
      return &value_;
  }
private:
  std::string value_;
};

TupleValue *ValueToTupleValue(Value *v);

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_