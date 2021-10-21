/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
#include "value.h"

TupleValue *ValueToTupleValue(Value *v) {
  if (!v)
    return nullptr;
  switch (v->type) {
    case INTS:
      return new IntValue(*(int*)(v->data));
    case FLOATS:
      return new FloatValue(*(float*)(v->data));
    case CHARS:
      return new StringValue((const char*)v->data);
    default:
      /* unsupported */
      return nullptr;
  }
}