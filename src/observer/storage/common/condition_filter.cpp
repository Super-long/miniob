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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include <sql/executor/tuple.h>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"
#include "sql/executor/execute_stage.h"

using namespace common;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.is_sub_select = false;
  left_.tuple_set = nullptr;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.is_sub_select = false;
  right_.tuple_set = nullptr;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op)
{
  if (attr_type < CHARS || attr_type > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}
RC DefaultConditionFilter::init(const char *db, ExecuteStage* stage, Table &table, const Condition &condition, SessionEvent *session_event)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
    left.type = type_left;
  } else if (1 == condition.left_is_subselect) {
      std::vector<TupleSet> result_tupleset;
      int size;
      stage->do_select(db, *condition.left_select, session_event, result_tupleset, &size);
      left.is_attr = false;
      left.is_sub_select = true;
      // left
      if (!result_tupleset.size()) {
        left.tuple_set = NULL;
      } else {
        left.tuple_set = new TupleSet(std::move(result_tupleset.front()));
      }

      if (left.tuple_set->schema().size() != 1) {
        return INVALID_ARGUMENT;
      }

      left.tuple_set->debug();

      type_left = left.tuple_set->schema().field(0).type();
      left.type = type_left;
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data;  // 校验type 或者转换类型
    type_left = condition.left_value.type;
    left.type = type_left;

    AttrType tright;
    if (!condition.right_is_attr) {
        tright = condition.right_value.type;
    } else {
        tright = table_meta.field(condition.right_attr.attribute_name)->type();
    }
    if (tright == DATES) {
        char *data = static_cast<char *>(left.value);
        std::string new_value;
        char *token = strtok(data, "-");
        std::vector<std::string> vec;
        while (token != nullptr) {
            if (strlen(token) == 1) {
                new_value += "0";
            }
            vec.emplace_back(token);
            new_value += token;
            token = strtok(nullptr, "-");
            if (token != nullptr) {
                new_value += "-";
            }
        }
        // check validation
        int year = atoi(vec[0].c_str());
        if (year <= 0) {
            return INVALID_ARGUMENT;
        }
        int month = atoi(vec[1].c_str());
        if (month <= 0 || month >= 13) {
            return INVALID_ARGUMENT;
        }
        int day = atoi(vec[2].c_str());
        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12: {
                if (day <= 0 || day >= 32) {
                    return INVALID_ARGUMENT;
                }
                break;
            }
            case 4:
            case 6:
            case 9:
            case 11: {
                if (day <= 0 || day >= 31) {
                    return INVALID_ARGUMENT;
                }
                break;
            }
            case 2: {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    if (day <= 0 || day >= 30) {
                        return INVALID_ARGUMENT;
                    }
                } else {
                    if (day <= 0 || day >= 29) {
                        return INVALID_ARGUMENT;
                    }
                }
                break;
            }
            default:
                return INVALID_ARGUMENT;
        }
        memcpy(left.value, new_value.c_str(), new_value.size()+1);
    }

    left.attr_length = 0;
    left.attr_offset = 0;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();
    right.type = type_right;
    right.value = nullptr;
  } else if (1 == condition.right_is_subselect) {
      std::vector<TupleSet> result_tupleset;
      int size;
      stage->do_select(db, *condition.right_select, session_event, result_tupleset, &size);
      right.is_attr = false;
      right.is_sub_select = true;
      // right
      if (!result_tupleset.size()) {
        right.tuple_set = NULL;
      } else {
        right.tuple_set = new TupleSet(std::move(result_tupleset.front()));
      }

      if (right.tuple_set->schema().size() != 1) {
        return INVALID_ARGUMENT;
      }

      right.tuple_set->debug();

      type_right = right.tuple_set->schema().field(0).type();
      right.type = type_right;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;
    type_right = condition.right_value.type;
    right.type = type_right;

      if (type_left == DATES) {
          char *data = static_cast<char *>(right.value);
          std::string new_value;
          char *token = strtok(data, "-");
          std::vector<std::string> vec;
          while (token != nullptr) {
              if (strlen(token) == 1) {
                  new_value += "0";
              }
              vec.emplace_back(token);
              new_value += token;
              token = strtok(nullptr, "-");
              if (token != nullptr) {
                  new_value += "-";
              }
          }
          // check validation
          int year = atoi(vec[0].c_str());
          if (year <= 0) {
              return INVALID_ARGUMENT;
          }
          int month = atoi(vec[1].c_str());
          if (month <= 0 || month >= 13) {
              return INVALID_ARGUMENT;
          }
          int day = atoi(vec[2].c_str());
          switch (month) {
              case 1:
              case 3:
              case 5:
              case 7:
              case 8:
              case 10:
              case 12: {
                  if (day <= 0 || day >= 32) {
                      return INVALID_ARGUMENT;
                  }
                  break;
              }
              case 4:
              case 6:
              case 9:
              case 11: {
                  if (day <= 0 || day >= 31) {
                      return INVALID_ARGUMENT;
                  }
                  break;
              }
              case 2: {
                  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                      if (day <= 0 || day >= 30) {
                          return INVALID_ARGUMENT;
                      }
                  } else {
                      if (day <= 0 || day >= 29) {
                          return INVALID_ARGUMENT;
                      }
                  }
                  break;
              }
              default:
                  return INVALID_ARGUMENT;
          }
          memcpy(right.value, new_value.c_str(), new_value.size()+1);
      }

    right.attr_length = 0;
    right.attr_offset = 0;
  }

  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现

  if (type_left != type_right) {
      if (condition.right_is_subselect || condition.left_is_subselect) {
        if ((type_left == INTS && type_right == FLOATS) ||
            (type_left == FLOATS && type_right == INTS)) {
          return init(left, right, FLOATS, condition.comp);
        }
      }

      if ((type_left == DATES && type_right == CHARS) || (type_left == CHARS && type_right == DATES)) {
          // LOG_INFO("%s\n%s", (char *)left.value, (char *)right.value);
          return init(left, right, DATES, condition.comp);
      }
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, condition.comp);
}

bool DefaultConditionFilter::filter_tuple(const Tuple & tuple) const {

    auto cmp_result = tuple.get(left_.attr_offset).compare(tuple.get(right_.attr_offset));

    switch (comp_op_) {
        case EQUAL_TO:
            return 0 == cmp_result;
        case LESS_EQUAL:
            return cmp_result <= 0;
        case NOT_EQUAL:
            return cmp_result != 0;
        case LESS_THAN:
            return cmp_result < 0;
        case GREAT_EQUAL:
            return cmp_result >= 0;
        case GREAT_THAN:
            return cmp_result > 0;

        default:
            break;
    }
    return false;
}

bool DefaultConditionFilter::filter_two_tuple(const Tuple & tuple1,const Tuple & tuple2) const {

    auto cmp_result = tuple1.get(left_.attr_offset).compare(tuple2.get(right_.attr_offset));

    switch (comp_op_) {
        case EQUAL_TO:
            return 0 == cmp_result;
        case LESS_EQUAL:
            return cmp_result <= 0;
        case NOT_EQUAL:
            return cmp_result != 0;
        case LESS_THAN:
            return cmp_result < 0;
        case GREAT_EQUAL:
            return cmp_result >= 0;
        case GREAT_THAN:
            return cmp_result > 0;

        default:
            break;
    }
    return false;
}

bool is_in_tuple(char *left_value, const TupleSet &right_tupleset, AttrType attr_type_) {
  int cmp_result = -1;
  for (int i = 0; i < right_tupleset.size(); ++i) {
    auto right_value = (char *)(right_tupleset.tuples()[i].get(0).val());

    switch (attr_type_) {
      case DATES:
      case CHARS: {  // 字符串都是定长的，直接比较
        // 按照C字符串风格来定
        cmp_result = strcmp(left_value, right_value);
      } break;
      case INTS: {
        // 没有考虑大小端问题
        // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
        int left = *(int *)left_value;
        int right = *(int *)right_value;
        cmp_result = left - right;
      } break;
      case FLOATS: {
        float left = *(float *)left_value;
        float right = *(float *)right_value;
        cmp_result = (int)(left - right);
      } break;
      default: {
      }
    }
    if (cmp_result == 0) {
      break;
    }
  }
  return cmp_result == 0;
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  char *left_value = nullptr;
  char *right_value = nullptr;
  const TupleSet *right_tupleset = nullptr;
  const TupleSet *left_tupleset = nullptr;

  if (left_.is_attr) {  // value
    left_value = (char *)(rec.data + left_.attr_offset);
  } else if (left_.is_sub_select) {
    left_tupleset = left_.tuple_set;
    if (!left_tupleset || left_tupleset->tuples().size() == 0) {
      switch (comp_op_) {
      case ING: return false;
      case NOT_ING: return true;
      default: {LOG_DEBUG("empty subquery"); return false;}; /* LOG_DEBUG */
      }
    }

    left_value = (char *)(left_tupleset->tuples()[0].get(0).val());
    if (left_.type == FLOATS && right_.is_attr && right_.type == INTS && attr_type_ == FLOATS) {
      // 如果是整数和浮点数的比较，需要转换成浮点数
      right_value = (char *)(rec.data + right_.attr_offset);
      int right_i = *(int *)right_value;

      float *right_float = (float *)malloc(sizeof(float));
      *right_float = right_i;
      right_value = (char*)right_float;
    }
  } else {
    left_value = (char *)left_.value;
  }
  if (!right_value) {
    if (right_.is_attr) {
      right_value = (char *)(rec.data + right_.attr_offset);
    } else if (right_.is_sub_select) {
      right_tupleset = right_.tuple_set;
      if (!right_tupleset || right_tupleset->tuples().size() == 0) {
        switch (comp_op_) {
        case ING: return false;
        case NOT_ING: return true;
        default: {LOG_DEBUG("empty subquery"); return false;}; /* LOG_DEBUG */
        }
      }

      right_value = (char *)(right_tupleset->tuples()[0].get(0).val());
      if (right_.type == FLOATS && left_.type == INTS && attr_type_ == FLOATS) {
        // 如果是整数和浮点数的比较，需要转换成浮点数
        int left_i = *(int *)left_value;
        float *left_float = (float *)malloc(sizeof(float));
        *left_float = left_i;
        left_value = (char*)left_float;
      }
    } else {
      right_value = (char *)right_.value;
    }
  }

  int cmp_result = 0;
  switch (attr_type_) {
    case DATES:
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = *(float *)right_value;
      if (left - right  > 0) {
        cmp_result = 1;
      } else if (left - right < 0) {
        cmp_result = -1;
      }
    } break;
    default: {
    }
  }

  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;
    case ING: {
      if (right_tupleset) {
        return is_in_tuple(left_value, *right_tupleset, attr_type_);
      } else if (left_tupleset) {
        LOG_PANIC("we should not use grammer like select xxx from xxx where (xxx) IN xx ?!");
      }
    }
    case NOT_ING: {
      if (right_tupleset) {
        return !is_in_tuple(left_value, *right_tupleset, attr_type_);
      } else if (left_tupleset) {
        LOG_PANIC("we should not use grammer like select xxx from xxx where (xxx) NOT IN xx ?!");
      }
    }

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(NULL, NULL, table, conditions[i], NULL);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
