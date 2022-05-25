---
layout: wiki  # 使用wiki布局模板
wiki: MySQL # 这是项目名
title: MySQL基础
---

# 基本概念

## 数据类型

数值类型
有包括 TINYINT、SMALLINT、MEDIUMINT、INT、BIGINT，分别表示 1 字节、2 字节、3 字节、4 字节、8 字节的整数类型。

1）任何整数类型都可以加上 UNSIGNED 属性，表示无符号整数。

2）任何整数类型都可以指定长度，但它不会限制数据的合法长度，仅仅限制了显示长度。

还有包括 FLOAT、DOUBLE、DECIMAL 在内的小数类型。

字符串类型
包括 VARCHAR、CHAR、TEXT、BLOB。

注意：VARCHAR(n) 和 CHAR(n) 中的 n 并不代表字节个数，而是代表字符的个数。

日期和时间类型
常用于表示日期和时间类型为 DATETIME、DATE 和 TIMESTAMP。

尽量使用 TIMESTAMP，空间效率高于 DATETIME。
