#include "storage/common/unique_index.h"
#include "common/log/log.h"

UniqueIndex::~UniqueIndex() noexcept {
  close();
}

RC UniqueIndex::create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  
  RC rc = Index::init(index_meta, fields_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  assert(false == fields_meta.empty());
  rc = index_handler_.create(file_name, FieldMeta2FieldsAttr(fields_meta));
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC UniqueIndex::open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta) {
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

RC UniqueIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

// 唯一索引显然我们只使用到了 fields_meta_ 的第0项
RC UniqueIndex::insert_entry(const char *record, const RID *rid) {
  RID is_unique_rid;
  assert(false == fields_meta_.empty());
  // TODO：因为我修改了get_entry中的comparekey，所以在但是其实rollback中我们需要rid的比较，所以多列所以需要重新实现get_entry
  RC rc = index_handler_.get_entry(record + fields_meta_[0].offset(), &is_unique_rid);
  if (rc != RC::SUCCESS) {
    return index_handler_.insert_entry(record + fields_meta_[0].offset(), rid);
  }
  // 反之找到对应的值，那我们应该返回错误
  return RC::RECORD_INVALID_KEY;
}

RC UniqueIndex::delete_entry(const char *record, const RID *rid) {
  assert(false == fields_meta_.empty());
  // 在某一个索引插入失败的时候会调用delete_entry
  return index_handler_.delete_entry(record + fields_meta_[0].offset(), rid);
}

IndexScanner *UniqueIndex::create_scanner(CompOp comp_op, const char *value) {
  LOG_DEBUG("Pay attention here！ERROR in UniqueIndex::create_scanner");
  return nullptr;
}

RC UniqueIndex::sync() {
  return index_handler_.sync();
}
