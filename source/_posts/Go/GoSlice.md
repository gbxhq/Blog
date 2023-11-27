---
title: Go 切片问题汇总
date: 2021-01-18
categories: Note
tags: [Go,Note]
---

## 切片作为函数参数的理解

```go
func f()  {
    ans := []string{"aaa"}
    renew(ans)
    fmt.Printf("%v\n", ans) # [fff]
}

func renew(x []string)  {
    x[0] = "fff"
}
```

ans 数组会变成 "fff"，说明切片 ans 进入` renew` 方法是ans 切片的引用，可以变更 ans 切片的内容

但如果在 `renew` 里 append 操作，再返回打印 ans 会发现，ans 里面还是就 1 个，这是因为，ans 的 len 属性没有变化！虽然 ans 地址后面是写入了内容的，但是回到 f() 这一层，len 的值又成了 1，是读不到下一个单位长度的值的。

由此我们得到结论：

在 go 的函数里如果我们传入一个切片，只是改变里面的值，不改变切片的大小，那么可以实现。

如果还要改变切片的大小。那么请传入地址。

```golang
func f()  {
    ans := []string{"aaa"}
    add(&ans)
    fmt.Printf("%v\n", ans) # [aaa,new]
}

func add(x *[]string)  {
    x = append(x, "new")
}
```
