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

## 第一种方式

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

![在这里插入图片描述](https://img-blog.csdnimg.cn/44940310ec034a81a570c94d89ca537b.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAUmVndWxhdGlvbnM=,size_20,color_FFFFFF,t_70,g_se,x_16)

**4.需要创建一个 theme 目录 把 bundle.go 放入其中**
![在这里插入图片描述](https://img-blog.csdnimg.cn/b8bebda0cc6c45219ef98a890cb55283.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAUmVndWxhdGlvbnM=,size_20,color_FFFFFF,t_70,g_se,x_16)
**5.修改 bundle.go 文件 把 package 和 import 修改成指定格式后保存 见下图：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/9f9282a9ca3f433d803277f9a7fdf9ed.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAUmVndWxhdGlvbnM=,size_19,color_FFFFFF,t_70,g_se,x_16)
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

// resourceNotoSansSCTtf 对应的是 bundle.go 中的变量名
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

## 第二种方式

**1.在项目中新建一个 theme 目录**
![在这里插入图片描述](https://img-blog.csdnimg.cn/2f1f7224dc284dc8b74ccc62a3f5033d.png)
**2.在 theme 文件夹中 新建 fonts 目录**
![在这里插入图片描述](https://img-blog.csdnimg.cn/c55c785047584b8e8c64cb5514cf73d8.png)

**3.把下载的 ttf 格式的字体文件放置到 fonts 目录中**
![在这里插入图片描述](https://img-blog.csdnimg.cn/ae5798647e1e4e1fbdd1c0265a75573d.png)
4.在 theme 目录中 新建 theme.go 文件

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

//	StaticName 为 fonts 目录下的 ttf 类型的字体文件名
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
	"fyne/src/theme"	// fyne是我的项目路径
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