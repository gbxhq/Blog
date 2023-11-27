---
title: Go基础-1
date: 2020-01-18 20:56:44
categories: Note
tags: [Go,Note]
---

<!---more--->

# 基础语法

- 编译
  
  ```shell
  go build -o AppName
  ```
  
  跨平台编译
  
  ```shell
  CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build
  CGO_ENABLED=0 GOOS=windows GOARCH=amd64 go build
  ```
  
  可以用export先把上述变量更改

- `go install`会先执行`go build`然后把build好的可执行文件自动拷到`/bin`目录

变量声明以关键字`var`开头，变量类型放在变量的后面，行尾无需分号。 举个例子：

```go
var name string
var age int
var isOk bool
```

## 变量声明

### 标准声明

```go
var 变量名 变量类型
```

### 批量声明

每声明一个变量就需要写`var`关键字会比较繁琐，go语言中还支持批量变量声明：

```go
var (
    a string
    b int
    c bool
    d float32
)
```

### 变量的初始化

```go
var name string = "Q1mi"
var age int = 18
```

或者一次初始化多个变量

```go
var name, age = "Q1mi", 20
```

#### 短变量声明

在函数内部，可以使用更简略的 `:=` 方式声明并初始化变量。

```go
package main

import (
    "fmt"
)
// 全局变量m
var m = 100

func main() {
    n := 10
    m := 200 // 此处声明局部变量m
    fmt.Println(m, n)
}
```

#### 匿名变量

在使用多重赋值时，如果想要忽略某个值，可以使用`匿名变量（anonymous variable）`。 匿名变量用一个下划线`_`表示，例如：

```go
func foo() (int, string) {
    return 10, "Q1mi"
}
func main() {
    x, _ := foo()
    _, y := foo()
    fmt.Println("x=", x)
    fmt.Println("y=", y)
}
```

匿名变量不占用命名空间，不会分配内存，所以匿名变量之间不存在重复声明。 (在`Lua`等编程语言里，匿名变量也被叫做哑元变量。)

注意事项：

1. 函数外的每个语句都必须以关键字开始（var、const、func等）
2. `:=`不能使用在函数外。
3. `_`多用于占位，表示忽略值。

# 常量

相对于变量，常量是恒定不变的值，多用于定义程序运行期间不会改变的那些值。 常量的声明和变量声明非常类似，只是把`var`换成了`const`，常量在定义的时候必须赋值。

```go
const pi = 3.1415
const e = 2.7182
```

声明了`pi`和`e`这两个常量之后，在整个程序运行期间它们的值都不能再发生变化了。

多个常量也可以一起声明：

```go
const (
    pi = 3.1415
    e = 2.7182
)
```

const同时声明多个常量时，如果省略了值则表示和上面一行的值相同。 例如：

```go
const (
    n1 = 100
    n2
    n3
)
```

上面示例中，常量`n1`、`n2`、`n3`的值都是100。

## iota

`iota`是go语言的常量计数器，只能在常量的表达式中使用。

`iota`在const关键字出现时将被重置为0。const中每新增一行常量声明将使`iota`计数一次(iota可理解为const语句块中的行索引)。 使用iota能简化定义，在定义枚举时很有用。

举个例子：

```go
const (
        n1 = iota //0
        n2        //1
        n3        //2
        n4        //3
    )
```

### 几个常见的`iota`示例:

使用`_`跳过某些值

```go
const (
        n1 = iota //0
        n2        //1
        _
        n4        //3
    )
```

`iota`声明中间插队

```go
const (
        n1 = iota //0
        n2 = 100  //100
        n3 = iota //2
        n4        //3
    )
    const n5 = iota //0
```

定义数量级 （这里的`<<`表示左移操作，`1<<10`表示将1的二进制表示向左移10位，也就是由`1`变成了`10000000000`，也就是十进制的1024。同理`2<<2`表示将2的二进制表示向左移2位，也就是由`10`变成了`1000`，也就是十进制的8。）

```go
const (
        _  = iota
        KB = 1 << (10 * iota)
        MB = 1 << (10 * iota)
        GB = 1 << (10 * iota)
        TB = 1 << (10 * iota)
        PB = 1 << (10 * iota)
    )
```

多个`iota`定义在一行

```go
const (
        a, b = iota + 1, iota + 2 //1,2
        c, d                      //2,3
        e, f                      //3,4
    )
```

## 类型

```
多行字符串用` 注意不是单引号，是[反引号]
```

### 字符串的常用操作

| 方法                                  | 介绍      |
|:-----------------------------------:|:-------:|
| len(str)                            | 求长度     |
| +或fmt.Sprintf                       | 拼接字符串   |
| strings.Split                       | 分割      |
| strings.contains                    | 判断是否包含  |
| strings.HasPrefix,strings.HasSuffix | 前缀/后缀判断 |
| strings.Index(),strings.LastIndex() | 子串出现的位置 |
| strings.Join(a[]string, sep string) | join操作  |

## byte和rune类型

 这里没细看，mark

## 类型转换

Go语言中只有强制类型转换，没有隐式类型转换。

强制类型转换的基本语法如下：

```bash
T(表达式)
```
