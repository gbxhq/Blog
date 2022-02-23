---
title: Problems in Using VSCode
date: 2018-09-07 09:14:07
categories: [Log]
tags: tips
---

Sublime转战VS Code。因为VS Code还能Debug一下。

<!---more--->

# 先加入环境变量

从终端调起VS Code还是很常用的。

先打开环境变量配置文件。目录是` ~/.bash_profile`。我用Sublime打开（玩不了vim）命令就是

```bash
subl ~/.bash_profile //哈哈过河拆桥系列
```

然后加入这么一行

```
export PATH=/Applications/Visual\ Studio\ Code.app/Contents/Resources/app/bin:$PATH
```

这样就能用 `code`这个命令了。 比如 `code .`就是打开当前文件夹。

再补充一个知识点。

就是可以给命令加别名。在`.bash_profile`文件添加这样的语句：

```
alias  web="code ~/work/web"
```

最后运行`source ~/.bash_profile`让配置文件生效。

就是说`web`已经成了一个命令。 alias就是别名嘛~

# 配置C/C++环境

- 如果只是编译。~~一个Code Runner的插件就够了。~~但是想Debug。还是要动动手啊！

然后我主要参考了这篇博客。还是很清楚的。

https://blog.csdn.net/qq547276542/article/details/73823570?locationNum=5&fps=1

- 现在遗留了一个问题就是。Debug的过程必须在系统的终端进行。怎么在VSCode里内置的终端呢。那样看起来就方便很多了。

- 放弃Code Runner ，换用了另一个叫 `C/C++ complie`的插件。

  用⌘+R就可以允许。很方便。

# 快捷键积累

用到啥记点啥挺不错 ⌘⇧⌃⌥

- 后退： **⌃ -**  

  前进：**⌃⇧ -** 

- 扩选：**⌘⇧⌃→**

  缩选：**⌘⇧⌃←**

- 选择下一个匹配项：**⌘D**

  选择所有匹配项：**⌘⇧L**

- 向上移动一行：**⌥↑**

  向下移动一行：**⌥↓**

- 向上复制一行：**⇧⌥↑**

  向下复制一行：**⇧⌥↓**

- 在上面添加光标：**⌘⌥↑**

  在下面添加光标：**⌘⌥↓**

- 到行首：**ctrl + a**

  到行尾：**ctrl + e**

  前进后退：**ctrl + f/b** (相当于左右方向键)

