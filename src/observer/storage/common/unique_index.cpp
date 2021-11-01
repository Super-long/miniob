#include "storage/common/unique_index.h"
#include "common/log/log.h"

UniqueIndex::~UniqueIndex() noexcept {
  close();
}

RC UniqueIndex::create(const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  
  // 当前我们只考虑索引中有单个值
  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.create(file_name, field_meta.type(), field_meta.len());
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC UniqueIndex::open(const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_meta);
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

RC UniqueIndex::insert_entry(const char *record, const RID *rid) {
  RID is_unique_rid;
  RC rc = index_handler_.get_entry(record, &is_unique_rid);
  // 没找到对应的值
  if (rc == RC::RECORD_INVALID_KEY) {
    return index_handler_.insert_entry(record + field_meta_.offset(), rid);
  }
  // 反之找到对应的值，那我们应该返回错误
  return RC::RECORD_INVALID_KEY;
}

RC UniqueIndex::sync() {
  return index_handler_.sync();
}
