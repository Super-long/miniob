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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept {
  close();
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, fields_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.create(file_name, FieldMeta2FieldsAttr(fields_meta));
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, fields_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

void SpliceFields(char** key, const char *record, const std::vector<FieldMeta>& fields_meta_) {
  // 通过已有的field中拼接数据，然后传入执行比较
  int key_size = 0;
  for (auto& item : fields_meta_) {
    key_size += item.len();
  }
  key_size = 0;
  char* pkey = new char[key_size];
  // 把多个field拼接成一个数据块，索引本身
  for (size_t i = 0; i < fields_meta_.size(); i++) {
    memcpy(pkey + key_size, record + fields_meta_[i].offset(), fields_meta_[i].len());
    key_size += fields_meta_[i].len();
  }
  *key = pkey;
  return;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  // 后面做成智能指针
  char* pkey = nullptr;
  // 这里我们会给pkey分配一个指针
  SpliceFields(&pkey, record, fields_meta_);
  LOG_DEBUG("splice fields record data {%s}", pkey);

  RC rc = index_handler_.insert_entry(pkey, rid);
  delete[] pkey;
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  char* pkey = nullptr;
  SpliceFields(&pkey, record, fields_meta_);

  RC rc = index_handler_.delete_entry(pkey, rid);
  delete[] pkey;
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op, const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() {
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner) :
    tree_scanner_(tree_scanner) {
}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}