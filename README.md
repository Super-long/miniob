## 提交规范
1. 以PR形式提交，至少一人review
2. commit信息/PR信息需要全面一些，写出提交内容以及遇到的坑点

## 开发周记
分为两个文件夹，记录从简，主要是为了对这段时间回想时清晰一点
1. 一个problem，记录miniob相关问题
2. 一个summary，总结一周做的事情

## 类图
miniob.drawio，登陆https://www.diagrams.net/打开，基本的，简单的一个脉络，未完成


## 代码中目前存在的一些疑问
1. insert_record中insert_operation并没有修改record中的trx_id，那个注释需要取消吗

## disk_buffer_pool接口解释
具体用法可参考 miniob/unitest/bp_manager_test.cpp 中test_simple_disk_buffer_pool的用法
1. creat_file：创建一个page，写入磁盘，这个页上有一个BPFileSubHeader与bitmap，bitmap标记当前哪些pagnum是空闲的
2. open_file：先给hdr_frame分配一个page，然后载入第一个页，也就是前面我们创建的那个页
3. get_this_page：我们通过前面返回file_id，以及pagenum拿到page信息
4. allocate_page：在已有的文件中分配一个页，page_num直接拿file_sub_header->page_count的值