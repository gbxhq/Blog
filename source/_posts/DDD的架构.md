---
title: DDD 架构
date: 2020-01-19
categories: DDD
tags: [DDD]
---

# 端口和适配器架构

port&adapter。也叫六边形架构

与MVC自下而上不同，端口适配器架构是由内向外：应用-端口-适配器。

# 事件驱动架构

事件溯源

# CQRS

Command Query Responsibility Segregation
命令和查询职责分离

把同一个模型的 无副作用查询操作 和 改变状态的修改操作（称之为Command）分开。
两部分可以分别在不同的模块和服务实现。部署到不同的硬件。甚至使用完全不同的数据存储。

比如。Command经常使用事件溯源来实现。

这种架构特别适合需要高性能，Query和Command的扩展性有不同要求的应用。