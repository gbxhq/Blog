---
title: Redis学习
date: 2022-02-27 16:12:14
tags:
---

# Redis

开源、C、k-v、单线程

特征

- 速度快 10w_QPS
- 多数据结构
- 持久化
- 功能丰富
- 高可用

```shell
keys * #O(n)级别，不要在生成环境用。单线程会扫描、形成阻塞
# 用 scan 看所有的 key
scan 0
# scan 返回游标 0 时说明遍历完了
127.0.0.1:6379> scan 0 match rank* count 1
1) "4"
2) 1) "rank:m"
type key # 数据结构
OBJECT encoding key # 编码
```

## 基本数据类型内部编码

### String

- raw <39
- int
- embstr >39

### Hash

- hashtable
- ziplist

### List

- linkdelist
- ziplist

### Set

- hashtable
- intset

### Zset

- skiplist
- ziplist

