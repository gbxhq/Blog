---
title: Hexo 渲染时设置例外
date: 2018-04-01 11:21:41
categories: Website
tags: Hexo
---

由于网络书签同步总是不方便，我把常用的网址做成了一个导航站[炫猿](http://oo1.win) 这个站是纯HTML配合Bootstrap写的，所以没有任何后台。但当我把它整个拖到Hexo里时，Hexo就把它“毁了”。So,有了这篇文章。

<!---more--->

# 目前使用的方法：
在HTML文件前增加
layout: false
---

来，体验一下：
[炫猿](/oo1)

# 方法二：设置例外目录
假设你的Source文件夹里面有个Demo目录，要忽略Demo目录下的所有html页面，可以通过在`_config.yml`设置skip_render来忽略的目录，具体如下：
`skip_render: Demo/*.html`

文件匹配是基于正则匹配的，更复杂的情况如下

1.单个文件夹下全部文件：`skip_render: demo/*`

2.单个文件夹下指定类型文件：`skip_render: demo/*.html`
3.单个文件夹下全部文件以及子目录:`skip_render: demo/**`

4.多个文件夹以及各种复杂情况：

```
skip_render:
    - 'demo/*.html'
    - 'demo/**'
```
