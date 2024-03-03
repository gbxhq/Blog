---
title: Docker目录/var/lib/docker/containers文件太大
date: 2024-02-24 14:18:04
tags:
---

参考 [Docker目录/var/lib/docker/containers文件太大 - 人艰不拆_zmc - 博客园 (cnblogs.com)](https://www.cnblogs.com/zhangmingcheng/p/13960496.html)

#  单次删除的方法

```shell
root@alpha-be59153b40:~# docker ps -aq
--- 列出所有的容器 ---
a620657d1651
a6af43795580
1a8facf236fb
24af525d53bc

root@alpha-be59153b40:~# docker inspect --format='{{.LogPath}}' a6af43795580
--- 查看容器下的日志文件 ---
/var/lib/docker/containers/a6af43795580293adacdd5ed3e48b5a34733dcbafadef778f1e0877ea8df6578/a6af43795580293adacdd5ed3e48b5a34733dcbafadef778f1e0877ea8df6578-json.log


root@alpha-be59153b40:~# truncate -s 0 /var/lib/docker/containers/a6af43795580293adacdd5ed3e48b5a34733dcbafadef778f1e0877ea8df6578/a6af43795580293adacdd5ed3e48b5a34733dcbafadef778f1e0877ea8df6578-json.log
--- 把这个文件大小设置成 0 ---
```

在这里也是学到了一个新的 Linux 命令：`truncate`

**truncate常用选项**

下面是truncate的常用选项：

```text
-c, --no-create --> 不创建任何文件
-o, --io-blocks --> 将大小视为存储块的数量，而不是字节
-r, --reference=RFILE --> 参考指定的文件大小
-s, --size=SIZE --> 按照指定的字节设置文件大小
```

把上面的三个命令合成一个：（把所有容器的 log 都删了）

docker ps -aq | xargs docker inspect --format='{{.LogPath}}' | xargs truncate -s 0





# 永久生效的方法

### 控制容器日志大小

以上只是临时解决的方式，最好是创建容器时就控制日志的大小。

#### 运行时控制

启动容器时，我们可以通过参数来控制日志的文件个数和单个文件的大小

```
# max-size 最大数值``# max-file 最大日志数``$ docker run -it --log-opt max-size=10m --log-opt max-file=3 redis
```

一两个容器还好，但是如果有很多容器需要管理，这样就很不方便了，最好还是可以统一管理。

### 全局配置

创建或修改文件 `/etc/docker/daemon.json`，并增加以下配置

```
{``  ``"log-driver":"json-file",``  ``"log-opts":{``    ``"max-size" :"50m","max-file":"3"``  ``}``}
```

max-size=50m，意味着一个容器日志大小上限是50M， 
max-file=3，意味着一个容器有三个日志，分别是id+.json、id+1.json、id+2.json。可以存在的最大日志文件数。如果超过最大值，则会删除最旧的文件。**仅在max-size设置时有效。默认为5。

随后重启 Docker 服务

```
sudo systemctl daemon-reload``sudo systemctl restart docker
```

不过已存在的容器不会生效，需要重建才可以
