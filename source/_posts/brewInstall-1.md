---
title: brew安装 redis 和 mysql
date: 2020-11-23 22:16:36
categories:
tags:
---



<!---more--->

# mysql

1. 安装homebrew
2. brew install mysql 安装mysql

安装完成之后，可以运行命令启动mysql服务

```
mysql.server start
```

然后输入命令设置密码

```
mysql_secure_installation
```

设置完成之后，进入mysql服务

```
mysql -uroot -p
Enter password:
```

# redis

