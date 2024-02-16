---
title: MySql记录
date: 2019-11-05 13:35:46
categories: Log
tags: MySQL
---



<!---more--->

# 导入导出

```mysql
mysqldump -u root -p123456 --all-databases
# 或指定数据库
mysqldump -u root -p123456 test
```




# Problems

-   [MySQL 连接出现 Authentication plugin 'caching_sha2_password' cannot be loaded](https://www.cnblogs.com/zhurong/p/9898675.html)

```mysql
mysql> ALTER USER 'root'@localhost IDENTIFIED BY '123' PASSWORD EXPIRE NEVER;
Query OK, 0 rows affected (0.03 sec)

mysql> ALTER USER 'root'@localhost IDENTIFIED WITH mysql_native_password BY '123';
Query OK, 0 rows affected (0.00 sec)

mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0.01 sec)
```

## [mysql5.7 timestamp默认值‘0000-00-00 00:00:00’报错](https://www.cnblogs.com/wang666/p/9186559.html)

```
# 修改全局
set @@global.sql_mode = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
# 修改当前
set @@sql_mode = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';

改完 check 一下，修改sql_mode(将上述查询到的sql_mode中的NO_ZERO_DATE和NO_ZERO_IN_DATE删除即可)
# 查看当前sql_mode
select @@sql_mode;
# 查看全局sql_mode
select @@global.sql_mode;
```

