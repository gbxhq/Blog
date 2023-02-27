---
title:  Time.tick 使用 / 阻塞 main 函数
date: 2020-01-19
categories: Go
tags: [Go,Note]
---

每隔1秒打印一下时间

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