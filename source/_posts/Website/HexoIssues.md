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

