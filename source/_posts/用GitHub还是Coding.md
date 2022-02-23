---
title: 静态Pages部署用GitHub还是Coding
date: 2019-12-03 16:34:11
categories: Website
tags: Website
---



<!---more--->

静态页面部署，放到GitHub Pages，稳定&慢；放到Coding，快&挂过好几次。

# 解决方案

最终选择，国内线路解析到Coding，其余解析到GitHub。

在DNSpod如下配置即可：

![dns](https://0pic.oss-cn-beijing.aliyuncs.com/dns_cname.png)



# coding 申请SSL错误

这里有个小坑，就是coding的Pages服务，想开启https，需要先关闭解析到github的那条记录。成功开启https后再启用即可。