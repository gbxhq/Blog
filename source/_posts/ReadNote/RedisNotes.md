---
title: Redis记录
date: 2021-02-27 16:12:14
tags: Redis
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

## 操作

时间复杂度

### String

```redis
SETNX k v #存入一个不存在的 kv
MGET k #multi get
```

### Hash

Hash 的优缺点

缺点：不能过期

优点：省、归类

```redis
HSET
HSETNX
HMGET
HMSET
HGETALL k# hash-k 中所有 k-v
HLEN k# hash-k-中field 的数量
HINCRBY k field increment # has-k 中 field键 的值 +increment
```

### List

灵活

```redis
# L左 R 右 B 阻塞 ，没有元素则等待
BLPOP 
BRPOP
LRANGE key start stop #获取区间
```

### Set

```redis
SMEMBERS k # 别在生产环境 单线程
SPANDMEMBER k [cnt] # 列出 cnt 个
SPOP key [cnt] # 抽（删）cnt 个
```

```redis
SINTER k [k ...] #交集 共同好友
SINTERSTORE target key [k ...] # 交集存入 target
SUNION #并
SUNIONSTORE
SDIFF #差
SDIFFSTORE
```

### ZSET

把 SET 里操作的 S 改成 Z 雷同

```
ZRANGE k start stop [WITHSCORES] # 正序
ZREVRANGE k start stop [WITHSCORES] # 倒序
```

### Bitmaps

Bitmaps 只能设置标志位 0 或 1 

365天内，是否上过 2 次课

```redis
127.0.0.1:6379>
127.0.0.1:6379> SETBIT xuanshan 0 1 # 第 0 天标记为 1
(integer) 0
127.0.0.1:6379> SETBIT xuanshan 6 1
(integer) 0
127.0.0.1:6379> SETBIT xuanshan 364 1
(integer) 0
127.0.0.1:6379> STRLEN xuanshan
(integer) 46
127.0.0.1:6379> BITCOUNT xuanshan 0 365
(integer) 3
127.0.0.1:6379> BITCOUNT xuanshan 0 -1
(integer) 3
127.0.0.1:6379> BITCOUNT xuanshan -2 -1
(integer) 1
```

![image-20220227184223768](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220227184223768.png)

### HyperLogLog

不够精确

![image-20220227184121074](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220227184121074.png)

## Geo

地理位置 redis3.2

![image-20220227184054122](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220227184054122.png)

## 内存策略

高可用

1. VIP 主从漂移
2. 集群
3. 信号隔离、线程池
4. 压测、限流

热 key 重建 

- 加锁重建

![image-20220228010310724](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220228010310724.png)

- 热 key 不过期

  ![image-20220228010530995](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220228010530995.png)

  ![image-20220228010617919](https://raw.githubusercontent.com/gbxhq/Pic/main/image-20220228010617919.png)

# 高可用

## 批量操作

减少 Socket IO 时间、执行命令开销、资源竞争、系统调用开销

- m 操作

  优点：原子

  缺点：单线程有延迟

- pipeline

  优点：灵活，可控

  缺点：无原子性，只能作用到一个节点

- 事务

  保证原子的批量操作

  优点 原子 乐观锁

  缺点 效率最低
