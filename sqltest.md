## Create Table
1. create table test1(in1 int, ch1 char, fl1 float, da1 date); 
2. create table test2(in2 int, ch2 char, fl2 float, da2 date); 
3. create table test3(in3 int, ch3 char, fl3 float, da3 date); 
3. create table test4(in4 int, ch4 char, fl4 float, da4 date); 
5. create table test5(in5 int, ch5 char, fl5 float, da5 date); 

## Insert Multi Values
insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test3 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test4 values(5,"e",1.1, "2000-10-01"),(4,"d",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(2,"b",4.4, "2000-10-04"),(1,"a",5.5, "2000-10-05");
insert into test5 values(5,"e",1.1, "2000-10-01"),(4,"d",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(2,"b",4.4, "2000-10-04"),(1,"a",5.5, "2000-10-05");
insert into test5 values(5,"e",1.1, "2000-10-01"),(4,"d",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(2,"b",4.4, "2000-10-04"),(1,"a",5.5, "2000-10-05");

## Multi-Tables Query
1. select * from test1, test2, test3;                                                       // y
2. select * from test1, test2 where test1.ch1 = test2.ch2;                                  // y
3. select * from test1, test2 where test1.in1 < 10;                                         // y
4. select test1.in1, test2.in2 from test1, test2;                                           // y
5. select test1.in1, test2.in2 from test1,test2 where test1.ch1 = test2.ch2;                // y
6. select test1.in1, test1.ch1, test2.ch2 from test1, test2 where test1.ch1 = test2.ch2;    // y
7. select test1.in1 from test1,test2 where test1.ch1 = test2.ch2;                           // y
8. select test1.in1 from test1,test2 where test1.in1 < 10;                                  // y
9. select test1.in1 from test1,test2 where test2.in2 < 10;                                  // y
10. select test1.*, test2.in2 from test1, test2;                                            // y
11. select *, test1.in1 from test1, test2;                                                  // y

## Aggregate Functions
---
1. 不考虑常量中的字符串
2. 不考虑count(1,0,3)这种case，聚合函数中最多一个元素

---

1. select count(in1) from test1;                                                            // y
2. select count(fl1) from test1;                                                            // y
3. select count(da1) from test1;                                                            // y
4. select count(1.1) from test1;                                                            // y
5. select count(1) from test1;                                                              // y
6. select count(*) from test1;                                                              // y
7. select count(test1.in1) from test1;                                                      // y
8. select count(test1.*) from test1;                                                        // y

---

1. select max(in1) from test1;                                                              // y
2. select max(fl1) from test1;                                                              // y
3. select max(da1) from test1;                                                              // y
4. select max(1.1) from test1;                                                              // y
5. select max(1) from test1;                                                                // y
6. select max(test1.in1) from test1;                                                        // y

---

1. select min(in1) from test1;                                                              // y
2. select min(fl1) from test1;                                                              // y
3. select min(da1) from test1;                                                              // y
4. select min(1.1) from test1;                                                              // y
5. select min(1) from test1;                                                                // y
6. select min(test1.in1) from test1;                                                        // y

---

1. select min(in1), max(fl1) from test1;                                                    // y
2. select min(test1.in1), max(test1.in1), avg(test1.fl1) from test1;                        // y
3. select count(1), count(1.1), min(test1.in1), max(test1.in1), avg(test1.fl1) from test1;  // y
4. select count(in1), max(in1) from test1;                                                  // y
5. select count(*), min(in1) from test1;                                                    // y
5. select min(in1), count(*) from test1;                                                    // y
6. select count(*), max(test1.in1) from test1, test2 where test1.in1 < test2.in2;           // y
7. select count(test1.in1),max(test2.fl2) from test1, test2 where test1.in1 < test2.in2;    // y
8. select min(test1.in1), max(test2.fl2) from test1, test2;                                 // y
9. select count(in1),max(fl1),avg(fl1),count(*) from test1;                                 // y
10. select count(*),count(in1),max(fl1),avg(fl1) from test1;                                // y
11. select count(*), max(in1), count(*) from test1;                                         // y
12. select max(in1),max(in1) from test1;                                                    // y
13. select max(1.1),count(*) from test1;                                                    // y
---

1. select min(test1.in1) from test1, test2;                                                 // y
2. select max(test1.in1) from test1, test2;                                                 // y
3. select avg(test1.in1) from test1, test2;                                                 // y
4. select count(test1.in1) from test1, test2;                                               // y
5. select count(test1.in1) from test1, test2 where test1.fl1 = test2.fl2;                   // y
6. select count(*) from test1, test2;                                                       // y
7. select max(test1.in1), count(*), count(*), count(test1.in1),count(*),min(test2.in2) from test1,test2; // y
---

测试不测的：
1. select count('2021-10-21') from test1;
2. select count('asd') from test1;

### Date
1. select da1 from test1 where da1='2000-10-01';                                               // y
2. select * from test1 where da1>'2020-1-20';                                                  // y
3. select * from test1 where da1<'2019-12-31';                                                 // y

1. insert into test4 values(5,"2019-12-21"),(6,"2016-02-29"),(7,"1970-01-01"),(8,"2000-01-01");
2. insert into test4 values(3,"2020-01-01"),(4,"2020-01-01");
3. select * from test4 where da > '2020-1-20';
4. select * from test4 where da < '2019-12-31';
5. select * from test4 where da = '2020-1-1';

### order by
1. select * from test1 order by in1 desc;                                                     // y
2. select * from test1, test2 where test1.in1 = test2.in2 order by test1.in1 desc;            // y
3. select * from test1, test2 order by test1.in1, test2.in2 desc;                             // y
4. select test1.in1, test2.in2 from test1, test2 order by test2.ch2 desc, order by test1.in1;
5. select test1.in1, test2.in2 from test1, test2 order by test2.ch2, test1.in1 desc;          // y

### group by 
1. select test1.in1, test2.in2, count(*), max(test2.in2) from test1, test2 group by test1.in1, test2.in2;   // y
2. select test2.in2, test1.in1, count(*), max(test2.in2) from test1, test2 group by test1.in1, test2.in2;   // y
3. select test1.in1, count(*), max(test1.fl1) from test1 group by test1.in1;                                // y
4. select test1.in1, max(test1.fl1), max(test1.da1), count(*) from test1 group by test1.in1;                // y
5. select test1.in1, test2.in2, count(*), max(test2.in2) from test1, test2 where test1.in1 = test2.in2 group by test1.in1, test2.in2;   // y
6. select test1.in1, test2.in2, count(*), max(test2.in2) from test1, test2 where test1.in1 > 100 group by test1.in1, test2.in2;
7. select test1.in1, count(test1.in1) from test1, test2 where test2.in2 > 100 group by test1.in1;

### unique index 
1. create unique index index_in1 on test1(in1); 
2. create unique index index_fl1 on test1(fl1);
3. insert into test1 values(1,"a",1.1, "2000-10-01");
4. insert into test1 values(7,"a",1.1, "2000-10-01");
5. create unique index index_in2 on test2(in2);

### text type
create table tt_12(id int, txt text);
insert into tt_12 values(1,"1234567890");
insert into tt_12 values(1,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
insert into tt_12 values(11,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaafuckyouhehehehehaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
select * from tt_12;
update tt_12 set txt="zaijian" where id=11;

create table tt_13(id int, txt text);
insert into tt_13 values(12,"A TMP DATA");
insert into tt_13 values(3,"THIS IS A VERY VERY LONG STRING3");
insert into tt_13 values(4,"THIS IS A VERY VERY LONG STRING PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD1");
select * from tt_13;

 INSERT INTO tt_13 VALUES (5,'THIS IS A VERY VERY LONG STRING PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD PAD1 PAD PAD PAD PAD');

select * from tt_13;

### join
select * from test1,test2;

select * from test1 INNER JOIN test2 ON test1.in1 = test2.in2;
select * from test1 INNER JOIN test2 ON test1.in1 = test2.in2 INNER JOIN test3 ON test1.ch1 = test3.ch3;

select * from test1 INNER JOIN test2 ON test1.in1 = test2.in2 INNER JOIN test3 ON test1.ch1 = test3.ch3 INNER JOIN test4 ON test1.ch1 = test4.ch4;

select * from test1 INNER JOIN test2 ON test1.in1 = test2.in2 AND test1.ch1 > test2.ch2 INNER JOIN test3 ON test1.ch1 = test3.ch3;

create table join_table_large_1(id int, num1 int);
create table join_table_large_2(id int, num2 int);
create table join_table_large_3(id int, num3 int);
create table join_table_large_4(id int, num4 int);
create table join_table_large_5(id int, num5 int);
create table join_table_large_6(id int, num6 int);

insert into join_table_large_1 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);
insert into join_table_large_2 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);
insert into join_table_large_3 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);
insert into join_table_large_4 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);
insert into join_table_large_5 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);
insert into join_table_large_6 values(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8),(9,9),(10,10);

,(11,11),(12,12),(13,13),(14,14),(15,15),(16,16),(17,17),(18,18),(19,19),(20,20),(21,21),(22,22),(23,23),(24,24),(25,25),(26,26),(27,27),(28,28),(29,29),(30,30),(31,31),(32,32),(33,33),(34,34),(35,35),(36,36),(37,37),(38,38),(39,39),(40,40),(41,41),(42,42),(43,43),(44,44),(45,45),(46,46),(47,47),(48,48),(49,49),(50,50),(51,51),(52,52),(53,53),(54,54),(55,55),(56,56),(57,57),(58,58),(59,59),(60,60),(61,61),(62,62),(63,63),(64,64),(65,65),(66,66),(67,67),(68,68),(69,69),(70,70),(71,71),(72,72),(73,73),(74,74),(75,75),(76,76),(77,77),(78,78),(79,79),(80,80),(81,81),(82,82),(83,83),(84,84),(85,85),(86,86),(87,87),(88,88),(89,89),(90,90),(91,91),(92,92),(93,93),(94,94),(95,95),(96,96),(97,97),(98,98),(99,99),(100,100),(101,101);


select * from join_table_large_1 inner join join_table_large_2 on join_table_large_1.id=join_table_large_2.id inner join join_table_large_3 on join_table_large_1.id=join_table_large_3.id inner join join_table_large_4 on join_table_large_3.id=join_table_large_4.id inner join join_table_large_5 on 1=1 inner join join_table_large_6 on join_table_large_5.id=join_table_large_6.id where join_table_large_3.num3 <10 and join_table_large_5.num5<10;


join-tables: result file difference(`-` is yours and `+` is base)
 SELECT * FROM JOIN_TABLE_1 INNER JOIN JOIN_TABLE_2 ON JOIN_TABLE_1.ID=JOIN_TABLE_2.ID INNER JOIN JOIN_TABLE_3 ON JOIN_TABLE_1.ID=JOIN_TABLE_3.ID;
-1 | A | 1 | 120 | 1 | 2
-JOIN_TABLE_1.ID | JOIN_TABLE_1.NAME | JOIN_TABLE_3.ID | JOIN_TABLE_3.NUM2 | JOIN_TABLE_2.ID | JOIN_TABLE_2.NUM
+1 | A | 1 | 2 | 1 | 120
+JOIN_TABLE_1.ID | JOIN_TABLE_1.NAME | JOIN_TABLE_2.ID | JOIN_TABLE_2.NUM | JOIN_TABLE_3.ID | JOIN_TABLE_3.NUM2
 SELECT * FROM JOIN_TABLE_1 INNER JOIN JOIN_TABLE_2 ON JOIN_TABLE_1.ID=JOIN_TABLE_2.ID AND JOIN_TABLE_2.NUM>13 WHERE JOIN_TABLE_1.NAME='B';
-FAILURE
+2 | B | 2 | 15
+JOIN_TABLE_1.ID | JOIN_TABLE_1.NAME | JOIN_TABLE_2.ID | JOIN_TABLE_2.NUM
 SELECT * FROM JOIN_TABLE_1 INNER JOIN JOIN_TABLE_2 ON JOIN_TABLE_1.ID=JOIN_TABLE_2.ID AND JOIN_TABLE_2.NUM>13 WHERE JOIN_TABLE_1.NAME='A';
-FAILURE
+JOIN_TABLE_1.ID | JOIN_TABLE_1.NAME | JOIN_TABLE_2.ID | JOIN_TABLE_2.NUM
 SELECT * FROM JOIN_TABLE_1 INNER JOIN JOIN_TABLE_2 ON JOIN_TABLE_1.ID=JOIN_TABLE_2.ID AND JOIN_TABLE_2.NUM>23 WHERE JOIN_TABLE_1.NAME='B';
-FAILURE
+JOIN_TABLE_1.ID | JOIN_TABLE_1.NAME | JOIN_TABLE_2.ID | JOIN_TABLE_2.NUM


select * from test1 where in1 >(select in2 from test2);


select * from t1 where t1.age >(select max(t2.age) from t2);
select * from t1 where t1.age > (select avg(t2.age) from t2) and t1.age > 20.0;


简单子查询
1. 不同类型 ok
2. 多列 ok
3. 多行 ok
4. IN/NOT IN ok

复杂子查询


insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");

select * from test1 where in1 in(SELECT test2.in2 from test2);
select * from test1 where in1 not in(SELECT test2.in2 from test2);

select * from test1 where in1 <(SELECT max(test1.in1) from test1);
select * from test1 where in1 <(SELECT max(test2.ch2) from test2);

select * from test1 where in1 <(SELECT max(test1.in1),in1 from test1);

select * from test1 where in1 <(SELECT max(test1.ch1), max(test2.ch2) from test2,test1);

select * from test1 where in1 in(SELECT test2.in2 from test2) and test1.in1 < 4 and test1.ch1 > 'a';

select * from test1 where in1 = (SELECT avg(test2.in2) from test2);

insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
SELECT * FROM test1 WHERE fl1 <= (SELECT MAX(test2.fl2) FROM test2);

select * from test1 where (SELECT avg(test2.in2) from test2) = in1;


create table SSQ_1(ID int, COL1 int, FEAT1 float);
create table SSQ_2(ID int, COL2 int, FEAT2 float);
insert into SSQ_1 values(1, 4, 11.2);
insert into SSQ_1 values(2, 2, 12.0);
insert into SSQ_1 values(3, 3, 13.5);
insert into SSQ_2 values(1, 4, 11.2);
insert into SSQ_2 values(2, 2, 12.0);
insert into SSQ_2 values(3, 3, 13.0);
SELECT * FROM SSQ_1 WHERE FEAT1 <= (SELECT MAX(SSQ_2.FEAT2) FROM SSQ_2);


insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
insert into test3 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
select * from test1 where in1 in (select in2 from test2 where test2.in2 in (select in3 from test3));

select * from test1 where (select avg(test2.in2) from test2) <> (select avg(test3.in3) from test3);

select * from test1 where (select avg(test2.in2) from test2) = (select avg(test3.in3) from test3);

select * from test1 where fl1 <> (select avg(test2.in2) from test2 where test2.fl2 > test1.fl1);

select * from test1 where fl1 <> (select max(test2.fl2) from test2 where test2.fl2 > test1.fl1);


create table CSQ_1(ID int, COL1 int, FEAT1 float);
create table CSQ_2(ID int, COL2 int, FEAT2 float);
create table CSQ_3(ID int, COL3 int, FEAT3 float);

insert into CSQ_1 values(1, 4, 11.2);
insert into CSQ_1 values(2, 2, 12.0);
insert into CSQ_1 values(3, 3, 13.5);

insert into CSQ_2 values(1, 4, 12.8);
insert into CSQ_2 values(2, 2, 12.7);
insert into CSQ_2 values(3, 3, 14.5);

insert into CSQ_3 values(1, 4, 10.0);
insert into CSQ_3 values(2, 2, 10.0);
insert into CSQ_3 values(3, 3, 10.0);

+1 | 4 | 11.2
+3 | 3 | 13.5
SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2,CSQ_1 WHERE CSQ_2.FEAT2 > CSQ_1.FEAT1;

SELECT * FROM CSQ_1 WHERE FEAT1 <> (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.FEAT2 > CSQ_1.FEAT1);
SELECT * FROM CSQ_1 WHERE COL1 > (SELECT AVG(CSQ_2.COL2) FROM CSQ_2 WHERE CSQ_2.FEAT2 >= (SELECT MIN(CSQ_3.FEAT3) FROM CSQ_3));

SELECT * FROM CSQ_1 WHERE COL1 NOT IN (SELECT CSQ_2.COL2 FROM CSQ_2 WHERE CSQ_2.ID IN (SELECT CSQ_3.ID FROM CSQ_3 WHERE CSQ_1.ID = CSQ_3.ID));


SELECT CSQ_3.ID FROM CSQ_3,CSQ_2 WHERE CSQ_2.ID > CSQ_3.ID;

SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.ID IN (SELECT CSQ_3.ID FROM CSQ_3 WHERE CSQ_2.ID > CSQ_3.ID);

SELECT * FROM CSQ_1 WHERE FEAT1 < (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.ID IN (SELECT CSQ_3.ID FROM CSQ_3 WHERE CSQ_1.ID > CSQ_3.ID));

SELECT * FROM CSQ_1 WHERE FEAT1 < (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.ID IN (SELECT CSQ_3.ID FROM CSQ_3 WHERE CSQ_1.ID > CSQ_3.ID));

SELECT * FROM CSQ_1 WHERE FEAT1 <> (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_2 WHERE CSQ_2.FEAT2 > CSQ_1.FEAT1);

SELECT * FROM CSQ_1 WHERE FEAT1 <> (SELECT AVG(CSQ_2.FEAT2) FROM CSQ_1,CSQ_2 WHERE CSQ_2.FEAT2 > CSQ_1.FEAT1);

SELECT * FROM CSQ_3,CSQ_1 WHERE CSQ_1.ID < CSQ_3.ID;
test Super-long complex-sub-query
view Super-long complex-sub-query