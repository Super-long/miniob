#ifndef __OBSERVER_STORAGE_COMMON_UNIQUE_TREE_INDEX_H_
#define __OBSERVER_STORAGE_COMMON_UNIQUE_TREE_INDEX_H_

#include "storage/common/index.h"
#include "storage/common/bplus_tree.h"

class UniqueIndex : public Index {
public:
  UniqueIndex() = default;
  virtual ~UniqueIndex() noexcept;

  RC create(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta);
  RC open(const char *file_name, const IndexMeta &index_meta, std::vector<FieldMeta> fields_meta);
  RC close();

  RC insert_entry(const char *record, const RID *rid) override;
  RC delete_entry(const char *record, const RID *rid) override;

  IndexScanner *create_scanner(CompOp comp_op, const char *value) override;
  RC sync() override;

private:
  bool inited_ = false;
  BplusTreeHandler index_handler_;
};

#endif //__OBSERVER_STORAGE_COMMON_UNIQUE_TREE_INDEX_H_