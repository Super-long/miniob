## Create Table
1. create table test1(in1 int, ch1 char, fl1 float, da1 date); 
2. create table test2(in2 int, ch2 char, fl2 float, da2 date); 
3. create table test3(in3 int, ch3 char, fl3 float, da3 date); 

## Insert Multi Values
1. insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
2. insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
3. insert into test3 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
4. insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c","2000-10-03", 1),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");

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