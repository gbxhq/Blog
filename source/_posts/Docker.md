---
title: Docker
date: 2022-05-09 11:38:05
tags: [Docker]
---

## 换源

修改docker镜像源，docker默认的源为国外官方源，下载速度较慢，可改为国内

进入`/etc/docker`，查看有没有`daemon.json`。这是docker默认的配置文件。如果没有新建

```shell
❯ sudo vim /etc/docker/daemon.json
# 修改为一下内容
{
  "registry-mirrors": ["https://registry.docker-cn.com","http://hub-mirror.c.163.com"]
}
# 重启 docker：
❯ sudo service docker restart
```

---

Docker国内源说明：
Docker 官方中国区：https://registry.docker-cn.com
网易：http://hub-mirror.c.163.com
中国科技大学：https://docker.mirrors.ustc.edu.cn
阿里云：https://pee6w651.mirror.aliyuncs.com