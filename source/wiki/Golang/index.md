---
layout: wiki  # 使用wiki布局模板
wiki: Golang # 这是项目名
title: Golang
---

# Go 文档

https://gobyexample-cn.github.io/

# 编程规范

https://gocn.github.io/styleguide/

# 引用传递

Go语言中所有的传参都是值传递（传值），都是一个副本，一个拷贝。因为拷贝的内容有时候是非引用类型（int、string、struct等这些），这样就在函数中就无法修改原内容数据；有的是引用类型（指针、map、slice、chan等这些），这样就可以修改原内容数据。

是否可以修改原内容数据，和传值、传引用没有必然的关系。在C++中，传引用肯定是可以修改原内容数据的，在Go语言里，虽然只有传值，但是我们也可以修改原内容数据，因为参数是引用类型。

这里也要记住，引用类型和传引用是两个概念。

再记住，Go里只有传值（值传递）。