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
// Created by wangyunlai.wyl on 2021
//

#include "storage/default/disk_buffer_pool.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(test_bp_manager, test_bp_manager_simple_lru) {
  BPManager bp_manager(2);

  Frame * frame1 = bp_manager.alloc();
  ASSERT_NE(frame1, nullptr);

  frame1->file_desc = 0;
  frame1->page.page_num = 1;

  ASSERT_EQ(frame1, bp_manager.get(0, 1));

  Frame *frame2 = bp_manager.alloc();
  ASSERT_NE(frame2, nullptr);
  frame2->file_desc = 0;
  frame2->page.page_num = 2;

  ASSERT_EQ(frame1, bp_manager.get(0, 1));

  Frame *frame3 = bp_manager.alloc();
  ASSERT_NE(frame3, nullptr);
  frame3->file_desc = 0;
  frame3->page.page_num = 3;

  frame2 = bp_manager.get(0, 2);
  ASSERT_EQ(frame2, nullptr);

  Frame *frame4 = bp_manager.alloc();
  frame4->file_desc = 0;
  frame4->page.page_num = 4;

  frame1 = bp_manager.get(0, 1);
  ASSERT_EQ(frame1, nullptr);

  frame3 = bp_manager.get(0, 3);
  ASSERT_NE(frame3, nullptr);

  frame4 = bp_manager.get(0, 4);
  ASSERT_NE(frame4, nullptr);
}

TEST(test_bp_manager, test_simple_disk_buffer_pool) {
  constexpr char* file_name = "bp_manger_miniob_test";
  auto disk_buffer_pool = new DiskBufferPool(2);
  RC ret = disk_buffer_pool->create_file(file_name);
  int file_id = -1;
  // 隐藏着分配了一个页
  disk_buffer_pool->open_file(file_name, &file_id);

  BPPageHandle page_handle1;

  disk_buffer_pool->allocate_page(file_id, &page_handle1);
  Frame* frame1 = page_handle1.frame;
  // 注意我们只需要去赋值page_num就可以了，其他的基础量已经在allocate_page中赋值过了
  frame1->page.page_num = 1;
  memcpy(frame1->page.data, "bp_manger_miniob_test:frame1", 30);
  frame1->dirty = true;
  ASSERT_NE(frame1, nullptr);

  disk_buffer_pool->unpin_page(&page_handle1);

  BPPageHandle page_handle2 = {};

  disk_buffer_pool->allocate_page(file_id, &page_handle2);
  Frame* frame2 = page_handle2.frame;
  frame2->page.page_num = 2;
  ASSERT_NE(frame2, nullptr);

  BPPageHandle page_handle3 = {};

  ret = disk_buffer_pool->allocate_page(file_id, &page_handle3);
  Frame* frame3 = page_handle3.frame;
  ASSERT_EQ(frame3, nullptr);

  page_handle1 = {};
  // 此时存在的2和一个起始页，pin_count=1，所以分配会失败
  ret = disk_buffer_pool->get_this_page(file_id, 1, &page_handle1);
  ASSERT_EQ(ret, RC::NOMEM);

  // 这里我们unpin page_num=2
  disk_buffer_pool->unpin_page(&page_handle2);

  page_handle2 = {};
  ret = disk_buffer_pool->get_this_page(file_id, 1, &page_handle2);
  frame1 = page_handle2.frame;
  //std::cout << "{" << frame1->page.data << "}" << std::endl;
  EXPECT_STREQ(frame1->page.data, "bp_manger_miniob_test:frame1");

  // 此时存在一个1和起始页，pincount=1，分配也会失败
  ret = disk_buffer_pool->get_this_page(file_id, 2, &page_handle1);
  ASSERT_EQ(ret, RC::NOMEM);

  int page_count = 0;
  // TODO:这里需要注意，page_count是每次allocate_page都会加1,注意pagenum的分配。
  // disk_buffer_pool->get_page_count(file_id, &page_count);
  // std::cout << "page_count : " << page_count << std::endl;
  //ASSERT_EQ(3, page_count);

  // 把此文件所有的页刷入磁盘，然后我们可以随便分配,此时分配3，4
  //disk_buffer_pool->flush_all_pages(file_id);
  ret = disk_buffer_pool->close_file(file_id);
  // 默认打开一个页
  ret = disk_buffer_pool->open_file(file_name, &file_id);
  disk_buffer_pool->get_page_count(file_id, &page_count);

  page_handle3 = {};
  disk_buffer_pool->allocate_page(file_id, &page_handle3);
  frame3 = page_handle3.frame;
  ASSERT_NE(frame3, nullptr);
  frame3->page.page_num = 3;

  ret = disk_buffer_pool->get_page_count(file_id, &page_count);

  BPPageHandle page_handle4 = {};
  ret = disk_buffer_pool->allocate_page(file_id, &page_handle4);
  Frame* frame4 = page_handle4.frame;
  ASSERT_EQ(frame4, nullptr);

  // disk_buffer_pool->get_page_count(file_id, &page_count);
  // std::cout << "page_count5 : " << page_count << std::endl;
  // ASSERT_EQ(4, page_count);

  disk_buffer_pool->unpin_page(&page_handle3);

  page_handle1 = {};
  frame1 = nullptr;
  ret = disk_buffer_pool->get_this_page(file_id, 1, &page_handle1);
  frame1 = page_handle1.frame;
  EXPECT_STREQ(frame1->page.data, "bp_manger_miniob_test:frame1");
}

int main(int argc, char **argv) {


  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}