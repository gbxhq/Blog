---
title: Python Problems Notes
date: 2018-05-23 14:37:07
categories: Python
tags: [Python,Note]
---

Python相关杂记录，方便自己查阅，没技术含量。

<!---more--->

# pip

## 更换源

mac用户文件夹下没有.pip文件夹，自己建就行。 系统自带的在`~/Library/Application Support/pip/pip.conf`

`code ~/.pip/pip.conf` **然后给权限**!

` sudo chmod 755 pip.conf`

添加内容：

```
[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple/
[install]
trusted-host=https://pypi.tuna.tsinghua.edu.cn/simple/
```

```
清华：https://pypi.tuna.tsinghua.edu.cn/simple
阿里云：http://mirrors.aliyun.com/pypi/simple/
```

# 引用其他文件

文件夹下加一个 `__init__.py`

哪怕是空的

# Spyder使用IPython Console弹出绘图窗口的设置方法

有图。挂了。七牛云坑啊。

# matplotlib 画图show()不显示图

1. `Spyder设置（Cmd + ，）`-->`IPython Console`-->`Graphics`-->`Backend 改成 QT5`
   [七牛图挂 有空补]
2. 更改完设置后要新开一个IPython Console才会生效。

