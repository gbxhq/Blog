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

**修改mysql配置文件（修改完重启服务）**

### Win下修改my.ini

```mysql
sql_mode='STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION'
#sql_mode='STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION'
```

### Linux

在my.cnf[mysqld]下添加

```mysql
sql-mode=ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION  
```

### MacOS

在MacOS中默认是没有my.cnf 文件，如果需要对MySql 进行定制，拷贝/usr/local/mysql/support-files/目录  
中任意一个.cnf 文件。笔者拷贝的是my-default.cnf，将它放到其他目录，按照上面修改完毕之后，更名为  
my.cnf，然后拷贝到/etc目录再重启下mysql就大功告成了。