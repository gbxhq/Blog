---
title: Go UI 框架 Fyne 使用
date: 2020-01-19
categories: Note
tags: [Go,Note]
---

> 给紫玉写了一个工具方便她处理Excel，之前一直是黑框的，需要她自己复制数据进去计算，最近有时间于是使用Fyne写了个界面。
> 记录下 Fyne 使用遇到的问题。总体来说可以满足简单的图形需求。

# mac交叉编译win报错

```
fyne package -os windows -icon 1.jpg
# runtime/cgo
gcc_libinit_windows.c:7:10: fatal error: 'windows.h' file not found
```

`brew install mingw-w64` 还是不行

看文档。交叉编译不能直接用 `fyne package`

参考文档 https://developer.fyne.io/started/cross-compiling

发现主要是设置 CGO_ENABLED、和CC两个环境变量，于是尝试：

`CGO_ENABLED=1 GOOS=windows GOARCH=amd64 CC=x86_64-w64-mingw32-gcc fyne package -os windows -icon 1.jpg`

成功

# Fyne解决中文乱码

## 配置字体

配置字体有两种方式 

### 第一种方式

**1.安装官方的 cmd 工具**

```bash
go get fyne.io/fyne/cmd/fyne
```

**2.准备好字体文件（建议使用 ttf 字体格式）**

```bash
字体文件下载地址 https://www.fonts.net.cn/
```

**3.使用fyne把字体文件打包成二进制格式**

```bash
fyne bundle fonts.ttf >> bundle.go
```

**4.需要创建一个 theme 目录 把 bundle.go 放入其中**
**5.修改 bundle.go 文件 **把 package 和 import 处理下

```go
package theme
import "fyne.io/fyne/v2"
```

**6.在 theme 文件夹新建 theme.go 文件 并添加以下代码**

```go
package theme

import (
    "fyne.io/fyne/v2"
    "fyne.io/fyne/v2/theme"
    "image/color"
)


type MyTheme struct{
    }

var _ fyne.Theme = (*MyTheme)(nil)

// resourceNotoSansSCTtf 对应的是 bundle.go 中的变量名!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
func (m MyTheme) Font(fyne.TextStyle) fyne.Resource {

    return resourceNotoSansSCTtf
}

func (*MyTheme) Color(n fyne.ThemeColorName, v fyne.ThemeVariant) color.Color {

    return theme.DefaultTheme().Color(n, v)
}

func (*MyTheme) Icon(n fyne.ThemeIconName) fyne.Resource {

    return theme.DefaultTheme().Icon(n)
}

func (*MyTheme) Size(n fyne.ThemeSizeName) float32 {

    return theme.DefaultTheme().Size(n)
}
```

------

### 第二种方式

**1.在项目中新建一个 theme 目录**
**2.在 theme 文件夹中 新建 fonts 目录**
**3.把下载的 ttf 格式的字体文件放置到 fonts 目录中**
**4.在 theme 目录中 新建 theme.go 文件**

```go
package theme

import (
    _ "embed"
    "fyne.io/fyne/v2"
    "fyne.io/fyne/v2/theme"
    "image/color"
)

var (
    //go:embed fonts/NotoSansSC.ttf
    NotoSansSC []byte
)

type MyTheme struct{
    }

var _ fyne.Theme = (*MyTheme)(nil)

//    StaticName 为 fonts 目录下的 ttf 类型的字体文件名
func (m MyTheme) Font(fyne.TextStyle) fyne.Resource {

    return &fyne.StaticResource{

        StaticName:    "NotoSansSC.ttf",
        StaticContent: NotoSansSC,
    }
}

func (*MyTheme) Color(n fyne.ThemeColorName, v fyne.ThemeVariant) color.Color {

    return theme.DefaultTheme().Color(n, v)
}

func (*MyTheme) Icon(n fyne.ThemeIconName) fyne.Resource {

    return theme.DefaultTheme().Icon(n)
}

func (*MyTheme) Size(n fyne.ThemeSizeName) float32 {

    return theme.DefaultTheme().Size(n)
}
```

------

## 在 main.go 中引入并使用

```go
package main

import (
    "fyne.io/fyne/v2/app"
    "fyne.io/fyne/v2/container"
    "fyne.io/fyne/v2/widget"
    "fyne/src/theme"    // fyne是我的项目路径
)

func main() {

    a := app.New()
    a.Settings().SetTheme(&theme.MyTheme{
    })
    w := a.NewWindow("你好")

    hello := widget.NewLabel("你好 Fyne!")
    w.SetContent(container.NewVBox(
        hello,
        widget.NewButton("嗨!", func() {

            hello.SetText("欢迎 :)")
        }),
    ))

    w.ShowAndRun()
}
```