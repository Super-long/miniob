## Create Table
1. create table test1(in1 int, ch1 char, fl1 float, da1 date); 
2. create table test2(in2 int, ch2 char, fl2 float, da2 date); 
3. create table test3(in3 int, ch3 char, fl3 float, da3 date); 

## Insert Multi Values
1. insert into test1 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
2. insert into test2 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");
3. insert into test3 values(1,"a",1.1, "2000-10-01"),(2,"b",2.2, "2000-10-02"),(3,"c",3.3, "2000-10-03"),(4,"d",4.4, "2000-10-04"),(5,"e",5.5, "2000-10-05");

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