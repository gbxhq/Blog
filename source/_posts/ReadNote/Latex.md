---
title: Latex
date: 2019-04-01 15:44:47
categories: Note
tags: Latex
---



<!---more--->

# 初见

```latex
\documentclass{article}

\usepackage{ctex} %支持中文

\begin{document}

你好， \LaTeX.
    
\end{document}
```

编译：`xelatex test.tex`

直接生产PDF

`texdoc ctex` 查看ctex手册

`texdoc lshort-zh` 中文入门手册

# 基本信息

```latex
\title{My First Document}
\author{ixs}
\date{\today}

\begin{document}
	\maketitle %显示基本信息
\end{document}
```

# 基本用法

一下内容来自[http://www.mohu.org/info/symbols/symbols.htm](http://www.mohu.org/info/symbols/symbols.htm) 覆盖常用的公式：

# 常用数学符号的 LaTeX 表示方法

（以下内容主要摘自[“一份不太简短的 LATEX2e 介绍”](http://www.mohu.org/info/lshort-cn.pdf)）

１、指数和下标可以用^和_后加相应字符来实现。比如：

![img](http://www.mohu.org/info/symbols/foot.gif)

2、平方根（square root）的输入命令为：\sqrt，n 次方根相应地为: \sqrt[n]。方根符号的大小由LATEX自动加以调整。也可用\surd 仅给出
符号。比如：

![img](http://www.mohu.org/info/symbols/sqrt.GIF)

3、命令\overline 和\underline 在表达式的上、下方画出水平线。比如：

![img](http://www.mohu.org/info/symbols/overline.GIF)

4、命令\overbrace 和\underbrace 在表达式的上、下方给出一水平的大括号。

![img](http://www.mohu.org/info/symbols/brace.GIF)

5、向量（Vectors）通常用上方有小箭头（arrow symbols）的变量表示。这可由\vec 得到。另两个命令\overrightarrow 和\overleftarrow在定义从A 到B 的向量时非常有用。

![img](http://www.mohu.org/info/symbols/vec.GIF)

6、分数（fraction）使用\frac{...}{...} 排版。一般来说，1/2 这种形式更受欢迎，因为对于少量的分式，它看起来更好些。

![img](http://www.mohu.org/info/symbols/frac.GIF)

7、积分运算符（integral operator）用\int 来生成。求和运算符（sum operator）由\sum 生成。乘积运算符（product operator）由\prod 生成。上限和下限用^ 和_来生成，类似于上标和下标。

![img](http://www.mohu.org/info/symbols/int.GIF)

## 以下提供一些常用符号的表示方法

![img](http://www.mohu.org/info/symbols/1.GIF)

![img](http://www.mohu.org/info/symbols/2.GIF)

![img](http://www.mohu.org/info/symbols/3.GIF)

![img](http://www.mohu.org/info/symbols/4.GIF)

![img](http://www.mohu.org/info/symbols/5.GIF)

![img](http://www.mohu.org/info/symbols/6.GIF)

![img](http://www.mohu.org/info/symbols/7.GIF)