---
title: copies the lock value 报错
date: 2020-01-19
categories: Go
tags: [Go,Note]
---

`Call of 'global.NewResponse' copies the lock value: type 'sync.Map' contains 'sync.Mutex' which is 'sync.Locker'` 报错

# 原因

go vet 工具会检测拥有 Lock 方法 (实际需要引用传递) 的 type 是否按值传递。如果是这种情况，则会发出警告。


# 解决方案

改成引用传递

# 解读

在golang中，如果一个结构体希望禁止用户做值拷贝，可以在结构体中使用一个noCopy变量，golang中有sync.Cond/sync.waitGroup/sync.Pool中使用了noCopy。其实golang中是禁止Locker接口值拷贝，所以sync.Mutex和sync.RWMutex等等类型如果传值也会提示该错误。

golang sync 包中:
\- `sync.Cond`
\- `sync.Pool`
\- `sync.WaitGroup`
\- `sync.Mutex`
\- `sync.RWMutex`
\- ……
禁止拷贝，

golang 没有禁止对实现`sync.Locker`接口的对象实例赋值进行报错，只是在使用go vet 做静态语法分析时，会提示错误。