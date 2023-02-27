---
title: Sleep 和 Tick 怎么选
date: 2020-01-19
categories: Go
tags: [Go,Note]
---

以下答案由ChatGPT生成：

你好，这是Bing。😊

[根据网上的资料](https://cloud.tencent.com/developer/article/1755511)[1](https://cloud.tencent.com/developer/article/1755511)[2](https://blog.csdn.net/Star_CSU/article/details/86650684)[3](https://blog.csdn.net/tiancityycf/article/details/102700213)，golang中定时执行任务有三种常见的方式：time.Sleep，time.Tick和time.Ticker。它们的区别和优劣如下：

- time.Sleep是使用睡眠完成定时，结束后继续往下执行循环来实现定时任务。它的缺点是不能保证每次执行的时间间隔一致，因为要考虑到任务本身的执行时间。
- time.Tick函数是使用channel阻塞当前协程，完成定时任务的执行。它的优点是可以保证每次执行的时间间隔一致，但是缺点是不能动态修改或停止定时器。
- time.Ticker结构体也是使用channel阻塞当前协程，完成定时任务的执行。它相比于time.Tick函数，多了一个Stop方法，可以动态停止定时器。

所以，在选择golang中定时任务的方式时，要根据具体的需求和场景来决定。

一般来说，如果需要固定间隔且不需要修改或停止定时器，可以使用time.Tick函数；

如果需要固定间隔且需要修改或停止定时器，可以使用time.Ticker结构体；

如果不需要固定间隔且只需要简单地延迟一段时间再执行任务，可以使用time.Sleep方法。

附录：

Tick 使用 demo

```go
package main

import (
	"fmt"
	"time"
)

func main() {
	ticker := time.NewTicker(time.Millisecond * 1000)
	go func() {
		for t := range ticker.C {
			fmt.Println("Tick at", t)
		}
	}()
	select {} // select 就好
}
```
