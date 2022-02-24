---
title: 在线编辑Hexo的最佳方案
date: 2022-02-24 18:17:09
categories: Website
tags: Hexo
---

网上看Hexo的在线编辑方案，主流的有两种：

1. HexoPlusPlus
2. 语雀

这两个方案大家百度一下都有教程。

但是，太麻烦了。如果你也是使用了自动化部署Hexo的方案（就是推送源文件到仓库，然后借助Github Actions或 vercel这种自动部署的方案），为啥不用Github的官方在线编辑器呢？

只需要在仓库界面按一下 . （句号键） 或者 把github.com 改成 github.dev，
就能在线编辑仓库的文件。我们在对应的文件夹新建、删除、修改后，commit一下就好了。

注意，在线编辑器，commit后是不需要push的哦。