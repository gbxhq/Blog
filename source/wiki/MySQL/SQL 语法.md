---
layout: wiki  # 使用wiki布局模板
wiki: MySQL # 这是项目名
title: SQL语法基础
order: 20
---

《必知必会》整理

# 了解SQL

Structured Query Language 结构化查询语言

## 基础语法

> |   表示 在可选项中选择一个
>
> [ ] 表示这个参数可选

- ALTER TABLE

更新  已存在  表  的  结构

```sql
ALTER TABLE table
(
    ADD|DROP column datatype [NULL|NOT NULL] [CONSTRAINTS],
    ADD|DROP column datatype [NULL|NOT NULL] [CONSTRAINTS],
    ...
);
```

- COMMIT

将 事务 写入 数据库。

```sql
COMMIT [TRANSACTION];
```

- CREATE INDEX

在 一个或多个 列 上 创建 索引。

```sql
CREATE INDEX i ndexname
ON tablename (column, ...);
```

- CREATE PROCEDURE

创建存储过程。 Oracle 使用的语法稍有不同。

```sql
CREATE PROCEDURE procedurename [parameters] [options]
AS
SQL statement;
```

- CREATE TABLE 

创建 新数据库表。

```sql
CREATE TABLE tablename
(
    column datatype [NULL INOT NULL] [CONSTRAINTS] ,
    column datatype [NULL INOT NULL] [CONSTRAINTS] ,
);
```

- CREATE VIEW

用来创建 一个或多个 表上的新视图。

```sql
CREATE VIEW viewname AS
SELECT columns, 。。。
FROM tables, ...
[WHERE ...]
[GROUP BY ...]
[HAVING ...];
```

- DELETE

从表中 删除 一行或多行。

```sql
DELETE FROM tablename
[WHERE ...];
```

- DROP

永久地删除数据厍对象

```sql
DROP INDEX | PROCEDURE | TABLE | VIEW
indexname | procedurename | tablename | viewname;
```

- INSERT

为表添加一行。

```sql
INSERT INTO tablename [(co1umns, ...)]
VALUES(values, ..);
```

- INSERT SELECT 

将SELECT的结果插人到一个表

```sql
INSERT INTO tablename [ (columns,)]
SELECT columns ， ... FROM tablename , ...
[WHERE ...];
```

- ROLLBACK

用于撤销-一个事务块。

```sql
ROLLBACK [TO savepointname];
或
ROLLBACK TRANSCATION;
```

- SELECT

用于从一个或多个表(视图)中检索数据。

```sql
SELECT columnname ，...
FROM tablename ， ...
[WHERE ...]
[UNION ...]
[GROUP BY ...]
[HAVING ...]
[ORDERBY ...];
```

- UPDATE

更新表中的一行或多行。

```sql
UPDATE tablename
SET columname = value , ...
[WHERE ...];
```

## 数据类型

### 字符串

- CHAR
    - 1-255个字符的定长字符串。长度必须在创建时规定。
- NCHAR
    - CHAR的特殊形式。用来支持多字节或Unicode字符。
- TEXT (也称 LONG\MEMO\VARCHAR)
    - 变长文本
- NVARCHAR
    - TEXT的特殊形式。

### 数值

- BTT 单个二进制位
- DECIMAL 定点、或浮点可变的浮点值
- FLOAT 浮点值
- INT 4字节整数
- REAL 4字节浮点
- SMALLINT 2字节整数
- TINYINT 1字节，0-255的整数

> 多数DMBS支持货币数据类型 `MONEY/CURRENCY` 有特定取值范围的DECIMAL类型。更适合存货币值

### 日期时间

- DATE 日期
- DATETIME 日期时间
- SMALLDATETIME 日期时间精确到分
- TIME 时间
  
# 检索数据

- SELECT * `*`选择所有
- SELECT DISTINCT name `DISTINCT` 结果去重

## 限制结果

返回前5行
- MySQL PostgreSQL SQLite MariaDB
    SELECT xxx FROM xxx LIMIT 5;

- 进阶：LIMIT 后跟两个参数

    ```sql
    LIMIT 10,2 -- 从第10个往后输出2个。输出的是 11 和 12
    ```


# 注释

```sql
#可以这样
SELECT xxx -- 可以这样
/*也可以
这样*/
```

# 排序检索数据

```sql
SELECT id,name,grade
FROM Stu
ORDER BY grade,name; --当出现并列分数则按姓名排列
#也可以写成：
ORDER BY 3,2; --3就是grade 2就是name 。对应于SELECT第一句
```

**重要：应保证 ORDER BY 子句是 SELECT 语句中的 *最后一个* 子句 ，否则会报错！**

## 排序方向：

默认升序[A~Z] ，改降序：
```sql
ORDER BY grade DESC
#多个属性想降序，必须对每一列都进行声明！
ORDER BY grade DESC, name  --name就是升序(ASC)排列
```

# 过滤数据

WHERE 子句操作符：

| = 等于          | > 大于 | >= 或 !< 大于等于  | BEWTEEN AND在指定值之间 |
| --------------- | ------ | ------------------ | ----------------------- |
| <> 或 != 不等于 | < <=   | <= 或  !> 小于等于 | IS NULL 为NULL          |

# 高级过滤

## 组合WHERE子句

用AND或OR组合子句

## AND和OR的顺序

AND级别比OR高。 如果需要改变顺序，请加括号：

```sql
WHERE (name = 'XiaoMing' OR name = 'XiaoHong')
	AND grade = 100;
```

## IN操作符

```sql
WHERE id IN ('001','002');
#等价于OR
WHERE id = '001' OR id = '002';
```

IN的优点：

简单直观。比OR更快。

可以包含其他SELECT子句后面会介绍。

## NOT 操作符

否定后面的条件。不单独使用。

```SQL
WHERE NOT id = '01'
#等价于
WHERE id != '01'
```

那为啥还要用NOT呢？

在复杂的条件中，可以迅速找出 **不符合** 条件的

# 通配符过滤

使用谓词 `LIKE` 

- %通配符

表示任意字符出现任意次

```sql
WHERE name LIKE 'Xiao%'
#XiaoMing XiaoHong XiaoLiang就都被搜出来了
```

%可以匹配 0 个 1 个 多个字符（包括空格）。当然 ，并不会匹配NULL值

- _通配符

_只匹配一个字符

- []通配符

匹配字符集（仅SQL Server支持）从`[ ]`里取一个字符

```sql
WHERE name LIKE 'Xiao[MH]'  -- 匹配XiaoM和XiaoH
WHERE name LIKE 'Xiao[^MH]' -- 除了XiaoM和XiaoH所有的
```

## 通配符技巧

- 不要过度使用通配符。有其他操作符能达到目的应优先考虑其他。
- 通配符置于开始处，搜索起来是最慢的

---

**SELECT name + '(' + classId + ')'拼接字段**

就是合并列

```sql
#在SQL Server中 用 +
SELECT name + '(' + classId + ')'
#在DB2 Oracle PostgreSQL SQLite中 用 ||
SELECT name || '(' || classId || ')'
#在 MySQL MariaDB 中
SELECT Concat(name, ' (', classId, ')')
```

> TRIM 函数 去某个字段的空格
>
> LTRIM() 去掉字符左边的空格  RTRIM()右边   TRIM()两边

## 使用别名

拼接之后 AS newName 给新的字段用别名

## 算数计算

```sql
SELECT quantity, price, quantity*price AS Pay
```

# 函数

不同的sql还不一样名。不怎么通用。 P65 Mark

# 汇总数据

## 聚集函数

- AVG() 返回列的平均值

- COUNT()返回列的行数

  - COUNT(columnName) 对特定的列计数，忽略NULL值
  - COUNT( * ) 表中的行数计数。不论是不是NIULL都计数。

- MAX() MIN()

- SUM() 列值之和

  ```sql
  SELECT AVG(price) AS avg_price FROM xxx; --返回平均价格
  ```

## DISTINCT去重

```sql
SELECT AVG(DISTINCT price) AS avg_price
```

# 分组

GROPU BY和HAVING

## 不用GROUP BY

```sql
SELECT SUM(grade) AS 小明的总分 FROM Stu
WHERE name = '小明'；
```

但这时候如果还想看小红，还想看小亮的总分，总不能挨个都写到WHERE里。

## GROUP BY

```Sql
SELECT nmae, SUM(grade) AS 总分 FROM Stu
GROUP BY name;
```

- GROUP BY必须出现于WHERE之后 ORDER BY之前
- NULL也会被分成一组

## 过滤分组

WHERE过滤的只是行，看上去像是分组了。

如果想排除分组怎么办？（比如不看小丽的总分）

HAVING，支持所有WHERE操作符。语法相同。

> 差别：
>
> WHERE在分组前进行过滤，过滤掉的行不参与分组。
>
> HAVING再对分组后的结果过滤

# 子查询

## IN(SELECT)

用 IN 操作符 嵌套 SECLECT 查询

```sql
SELECT name FROM Stu
WHERE grade IN (
    	SELECT grade FROM Stu
    	WHERE grade > 60
	);
```

- 作为子查询的SELECT子句只能是单列
- 多次嵌套会影响效率

## 作为计算字段

当做返回值

```sql
SELECT name, (
    	SELECT COUNT(*)
    	FROM tab1
    	WHERE tab1.id = tab2.id
	) AS quantity
FROM tab2
```

- 完全限定列名

  两个表里都已id字段，要加前缀的

- 后面学习的JOIN代替上面的方法更有效

# 联结表

## 笛卡尔积

WHERE条件子句不写，直接

```sql
SELECT id,name，grade
FROM tab1,tab2
```

## 内联结 等值联结

```sql
SELECT id, name, grade
FROM Stu INNER JOIN Quit
	ON Stu.id = Quit.id
```

等价于

```sql
SELECT id, name, grade
FROM Stu, Quit
WHERE Stu.id = Quit.id
```

只不过关键词 WHERE 换成 ON

> ANSI SQL规范首选 INNER JOIN 语法
>
> 第二种写法是很Low的哦

但第二种写法还可以联结多个表，当然性能会下降

# 高级联结

## 表的别名

使用AS ，注意，也可以在FROM之前的SELECT中使用哦

```sql
SELECT A.*, B.name
FROM tab1 AS A, tab2 AS B
```

---

除了内联结（等值联结） 还有三种其他联结

## 自联结

假如查询和小明考了一样分数的同学们的名字，用嵌套查询的方式可以这样：

```sql
SELECT name FROM Grade
WHERE grade = (SELECT grade FROM Grade 
              WHERE name = '小明')
```

用自联结就可以这样：

```sql
SELECT name
FROM Grade AS g1, Grade AS g2
WHERE g2.name = '小明' 
	AND g1.grade = g2.grade
```

> 一般情况下使用[[联结]]比使用[[子查询]]快得多。
>
> 当然也可以试用两种方法，以确定哪种性能更好

## 自然联结

排除多次出现。每一列只返回一次。

一般通过对一个表使用通配符(SELECT *)，对其他表使用 明确的 子集来完成。

比如查询同学的成绩。学号的那张表肯定是唯一的，就可以

```sql
SELECT S.* , xxxxxx
FROM Stu AS S, tab2, xxxxx
```

## 外联结

左外联结和右外联结，

有时候 表1 和 表2 联结，并不能出现一一对应的情况，这时候以表一的数据为准，【表一中有，表二中没有的】 联结之后填充NULL值。就是左外联结。 关键词是

```sql
FROM tab1 LEFT OUTER JOIN tab2
	ON 条件
```

右外联结 就是 `RIGHT OUTER JOIN`

> **全外联结**  `FULL OUTER JOIN`
>
> 带上左右不关联的行全部返回。但是 MySQL  SQLite MariaDB等不支持 FULL OUTER JOIN 的 语法



# 组合查询

用 UNION 联结两条 SELECT

```sql
SELECT name,id FROM xxx
WHERE id IN ('001','002','003')
UNION
SELECT name,id FROM xxx
WHERE xxx
```

> 上面的例子当然可以用 WHERE 配合 OR 来组合条件完成，
>
> 但是当遇到复杂的过滤条件， UNION 处理起来更简单。
>
> 性能上的差别，最好是测试以确定更优。

- Note：列的数据类型必须完全兼容。上面我给的例子是完全相同的两个列，实际上，只要类型兼容即可（即 必须是DBMS可以隐含转换的类型）。

## 重复的行

UNOIN 默认会去除重复行。（看上去效果和使用了多个WHERE子句一样）

如果想返回所有行。请使用 `UNOIN ALL` 关键词。实现合并两个集合而不去重。这样可以解决【用WHERE会去重】的问题。

> **其他UNION**
>
> 既然有并集。就还有 差集：`EXCEPT`    交集：`INTERSECT`
>
> 但实际上他们很少使用，因为可以用 联结  来得到结果

# 插入数据

学了这么久，查插删改一直在查，终于到了插了：

- 插入完整的行
- 插入行的一部分
- 插入查询的结果

## 插入完整的行

```sql
INSERT INTO tab1
VALUES('001','XiaoMing',99,Null,Null);
```

但是这种方法不安全。完全依赖列的顺序插入。表的结构变动后，迟早会出问题。更安全（麻烦）的方法：

```sql
INSERT INTO tab1(id,name,math,english,PE)
VALUES('001','XiaoMing',99,Null,Null);
```

## 插入部分行

就是说列名可以不写全。但必须满足以下某个条件：

- 该列定义 允许 NULL值
- 表定义中给出了默认值

## 插入检索的数据

```sql
INSERT INTO tab1(xxx,xxx,xxx)
SELECT xxx,xxx,xxx FROM xxx
```

其中INSERT 和 SELECT 的列名不要求匹配。插入只看位置。

## 从一张表复制到另一张表

```sql
SELECT *
INTO tabCopy -- 创建一张新表
FROM tab1
```

如果只是复制部分列，把 * 换成 列名

**MySQL  Oracle  PostgreSQL  SQLite**语法不同：

```sql
CREATE TABLE tabCopy AS
SELECT * FROM tab1;
```

# 删改

## 更新数据

```sql
UPDATE Stu
SET QQ = '123', WeChat = '123'
WHERE id = '001';
```

更新总是要以  要更新的 表名 开始。

会以 WHERE 子句结束，它告诉DBMS要更新哪一行。

**没有WHERE子句会更新所有行** 这不是我们所希望的

## 删除数据

```sql
DELETE FROM Stu
WHERE id = '001';
```

DELETE删除的是【行】。**一定要带上WHERE，不然就删了所有的行。**

> 如果想删除所有行，请使用 TRUNCATE TABLE ,它完成相同的工作速度 更快。

# 操作表

## 创建表

```sql
CREATE TABLE Stu
(
    id	CHAR(10)	NOT NULL,
    name	VARCHAR(254)	NOT NULL,
    avgGrade	DECIMAL(8,2)	NOT NULL	DEFAULT 0
);
```

[附录D](#附录D)展示了常见的数据类型

上述代码在MySQL上`varchar`必须替换为`text`

不指定`NOT NULL`， 则可以为空（`NULL`)

默认值(`DEFAULT`)比Null更好用，常用于日期和时间戳，如在MySQL上获取时间：`CURRENT_DATE()`

## 更新表

应在设计表的时候考虑未来可能的需求

```sql
ALTER TABLE Stu
ADD phone CHAR(20)
DROP COLUMN avrGrade;
```

增删了一列

> ALTER表前要备份。如果增加了，也许无法删除。如果删除了，也许无法恢复

## 删除表

```sql
DROP TABLE Stu
```

删除表没有确认也不能撤销。

如果该表是某个关系的组成成分，DBMS将阻止这条语句。这能防止意外删除。

## 重命名表

根据DBMS有所不同

# 使用视图

# 附录D 常见的数据类型

## 1.字符串

Q：定长和变长区别

A: 性能。处理定长比处理变长快得多；许多DBMS不允许变长列进行索引

| 类型                                    | 说明                                                         |
| --------------------------------------- | ------------------------------------------------------------ |
| CHAR                                    | 1~255的定长字符串 **长度必须在创建时规定**                   |
| NCHAR                                   | CHAR的特殊形式  用来支持多字节或Unicode字符（此类型的不同实现变化很大） |
| TEXT<br />（也称为LONG、MEMO或VARCHAR） | 变长文本                                                     |
| NVARCHAR                                | TEXT的特殊形式  用来支持多字节或Unicode字符（此类型的不同实现变化很大） |

> Notice：字符串的值 必须在 单引号内
>
> Note: 「不是数值的数字」要保存成字符串，如邮编01234如果保存成数值是1234，丢失一位。应作为字符串保存。

## 2.数值

| 类型     | 说明                             |
| -------- | -------------------------------- |
| BIT      | 0/1                              |
| DECIMAL  | 定点或精度可变的浮点数           |
| FLOAT    | 浮点数                           |
| INT      | 4字节整数 -2147483648~2147483647 |
| REAL     | 4字节浮点数                      |
| SMALLINT | 2字节整数 -32768~32767           |
| TINYINT  | 1字节整数 0~255                  |

> 多数DBMS支持 MONEY或CURRENCY，更适合存储货币的，有特定范围的DECIMAL

## 3.日期和时间

| 类型          | 说明                             |
| ------------- | -------------------------------- |
| DATE          | 日期                             |
| TIME          | 时间                             |
| DATETIME      | 日期时间                         |
| SMALLDATETIME | 日期时间，精确到分（无秒、毫秒） |

> NOTE: 不同的DBMS格式要参考具体文档

## 4.二进制

包含任何数据（图、多媒体、文档） 最不具兼容性

| 类型      | 说明                  |
| --------- | --------------------- |
| BINARY    | 定长二进制 255B~8000B |
| VARBINARY | 变长二进制 255B~8000B |
| RAW       | 定长二进制 最长255B   |
| LONG RAW  | 变长二进制 最长2GB    |

