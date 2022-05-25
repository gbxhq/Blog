---
title: UbuntuSSH
date: 2022-05-09 10:56:49
tags: [Linux,Ubuntu]
---

# 切换源

装好 Ubuntu 第一步先换个国内源，比如阿里：

https://developer.aliyun.com/mirror/ubuntu

在这里对着文档换吧。人家给提供了各种版本 ubuntu 的替换文本，无脑复制过去即可

# 开启 ssh

```shell
dpkg -l | grep ssh # 看看有木有 ssh 服务

ps -e | grep ssh # 看 ssh 服务端有没有启动

# 启动
sudo /etc/init.d/ssh start 或 sudo service ssh start
```

启动出现：

sshd: no hostkeys available -- exiting.

解决：

`ssh-keygen -A`