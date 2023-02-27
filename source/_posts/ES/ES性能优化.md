---
title: ES 优化
date: 2020-01-19
categories: ElasticSearch
tags: [ElasticSearch,ES]
---


## **3.5 使用过滤器上下文**

![img](https://ask.qcloudimg.com/http-save/751946/wi6c7wie28.jpeg?imageView2/2/w/1620)

原先使用的是query查询子句，优化后改成filter过滤器。 query查询子句用于回答“这个文档与此子句相匹配的程度”，而filter过滤器子句用于回答“这个文档是否匹配这个子句”，Elasticsearch只需要回答“是”或“否”，不需要为过滤器子句计算相关性分数，而且过滤器结果可以缓存。 查询在Query查询上下文和Filter过滤器上下文中，执行的操作是不一样的：

1. 查询上下文： 在查询上下文中，查询会回答这个问题——“这个文档匹不匹配这个查询，它的相关度高么？” 如何验证匹配很好理解，如何计算相关度呢？ES中索引的数据都会存储一个_score分值，分值越高就代表越匹配。另外关于某个搜索的分值计算还是很复杂的，因此也需要一定的时间。 查询上下文 是在 使用query进行查询时的执行环境，比如使用search的时候。
2. 过滤器上下文： 在过滤器上下文中，查询会回答这个问题——“这个文档匹不匹配？” 答案很简单，是或者不是。它不会去计算任何分值，也不会关心返回的排序问题，因此效率会高一点。 过滤上下文 是在使用filter参数时候的执行环境，比如在bool查询中使用Must_not或者filter。 另外，过滤器上下文中，查询的结果可以被缓存。

filter速度要快于query，filter是不计算相关性的，同时可以cache。所以尽可能使用过滤器上下文（Filter）替代查询上下文（Query）。 因为业务场景并不需要计算相关性分数，所以改用filter。

![img](https://ask.qcloudimg.com/http-save/751946/ky4u1go6r1.jpeg?imageView2/2/w/1620)