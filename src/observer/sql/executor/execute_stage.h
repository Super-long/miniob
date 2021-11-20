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
// Created by Longda on 2021/4/13.
//

#ifndef __OBSERVER_SQL_EXECUTE_STAGE_H__
#define __OBSERVER_SQL_EXECUTE_STAGE_H__

#include "common/seda/stage.h"
#include "sql/parser/parse.h"
#include "rc.h"

#include "session/session.h"
#include "sql/executor/execution_node.h"

using namespace common;
class SessionEvent;

class ExecuteStage : public common::Stage {
public:
  ~ExecuteStage();
  static Stage *make_stage(const std::string &tag);

  // RC do_select(const char *db, Selects &select, SessionEvent *session_event);
  RC do_select(const char *db, Selects &selects, SessionEvent *session_event,
               std::vector<TupleSet> &result_tupleset, int *size);
  RC select(const char *db, Selects &selects, SessionEvent *session_event);
  std::set<std::string>& getTables() {return tables_;}
  const std::set<std::string>& getTables() const {return tables_;}

protected:
  // common function
  ExecuteStage(const char *tag);
  bool set_properties() override;

  bool initialize() override;
  void cleanup() override;
  void handle_event(common::StageEvent *event) override;
  void callback_event(common::StageEvent *event,
                     common::CallbackContext *context) override;

  void handle_request(common::StageEvent *event);

protected:
private:
  // do_select中的一些辅助函数，为了让整个逻辑更加清楚一点
  RC create_schema(Session *session, const Selects &selects, const char *db, std::vector<SelectExeNode *>& select_nodes, SessionEvent *session_event);
  RC create_tuples(Session *session, std::vector<SelectExeNode *> select_nodes, std::vector<TupleSet>& result_tupleset);
  RC cross_join(std::vector<TupleSet>& tuple_sets, const Selects &selects, std::vector<TupleSet>& result_tupleset);
  RC execute_aggregation(TupleSet& result_tupleset, const Selects &selects, Session *session, const char *db, bool is_multi);
  RC join(std::vector<TupleSet>& tuple_sets, const Selects &selects, std::vector<TupleSet>& result_tupleset);
  RC inner_join(std::vector<TupleSet>& tuple_sets, const Selects &selects, std::vector<TupleSet>& result_tupleset);

private:
  Stage *default_storage_stage_ = nullptr;
  Stage *mem_storage_stage_ = nullptr;
  int selects_id_ = 0;

  std::set<std::string> tables_;
};

std::set<std::string> FindUnhaveRelations(const Selects &selects);

#endif //__OBSERVER_SQL_EXECUTE_STAGE_H__
