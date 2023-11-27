---
title: MySQL JSON 类型使用
date: 2020-01-19
categories: MySQL
tags: [MySQL]
---

JSON 类型是从 MySQL 5.7 版本开始支持的功能，而 8.0 版本解决了更新 JSON 的日志性能瓶颈。如果要在生产环境中使用 JSON 数据类型，强烈推荐使用 MySQL 8.0 版本。

创建

插入 和 查询

```mysql
mysql> insert into xuanshan Values('{"day":8,"month":99,"week":66}',1);
Query OK, 1 row affected (0.00 sec)

mysql> select * from xuanshan;
+-------------------------------------+------+
| post                                | id   |
+-------------------------------------+------+
| {"day": 8, "week": 66, "month": 99} |    1 |
+-------------------------------------+------+
```

更新

JSON_SET(json_doc, path, val[, path, val] …) 完全抹掉

```mysql
mysql> update xuanshan set post=JSON_SET('{"day":1}','$.day',33);
Query OK, 1 row affected (0.00 sec)
Rows matched: 1  Changed: 1  Warnings: 0

mysql> select * from xuanshan;
+-------------+------+
| post        | id   |
+-------------+------+
| {"day": 33} |    1 |
+-------------+------+
1 row in set (0.00 sec)
```

1. json_insert就是向json中插入，如果不存在则插入，存在则忽略
2. json_replace就是替换json中的项，如果不存在则忽略，存在则替换
3. json_set结合前面俩个，存在则替换，不存在则插入
4. json_merge_patch多个json进行合并，相同键名，后面的覆盖前面的，如果值是对象，则递归进行处理
5. json_merge_preserve多个json进行合并，相同键名，则键值组成新的对象
6. json_remove移除掉json某一项