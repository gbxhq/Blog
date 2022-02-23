---
title: Hexo使用问题总结
date: 2018-11-28 09:47:29
categories: Website
tags: Hexo
---

汇总一下Hexo遇到的问题，以及以后出现问题都会更新到这里

<!---more--->

# 独立贴

- [插图问题](../HexoPic)
- [在Git仓库设置一个分支推送源码，主分支负责展示](../Hexo_set_branch)
- 有时候想传一个静态的HTML页面直接放在Source文件夹，不想被`Hexo g`的时候渲染，怎么办呢？
- [Hexo渲染设置例外](../Hexo_set_extral)
- [Hexo同时推送到多个仓库](../Hexo01/#toc-heading-11)

# 小问题

## `DeprecationWarning: fs.SyncWriteStream is deprecated.`

解决，`/你的Hexo根目录/node_modules/hexo-admin/node_modules/hexo-fs/lib/fs.js`这个文件，打开，
718行:`exports.SyncWriteStream = fs.SyncWriteStream;` //注释掉 。
完工

## unknown block tag: xx

Hexo还真是脆弱啊。报错信息是这样的：

![](https://0pic.oss-cn-beijing.aliyuncs.com/20190415150313.png)

可以看到 关键的报错语句是 unknown block tag: F

在某个文件的58行 54列

**关键是大哥你都定位不到是哪一个文件吗！给我来个(unknown path)**

于是我在网上搜。有个人写到：他在NexT这个主题有个自定义的标签是用`{` `%` 标签名 `%` `}`这种方式来建立的。我就去全文搜我的文件里出现的`{`  `%`  只有一处：是[这篇文章](../../Log/UsefulTips)

![](https://0pic.oss-cn-beijing.aliyuncs.com/20190415150459.png)

太脆弱啦。连放在代码里的都不行。真是服了。

删了就解决了。

