---
title: Go 刷题记录
date: 2020-03-08 21:32:39
categories: [Algorithm]
tags: [Go,Algorithm]
---

> 再刷洛谷试炼场，发现试炼场已经无了。开始以为找不到了，知乎上看到站长的回复才知道真的无了。我是从这个人整理的版本里刷的：
>
> https://www.luogu.com.cn/paste/66uuuvdr

大概刷了 10 道题之后，放弃洛谷。

原因是里面几乎都是 C++选手，遇到一些解不了的case实在不知道 Go 是哪里 A 不过的。


# 输入输出

> 才发现用 go 刷题连输入输出都不会

- `print` 在golang中 是属于输出到标准错误流中并打印,官方不建议写程序时候用它。可以debug时候用

- `fmt.print` 在golang中 是属于标准输出流,一般使用它来进行屏幕输出.

# 处理字符串

```go
func replaceSpace(s string) string {
	var res strings.Builder
    for i:=range s{
    	if s[i]==' '{
			res.WriteString("%20")
		}else {
			res.WriteByte(s[i])
		}
	}
	return res.String()
}
```



#### [03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

交换法

