---
title: Gin记录
date: 2020-02-11 16:53:49
categories:
tags:
---



<!---more--->

安装 `go get github.com/gin-gonic/gin`

运行后卡着不动

给终端开了代理可以了。

---

```go
engine.GET("/hello", func(context *gin.Context) {
		path := context.FullPath()
		fmt.Println("AAA",path)

		name := context.Query("name")
		fmt.Println("BBB",name)

		context.Writer.Write([]byte("Hello,"+name))
	})

	engine.POST("/login", func(context *gin.Context) {
		fmt.Println(context.FullPath())

		name := context.PostForm("username")
		pwd := context.PostForm("password")
		fmt.Println(name+"\n"+pwd)

		context.Writer.Write([]byte(name+" 登录"))
	})
```

`context.Query()` 一个参数

`context.DefaultQuery()` 两个参数，可以设一个默认

`context.PostForm()`返回1个参数

`context.GetPostForm()`返回2个参数,还会返回一个是否存在

