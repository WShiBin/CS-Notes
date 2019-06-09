## Hive Architecture

![image-20190412224301691](Hive.assets/image-20190412224301691.png)

## Hive计算引擎

MR.Tez,Spark

## 源码目录

* bin
* conf —> hive-site.xml

```xml
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
		
    <!--元数据-->
    <property>
        <name>javax.jdo.option.ConnectionURL</name>
        <value>jdbc:mysql://hadoop102:3306/metastore?createDatabaseIfNotExist=true</value>
        <description>JDBC connect string for a JDBC metastore</description>
    </property>

  	<!--驱动-->
    <property>
        <name>javax.jdo.option.ConnectionDriverName</name>
        <value>com.mysql.jdbc.Driver</value>
        <description>Driver class name for a JDBC metastore</description>
    </property>

  	<!--用户名-->
    <property>
        <name>javax.jdo.option.ConnectionUserName</name>
        <value>root</value>
        <description>username to use against metastore database</description>
    </property>

  	<!--密码-->
    <property>
        <name>javax.jdo.option.ConnectionPassword</name>
        <value>shibin</value>
        <description>password to use against metastore database</description>
    </property>

  	<!--数据存放目录,默认hdfs-->
    <property>
        <name>hive.metastore.warehouse.dir</name>
        <value>/user/hive/warehouse</value>
        <description>location of default database for the warehouse</description>
    </property>

  	<!--hive命令时,打印头-->
    <property>
        <name>hive.cli.print.header</name>
        <value>true</value>
    </property>

    <!--hive命令时,打印当前数据库-->
    <property>
        <name>hive.cli.print.current.db</name>
        <value>true</value>
    </property>
  
    <property>
        <name>hive.metastore.schema.verification</name>
        <value>false</value>
    </property>

  	<!--更换计算引擎为Tez,默认MR计算,见Tez.md-->
    <property>
        <name>hive.execution.engine</name>
        <value>tez</value>
    </property>

</configuration>
```



* lib —> mysql-connector-java-5.1.17-bin.jar
* example



## Client 连接

### cli连接: hive

```shell
hive -f ~/test.hql # 执行脚本中sql语句
hive -i ~/test.hql
hive> source ~/test.hql
hive -e "select * from student" # 不进入hive的交互窗口执行sql语句
hive -S <-e/-f> "select * from student"  
hive --define var=xxx
hive --hiveconf var=xxx
hive --hivevar foo=student
select * from ${hivevar:foo}
select * from ${foo}

set;
set -v;
set varname;
set varname=val;

! pwd;
! bin/echo "hello";
dfs -ls /l
```

~/.hiverc —> hive启动默认加载

```shell
set hiveconf:hive.cli.print.current.db=true;
set hiveconf:hive.exec.mode.local.auto=true;
set hive.metastore.warehouse.dir=/hive; # 路径
set mapred.reduce.tasks=100;
```



~/.hivehistory —>hive 历史记录,(quit;才会触发)

### JDBC 连接

```shell
> hiveserver2
> beeline
Beeline version 1.2.1 by Apache Hive
beeline> !connect jdbc:hive2://hadoop005:10000
Connecting to jdbc:hive2://hadooop005:10000
Enter username for jdbc:hive2://hadoop005:10000: ben
Enter password for jdbc:hive2://hadoop005:10000:
Connected to: Apache Hive (version 1.2.1)
Driver: Hive JDBC (version 1.2.1)
Transaction isolation: TRANSACTION_REPEATABLE_READ
1: jdbc:hive2://hadoop005:10000>
```

### Java code

```java
package com.ishibin;

import java.sql.*;

/**
 * Created with IntelliJ IDEA.
 * Description:
 * User: Ben
 * Date: 2019-03-12
 * Time: 20:14
 */
public class HelloHive {
	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		Class.forName("org.apache.hive.jdbc.HiveDriver");
		Connection conn = DriverManager.getConnection("jdbc:hive2://hadoop005:10000");
		String sql = "select * from default.student";
		PreparedStatement ps = conn.prepareStatement(sql);
		ResultSet resultSet = ps.executeQuery();
		while (resultSet.next()) {
			int id = resultSet.getInt(1);
			String name = resultSet.getString(2);
			System.out.println(id + " - " + name + "\t");
		}
	}

	public boolean isOld(int i) {
		return (i % 2) == 1;
	}
}
```



## 数据类型

### 基本数据类型

| Hive数据类型 | Java数据类型 | 长度                                                 | 例子                                 |
| ------------ | ------------ | ---------------------------------------------------- | ------------------------------------ |
| TINYINT      | byte         | 1byte有符号整数                                      | 20                                   |
| SMALINT      | short        | 2byte有符号整数                                      | 20                                   |
| INT          | int          | 4byte有符号整数                                      | 20                                   |
| BIGINT       | long         | 8byte有符号整数                                      | 20                                   |
| BOOLEAN      | boolean      | 布尔类型，true或者false                              | TRUE  FALSE                          |
| FLOAT        | float        | 单精度浮点数                                         | 3.14159                              |
| DOUBLE       | double       | 双精度浮点数                                         | 3.14159                              |
| STRING       | string       | 字符系列。可以指定字符集。可以使用单引号或者双引号。 | ‘now is the time’ “for all good men” |
| TIMESTAMP    |              | 时间类型                                             |                                      |
| BINARY       |              | 字节数组                                             |                                      |

### 集合数据类型

| 数据类型 | 描述                                                         | 语法示例 |
| -------- | ------------------------------------------------------------ | -------- |
| STRUCT   | 和c语言中的struct类似，都可以通过“点”符号访问元素内容。例如，如果某个列的数据类型是STRUCT{first STRING, last STRING},那么第1个元素可以通过字段.first来引用。 | struct() |
| MAP      | MAP是一组键-值对元组集合，使用数组表示法可以访问数据。例如，如果某个列的数据类型是MAP，其中键->值对是’first’->’John’和’last’->’Doe’，那么可以通过字段名[‘last’]获取最后一个元素 | map()    |
| ARRAY    | 数组是一组具有相同类型和名称的变量的集合。这些变量称为数组的元素，每个数组元素都有一个编号，编号从零开始。例如，数组值为[‘John’, ‘Doe’]，那么第2个元素可以通过数组名[1]进行引用。 | Array()  |

实例:

```json
{
    "name": "songsong",
    "friends": ["bingbing" , "lili"] ,       	//列表Array, 
    "children": {                      				//键值Map,
        "xiao song": 18 ,
        "xiaoxiao song": 19
    },
    "address": {                      				//结构Struct,
        "street": "hui long guan" ,
        "city": "beijing" 
    }
}
```

test.txt

```
songsong,bingbing_lili,xiao song:18_xiaoxiao song:19,hui long guan_beijing
yangyang,caicai_susu,xiao yang:18_xiaoxiao yang:19,chao yang_beijin
```

Create table hql;

```sql
create table test(
    name string,
    friends array<string>,
    children map<string, int>,
    address struct<street:string, city:string>
)
row format delimited fields terminated by ','
collection items terminated by '_'
map keys terminated by ':'
lines terminated by '\n';
```

Hive shell;

```shell
> load data local inpath '/opt/module/hive/test.txt' into table test
```



### 类型转化

**隐式类型转换规则如下**

- 任何整数类型都可以隐式地转换为一个范围更广的类型，如TINYINT可以转换成INT，INT可以转换成BIGINT。
- 所有整数类型、FLOAT和STRING类型都可以隐式地转换成DOUBLE。
- TINYINT、SMALLINT、INT都可以转换为FLOAT。
- BOOLEAN类型不可以转换为任何其它的类型。

**可以使用CAST操作显示进行数据类型转换**

- 例如CAST('1' AS INT)将把字符串'1' 转换成整数1；如果强制类型转换失败，如执行CAST('X' AS INT)，表达式返回空值 NULL



## DDL数据定义

### 创建库

```sql
> create database db_name;			-- 默认hive-site.xml中,hive.metastore.warehouse.dir
> create database if not exists db_name;
> create database db_name location '/hive/hb_hive.db';
```

### 查询库

```sql
> show databases;
> show databases like 'db_nam*';
> desc database db_name;
> desc database extended db_name;
> use db_name;
```

### 修改库

```sql
> alter database db_name set dbproperties('createtime'='20170830');
> desc database extended db_name;
```

### 删除库

```sql
> drop database db_name;
> drop database if exists db_name;
> drop database db_name cascade; -- 强制删除
```

### 创建表

```sql
CREATE [EXTERNAL] TABLE [IF NOT EXISTS] table_name 
[(col_name data_type [COMMENT col_comment], ...)] 
[COMMENT table_comment] 
[PARTITIONED BY (col_name data_type [COMMENT col_comment], ...)] 
[CLUSTERED BY (col_name, col_name, ...) 
[SORTED BY (col_name [ASC|DESC], ...)] INTO num_buckets BUCKETS] 
[ROW FORMAT row_format] 
[STORED AS file_format] 
[LOCATION hdfs_path]
```

* EXTERNAL 外部表/管理表
* PARTITIONED  BY 分区(建子目录)
* CLUSTERED BY 分桶 
* SORTED BY 
* ROW FORMAT DELIMITED 
  * [FIELDS TERMINATED BY char] **—flelds分隔符**
  * [COLLECTION ITEMS TERMINATED BY char] **— collection 分隔符**
  * [MAP KEYS TERMINATED BY char]  **— map 分隔符**
  * [LINES TERMINATED BY char]  **—行分隔符**
  * | SERDE serde_name **— SerDe是Serialize/Deserilize的简称，目的是用于序列化和反序列化**
  * [WITH SERDEPROPERTIES (property_name=property_value, property_name=property_value, ...)]
* STORED AS 指定存储文件类型
  * SEQUENCEFILE（二进制序列文件）
  * TEXTFILE（文本）
  * RCFILE（列式存储格式文件）
* LOCATION 位置
* LIKE 复制表结构

```sql
create table test(
    name string,
    friends array<string>,
    children map<string, int>,
    address struct<street:string, city:string>
)
row format delimited fields terminated by ','
collection items terminated by '_'
map keys terminated by ':'
lines terminated by '\n';

desc test;
desc formatted test;
show create table test;
```



#### 管理表(Default)

```shell
set hive.metastore.warehouse.dir;
```

> **管理表会关联 dfs 上的数据, 删除表时,同时也会删除 dfs 中的数据**

```sql
create table if not exists student2(
	id int, name string
)
row format delimited fields terminated by '\t'
stored as textfile
location '/user/hive/warehouse/student2';

create table if not exists student3 as select id, name from student; --表结构及表内容

create table if not exists student4 like student; --表结构
```



#### 外部表

> 因为表是外部表，所以Hive并非认为其完全拥有这份数据。**删除该表并不会删除掉这份数据，不过描述表的元数据信息会被删除掉。**

```sql
create external table if not exists default.dept(
	deptno int,
	dname string,
	loc int
)
row format delimited fields terminated by '\t';
```

```
create external table if not exists default.emp(
	empno int,
	ename string,
	job string,
	mgr int,
	hiredate string, 
	sal double, 
	comm double,
	deptno int
)
row format delimited fields terminated by '\t';
```

```sql
load data local inpath '/opt/module/datas/dept.txt' into table default.dept;
```

```sql
alter table student set tblproperties ('EXTERNAL'='TURE'); --转成外部表
alter table student set tblproperties ('EXTERNAL'='FALSE'); --转成内部表
```

### 分区表

>  Hive中的分区本质上是在 HDFS 中分目录,文件夹名是分区号(/dept_partition/201906/dept.txt)

```sql
load data local inpath './dept.txt' into table dept_partition partition (month='201906');

select * from dept_partition where month='201903';

select * from dept_partition where month='201903'
union
select * from dept_partition where month='201704'
union
select * from dept_partition where month='201705';

alter table dept_partition add partition(month='201706');
alter table dept_partition add partition(month='201705') partition(month='201704');

alter table dept_partition drop partition (month='201704');
alter table dept_partition drop partition (month='201705'), partition (month='201706');

-- 显示表的分区
show partitions dept_partition;
desc formatted dept_partition;
```



![image-20190315202304900](./Hive.assets/image-20190315202304900.png)

```sql
create table dept_partition2(
    deptno int, dname string, loc string
)
partitioned by (month string, day string)
row format delimited fields terminated by '\t';

load data local inpath './dept.txt' into table dept_partition2 partition(month='201903', day='15');

select * from dept_partition2 where month= '201903' and  day = '15';
```

#### 把数据直接上传到分区目录上，让分区表和数据产生关联的三种方式

**方式一：上传数据后修复**

```sql
dfs -put ./dept.txt  /user/hive/warehouse/dept_partition2/month=201903/day=15;
select * from dept_partition2 where month='201903' and day='15';  --查不到
msck repair table dept_partition2;  --修复命令
select * from dept_partition2 where month='201903' and day='15';  --可以查到
```

**方式二：上传数据后添加分区**

```sql
dfs -put /opt/module/datas/dept.txt  /user/hive/warehouse/dept_partition2/month=201709/day=11;
alter table dept_partition2 add partition(month='201709', day='11');	
select * from dept_partition2 where month='201709' and day='11';
```

**方式三：创建文件夹后load数据到分区**

```sql
load data local inpath './dept.txt' into table dept_partition2 partition(month='201709',day='10');
select * from dept_partition2 where month='201709' and day='10';
```

### 修改表

```sql
-- rename tablename
ALTER TABLE table_name RENAME TO new_table_name
alter table dept_partition2 rename to dept_partition1;

-- change column
ALTER TABLE table_name CHANGE [COLUMN] col_old_name col_new_name column_type [COMMENT col_comment] [FIRST|AFTER column_name]
alter table dept_partition1 change phone_num addr string;

-- add column
ALTER TABLE table_name ADD|REPLACE COLUMNS (col_name data_type [COMMENT col_comment], ...) 
alter table dept_partition1 add columns (phone_num string);
-- replce columns
alter table dept_partition1 replace columns(deptno string, dname string, loc string);

-- desc
desc dept_partition1;
desc formatted dept_partition1;

-- delete table
drop table dept_partition1;

-- alter table to external table
alter table student set tblproperties ('EXTERNAL'='TURE');
alter table student set tblproperties ('EXTERNAL'='FALSE');
```



## DML数据操作

### 数据导入

#### 向表中装载数据（Load）

```sql
LOAD DATA LOCAL INPATH './examples/files/kv2.txt' OVERWRITE INTO TABLE invites PARTITION (ds='2008-08-15');
```

- load data:表示加载数据
- local:表示从本地加载数据到hive表；否则从HDFS加载数据到hive表
- inpath:表示加载数据的路径
- overwrite:表示覆盖表中已有数据，否则表示追加
- into table:表示加载到哪张表
- student:表示具体的表
- partition:表示上传到指定分区



#### 通过查询语句向表中插入数据(insert)

```sql
create table student(id int, name string) partitioned by (month string) row format delimited fields terminated by '\t';

-- basic insert
insert into table student partition(month='201709') values(1,'wangwu');

-- insert data from a talbe
insert overwrite table student partition(month='201708') 
	select id, name from student where month='201709';

-- insert data from muti tables
from student
	insert overwrite table student partition(month='201707')
	select id, name where month='201709'
	insert overwrite table student partition(month='201706')
	select id, name where month='201709';
```

#### 查询语句中创建表并加载数据(As Select)

```sql
create table if not exists student3
	as select id, name from student;
```

#### 创建表时通过Location指定加载数据路径

```sql
create table if not exists student5(
    id int, name string
)
row format delimited fields terminated by '\t'
location '/user/hive/warehouse/student5';

dfs -put /opt/module/datas/student.txt /user/hive/warehouse/student5;
```

#### Import数据到指定Hive表中

> 注意：先用export导出后，再将数据导入。

```sql
import table student2 partition(month='201709') from '/user/hive/warehouse/export/student';
```



### 数据导出

#### Insert导出

1．将查询的结果导出到本地

```sql
insert overwrite local directory './student' select * from student;
```

2．将查询的结果格式化导出到本地

```sql
insert overwrite local directory './student1' ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t';

select * from student;
```

3．将查询的结果导出到HDFS上(没有local)

```sql
insert overwrite directory './student2' ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t' 

select * from student;
```

#### Hadoop命令导出到本地

```shell
dfs -get /user/hive/warehouse/student/month=201709/000000_0 /opt/module/datas/export/student3.txt;
```

#### Hive Shell 命令导出

基本语法：（hive -f/-e 执行语句或者脚本 > file）

```shell
bin/hive -e 'select * from default.student;' > /opt/module/datas/export/student4.txt;
```

#### Export导出到HDFS上

```shell
export table default.student to '/user/hive/warehouse/export/student';
```

#### 清除表中数据（Truncate）

注意：Truncate只能删除管理表，不能删除外部表中数据

```sql
truncate table student;
```



## 查询

### 基本查询（Select…From）

```sql
select * from table_name;
select column_name1, column_name2 from table_name;
select column_name1 as alias_name, column_name2 from table_name; -- alias
```

#### 算术运算符

| 运算符 | 描述           |
| ------ | -------------- |
| A+B    | A和B 相加      |
| A-B    | A减去B         |
| A*B    | A和B 相乘      |
| A/B    | A除以B         |
| A%B    | A对B取余       |
| A&B    | A和B按位取与   |
| A\|B   | A和B按位取或   |
| A^B    | A和B按位取异或 |
| ~A     | A按位取反      |

#### 常用函数

count(), max(), min(), avg(), sum()

#### Limit语句

```sql
select * from table_name limit 10;
```

#### Where语句

```sql
select * from table_name where column_name < 1000;
```

#### 比较运算符（Between/In/ Is Null）

| 操作符                  | 支持的数据类型 | 描述                                                         |
| ----------------------- | -------------- | ------------------------------------------------------------ |
| A=B                     | 基本数据类型   | 如果A等于B则返回TRUE，反之返回FALSE                          |
| A<=>B                   | 基本数据类型   | **如果A和B都为NULL，则返回TRUE，其他的和等号（=）操作符的结果一致，如果任一为NULL则结果为NULL** |
| A<>B, A!=B              | 基本数据类型   | A或者B为NULL则返回NULL；如果A不等于B，则返回TRUE，反之返回FALSE |
| A<B                     | 基本数据类型   | A或者B为NULL，则返回NULL；如果A小于B，则返回TRUE，反之返回FALSE |
| A<=B                    | 基本数据类型   | A或者B为NULL，则返回NULL；如果A小于等于B，则返回TRUE，反之返回FALSE |
| A>B                     | 基本数据类型   | A或者B为NULL，则返回NULL；如果A大于B，则返回TRUE，反之返回FALSE |
| A>=B                    | 基本数据类型   | A或者B为NULL，则返回NULL；如果A大于等于B，则返回TRUE，反之返回FALSE |
| A [NOT] BETWEEN B AND C | 基本数据类型   | 如果A，B或者C任一为NULL，则结果为NULL。如果A的值大于等于B而且小于或等于C，则结果为TRUE，反之为FALSE。如果使用NOT关键字则可达到相反的效果。 |
| A IS NULL               | 所有数据类型   | 如果A等于NULL，则返回TRUE，反之返回FALSE                     |
| A IS NOT NULL           | 所有数据类型   | 如果A不等于NULL，则返回TRUE，反之返回FALSE                   |
| IN(数值1, 数值2)        | 所有数据类型   | 使用 IN运算显示列表中的值                                    |
| A [NOT] LIKE B          | STRING 类型    | B是一个SQL下的简单正则表达式，如果A与其匹配的话，则返回TRUE；反之返回FALSE。B的表达式说明如下：‘x%’表示A必须以字母‘x’开头，‘%x’表示A必须以字母’x’结尾，而‘%x%’表示A包含有字母’x’,可以位于开头，结尾或者字符串中间。如果使用NOT关键字则可达到相反的效果。 |
| A RLIKE B, A REGEXP B   | STRING 类型    | B是一个正则表达式，如果A与其匹配，则返回TRUE；反之返回FALSE。匹配使用的是JDK中的正则表达式接口实现的，因为正则也依据其中的规则。例如，正则表达式必须和整个字符串A相匹配，而不是只需与其字符串匹配。 |

2）案例实操

```sql
select * from table_name column_name = column_val;
select * from table_name column_name is null;
select * from table_name column_name between column_val1 and column_val2;
select * from table_name column_name in (column_val1, column_val2);
```

Like / Rlike(正则)

> %代表匹配多个, _代表匹配一个

#### 逻辑运算符（And/Or/Not）

| 操作符 | 含义   |
| ------ | ------ |
| AND    | 逻辑并 |
| OR     | 逻辑或 |
| NOT    | 逻辑否 |

```sql
select * from table_name column_name > column_val1 and column_name < column_val2;
select * from table_name column_name = column_val1 or column_name = column_val2;
select * from table_name column_name not in (column_val1, column_val2);
```

### 分组

#### Group By语句

> 一般和聚合函数一起使用

```sql
select job, max(sal) as max_sal from emp group by job;
select job, avg(sal) as avg_sal from  emp group by job;
```



#### Having语句

### Join语句

* 等值Join
* 表的别名
* 内连接
* 左外连接
* 右外连接
* 满外连接
* 多表连接

### 排序

* 区内排序(Sort By)
* 全局排序(Order By)
* 按照别名排序
* 多个列排序



#### 每个MapReduce内部排序-Sort By

```sql
select * from emp sort by empno desc;

insert overwrite local directory '/opt/module/datas/result' select * from emp sort by deptno desc;
```

#### 全局排序Order By

#### 分区Distribute By

一般配合sort by使用(分区了不排序没什么意义)

```sql
insert overwrite local directory '/opt/module/datas/distribute-result' select * from emp distribute by deptno sort by empno desc;
```

#### Cluster By

> 当distribute by和sorts by字段相同时，可以使用cluster by方式。
>
> cluster by clumon1 == distribut by clumon1 sort by clumon1
>
> cluster by除了具有distribute by的功能外还兼具sort by的功能。但是排序只能是升序排序，不能指定排序规则为ASC或者DESC。

```sql
select * from emp cluster by deptno;
select * from emp distribute by deptno sort by deptno;
```



### 分桶及抽样查询

* 分桶表数据存储
* 分桶抽样查询

其他常用查询函数

* 空字段赋值NVL()



#### CASE WHEN

```sql
case column_name 
	when 'column_val' 
		then val_1 
		else val_2 
end
```

```sql
select dept_id, 
sum(case sex when '男' then 1 else 0 end) male_count,
sum(case sex when '女' then 1 else 0 end) female_count
from emp_sex
group by dept_id;
```



#### 行转列

> 一列中多行转一行

* CONCAT(string A/col, string B/col…)
* CONCAT_WS(separator, str1, str2,…):
* COLLECT_SET(col)

````sql
select t.base, concat_ws('|', collect_set(t.name))
from (select name, concat(constellation, ',', blood_type) base from person_info) t
group by t.base
````



#### 列转行

* EXPLODE(col)：将hive一列中复杂的array或者map结构拆分成多行。
* LATERAL VIEW

> 用法：LATERAL VIEW udtf(expression) tableAlias AS columnAlias
>
> 解释：用于和split, explode等UDTF一起使用，它能够将一列数据拆成多行数据，在此基础上可以对拆分后的数据进行聚合。

```sql
select
    movie,
    category_name
from 
    movie_info lateral view explode(category) table_tmp as category_name;
```



#### 窗口函数

* OVER()：指定分析函数工作的数据窗口大小，这个数据窗口大小可能会随着行的变而变化
  * CURRENT ROW：当前行
  * n PRECEDING：往前n行数据
  * n FOLLOWING：往后n行数据
  * UNBOUNDED：起点，UNBOUNDED PRECEDING 表示从前面的起点， UNBOUNDED FOLLOWING表示到后面的终点
* LAG(col,n)：往前第n行数据
* LEAD(col,n)：往后第n行数据
* First_value
* NTILE(n)：把有序分区中的行分发到指定数据的组中，各个组有编号，编号从1开始，对于每一行，NTILE返回此行所属的组的编号。注意：n必须为int类型





#### Rank

## 函数

### 系统内置函数

```shell
hive> show functions;
hive> show functions like 'xpath*';
hive> desc function upper;
hive> desc function extended upper;
```

### 自定义UDF函数(一对一)

* 编写代码
  * 继承UDF
  * 重写方法evaluate
* 打 jar 包
* 放到 lib 下
* hive 中添加 jar 包
* 定义函数
* 调用函数

```xml
<!--添加hive依赖-->
<dependency>
    <groupId>org.apache.hive</groupId>
    <artifactId>hive-exec</artifactId>
    <!--<version>${hive.version}</version>-->
    <version>1.2.1</version>
</dependency>
```



```shell
> cp hivefunction-1.0-SNAPSHOT.jar /opt/module/hive/lib
hive (gmall)> add jar /opt/module/hive/lib/hivefunction-1.0-SNAPSHOT.jar;
# 创建临时函数 永久函数在 hive-site.xml 中配置
hive (gmall)> create temporary function base_analizer as 'com.ishibin.udf.BaseFieldUDF';
hive (gmall)> create temporary function flat_analizer as 'com.ishibin.udtf.EventJsonUDTF';
```



### 自定义UDTF函数(一对多)

- 编写代码
  - 继承GenericUDTF
  - 重写方法initialize/process/close
- 打 jar 包
- 放到 lib 下
- hive 中添加 jar 包
- 定义函数
- 调用函数



## 调优



### 表的优化

#### 动态分区调整

```shell
set hive.exec.dynamic.partition=true # 默认
```

