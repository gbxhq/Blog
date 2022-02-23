---
title: Linux记录
date: 2018-7-26 15:02:45
categories: Log
tags: Linux
---

太多框架都是Linux跑起来更好了。给台式机装了个Ubuntu，用Macbook ssh登进去操作。这样一来纯命令行操作和服务器一样了。Ubuntu的那些`dpkg` `tar` 的常用命令都得好好记一下了。

<!---more--->

# Linux

## 命令加不加"-"

1.单- 和双- -的区别
1.1 参数前单-表示后面参数为字符形式，如tar -zxvf；
1.2 参数前加- - 表示后面参数为单词，如rm - -help；

2.加-和不加-的区别
在这里插入代码片加不加-执行命令的结果是相同的，区别主要涉及Linux风格，System V和BSD。
2.1 参数前不加-属于System V风格；
2.2 加-属于BSD风格。
　　两种风格的区别主要为：
　　系统启动过程中 kernel 最后一步调用的是 init 程序，init 程序的执行有两种风格，即 System V 和 BSD。
　　System V 风格中 init 调用 /etc/inittab，BSD 风格调用 /etc/rc，它们的目的相同，都是根据 runlevel 执行一系列的程序。

## 命令记录

- 切换到root `sudo su`

- 退出：ctrl+D或`exit`或 `logout`

- `cp` 复制文件夹记得 `-r` 递归地复制

- **赋权限：**
  `chmod -R 755 /home/fb`

  **赋所有者权限**
  `chown -R root:root /home/fb`

  `-R`是递归整个文件夹
  
- 软链接：

  ```shell
  ln -s /usr/local/python3/bin/pip3 /usr/bin/pip3
  ```

## 添加用户

- 创建root用户

  ```shell
  useradd zoey #建用户
  passwd zoey #改密码
  ```

  给root权限

  修改/etc/passwd文件，找到如下有用户名的行，把用户ID修改为0

  ![](https://0pic.oss-cn-beijing.aliyuncs.com/ubuntuuserroot.png)

- 给某个用户换成zsh:

  `chsh -s /bin/zsh/ zoey`

## 定时任务

`crontab [-u username] [-l|-e|-r]`

参数：

​	-u: 只有root才能进行这个任务，也即帮其他用户新建/删除crontab工作调度;

​	-e: 编辑crontab 的工作内容;

​	-l: 查阅crontab的工作内容;

​	-r: 删除所有的crontab的工作内容，若仅要删除一项，请用-e去编辑。

具体使用的例子，看菜鸟教程给的[这些实例](https://www.runoob.com/w3cnote/linux-crontab-tasks.html)就差不多了。

# 后台任务

## `nohup`的方式

#### 1、`nohup command &`

例如 `nohup jupyter notebook & `实现在后台不挂起地启动`jupyter`任务，关闭终端，仍还运行，`nohup` 指的是不挂起，而&是后台运行，默认情况会在当前目录生成`nohup.out`，记录原本在控制台的输出情况

#### 2、找到进程PID(关闭在前面后台执行的进程的步骤，首先找到其进程PID)

```
ps -ef | grep xxxx1
```

`ps -ef`查看本机所有的进程；`grep xxxx`代表过滤找到条件`xxxx`的项目

#### 3、kill掉进程

```
kill -9 具体的PID
```

用这个方法时，我遇到一个问题就是我的Python代码里用`embed()`这一句来阻塞进程转到ipython，这样会和这种后台运行的方式冲突，或许是日志没法完成。具体解决方法没找到，但是找到了下面这种后台运行的方法：

## screen的方式

先`screen -S name`然后把程序跑起来。然后`ctrl+a` 然后按 `d`

完事~

### 常用操作

screen 创建一个新shell

Ctrl +a 然后d 退出当前shell

Ctrl +a 然后k 杀死当前shell

screen -ls 查看正在进行的子shell

screen -r [session name] 返回这个screen

### 杀死方法：
方法一：
`screen -X -S [session # you want to kill] quit`
比如

```shell
[root@localhost ~]# screen -ls
There are screens on:
        9975.admin   (Detached)
        4588.scheduler    (Detached)

[root@localhost ~]# screen -X -S 4588 quit
[root@localhost ~]# screen -ls
There is a screen on:
        9975.pts-0.localhost    (Detached)
1 Socket in /var/run/screen/S-root.
```

可以看到，4588会话已经没有了。

方法二：
激活screen：

` screen -r session_name`
 并利用exit退出并kiil掉session。

### 乱码问题

解决办法：在 `~/.screenrc` 里加入如下设置:

```
#编码
defutf8 on
defencoding utf8
encoding UTF-8 UTF-8
```


# 安装SFTP

1.安装sftp服务

`sudo apt-get install openssh-server`

2.修改配置文件

`sudo vim /etc/ssh/sshd_config`

```
##下面这行注释掉
#Subsystem sftp /usr/libexec/openssh/sftp-server
##后面加入
Subsystem sftp internal-sftp

找到PermitRootLogin no一行，改为PermitRootLogin yes   让root用户可以登录SFTP
```

3.重启sshd服务

`service ssh restart`

# Package Management Problems

## yum

`File "/usr/bin/yum", line 30 except KeyboardInterrupt, e:`

解决方法：

修改`/usr/bin/yum`文件中的第一行为`#!/usr/bin/python2.7`

## apt-get

`apt-get install E: 无法定位软件包`

在etc/ap的sources.list 添加镜像源

`deb http://archive.ubuntu.com/ubuntu/ trusty main universe restricted multiverse`

然后` sudo apt-get update ` 

接着安装就可以了

# MySQL

进入mysql

`mysql -u 用户名 root -p` 然后会让你输密码

不知道用户名密码：

etc/mysql 目录下的 debian.cnf 文件里

MySQL目录、默认的数据文件存储目录为/var/lib/mysql。

# Vim

vim都学了无数次了。但图形界面下我无法拒绝VS Code。这回不得不用vim的时候，还是把该记的记一记吧。

重新拿起来这分曾经的[教程](../fun/vimtutor_cn)

- `:q!` 不保存退出

- `x` 删除

- `$` `0` `^ ` 定位到行尾、首

- `w` `e` 下一个单词首/尾

- `G` `gg` `Ctrl+g ` 文件末行/首行 定位信息

- `u` `U` `Ctrl+R` 恢复/恢复整行 撤销恢复

- `p ` 粘贴

- `r` 代替

- `c/d`+`数字`+`对象`  更改/删除

- `/` `?` n/N  搜索   CTRL-O 使你返回到以前的位置，CTRL-I 回到以后的位置

- `%`  放在括号上可以匹配括号

- `:s/a/b`  替换a和b
  
   ` :#,#s/old/new/g `   其中，#,#是要更改的行号的范围
    ` :%s/old/new/g`      更改全文件中的所有事件。
   
    ` :%s/old/new/gc`      更改全文件中的所有事件,并给出替换与否的提示。  
   
- `yw`复制单词  `yy`复制整行 前面加数字是复制n行

### vim中文乱码

 编辑~/.vimrc文件，加上如下几行：

   set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
   set termencoding=utf-8
   set encoding=utf-8

# SSL

参考文章：<https://www.jianshu.com/p/e321cc362e5d>

报错：`ImportError: No module named 'requests.packages.urllib3'`

解决：`pip install --upgrade --force-reinstall 'requests==2.6.0' urllib3`