---
title: To be an Architect
date: 2018-01-04 10:24:51
categories: Note
tags: Note
---

公众号“架构师之路”的阅读笔记。特别喜欢58沈剑的文章风格，每次看都受益匪浅！故记录在博客中。

<!---more--->

## [不在线，好友发给我的微信消息，会不会丢？](https://mp.weixin.qq.com/s?__biz=MjM5ODYxMDA5OQ==&mid=2651961909&idx=1&sn=74ddfea06a25b3650e7f2e1b501a36cb&chksm=bd2d0fe98a5a86ffd72b6d342855e489b6185c39fe304d6cae04f18a9811e38e1f178013c1fe&scene=0&xtrack=1#rd)

**总结**

“离线消息”的玩法，可能比大家想象的要复杂，常见的优化有：

(1) 对于同一个用户B，一次性拉取所有用户发给ta的离线消息，再在客户端本地进行发送方分析，相比按照发送方一个个进行消息拉取，能大大减少服务器交互次数；

(2) 按需拉取，是无线端的常见优化；

(3) 分页拉取，是一个请求次数与包大小的折衷；

(4) 应用层的ACK，**应用层的去重**（用户无察觉），才能保证离线消息的不丢不重；

(5) 下一页的拉取，同时作为上一页的ACK，能够极大减少与服务器的交互次数；