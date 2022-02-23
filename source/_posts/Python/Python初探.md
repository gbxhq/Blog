---
title: Python初探
date: 2018-03-21
categories: Python
tags: Python
---

这是我刚开始学习Python时做的笔记，百度Python后先看到有廖雪峰的教程。就对着看了一遍。紧接着同学推荐了莫烦的教程，果然，这个教程上手更快。
另外我认为Python作为一个脚本语言，很多东西是在学习的时候没法记忆的，勤查着点就够了。
因此在学习了几小时以后，我基本上没有再做新的笔记。在以后学习的路上遇到什么问题再记录吧！

<!--more-->

# Note

## 廖雪峰Part

- / 是除法  //是整除

- name = input('please enter your name: ')

- list 有序  元素类型不限制

  tuple 定以后不可变

- if  else 后要有 `:`

- pass作为函数占位符。日后再说

- 返回值是一个tuple。但是，在语法上，返回一个tuple可以省略括号，而多个变量可以同时接收一个tuple，按位置赋给对应的值，所以，Python的函数返回多值其实就是返回一个tuple，但写起来更方便。

- 默认参数也是变量，必须是个不可变对象

- 参数前加` *`定义可变参数


  - `*list_name` 做参数传入该list的所有元素

- **关键字参数**

  ```python
  >>> extra = {'city': 'Beijing', 'job': 'Engineer'}
  >>> person('Jack', 24, **extra)
  name: Jack age: 24 other: {'city': 'Beijing', 'job': 'Engineer'}
  ```

  `**extra`表示把`extra`这个dict的所有key-value用关键字参数传入到函数的`**kw`参数，`kw`将获得一个dict，注意`kw`获得的dict是`extra`的一份拷贝，对`kw`的改动不会影响到函数外的`extra`。

  **命名关键字参数**

  对于关键字参数，函数的调用者可以传入任意不受限制的关键字参数。至于到底传入了哪些，就需要在函数内部通过`kw`检查。

  仍以`person()`函数为例，我们希望检查是否有`city`和`job`参数：

  ```Python
  def person(name, age, **kw):
      if 'city' in kw:
          # 有city参数
          pass
      if 'job' in kw:
          # 有job参数
          pass
      print('name:', name, 'age:', age, 'other:', kw)
  ```

  但是调用者仍可以传入不受限制的关键字参数：

  ```python
  >>> person('Jack',24,city='Beijing',addr='Chaoyang',zipcode=123456)
  ```

  如果要限制关键字参数的名字，就可以用命名关键字参数，例如，**只接收`city`和`job`作为关键字参数**。这种方式定义的函数如下：

  ```Python
  def person(name, age, *, city, job):
      print(name, age, city, job)
  ```

  和关键字参数`**kw`不同，命名关键字参数需要一个特殊分隔符`*`，`*`后面的参数被视为命名关键字参数。

  调用方式如下：

  ```Python
  >>> person('Jack', 24, city='Beijing', job='Engineer')
  Jack 24 Beijing Engineer
  ```

  如果函数定义中已经有了一个可变参数，后面跟着的命名关键字参数就不再需要一个特殊分隔符`*`了：

  ```Python
  def person(name, age, *args, city, job):
      print(name, age, args, city, job)
  ```

  命名关键字参数必须传入参数名，这和位置参数不同。如果没有传入参数名，调用将报错：

  ```Python
  >>> person('Jack', 24, 'Beijing', 'Engineer')
  Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
  TypeError: person() takes 2 positional arguments but 4 were given
  ```

  由于调用时缺少参数名`city`和`job`，Python解释器把这4个参数均视为位置参数，但`person()`函数仅接受2个位置参数。

  命名关键字参数可以有缺省值，从而简化调用：

  ```Python
  def person(name, age, *, city='Beijing', job):
      print(name, age, city, job)
  ```

  由于命名关键字参数`city`具有默认值，调用时，可不传入`city`参数：

  ```Python
  >>> person('Jack', 24, job='Engineer')
  Jack 24 Beijing Engineer
  ```

  使用命名关键字参数时，要特别注意，**如果没有可变参数，就必须加一个`*`作为特殊分隔符**。如果缺少`*`，Python解释器将无法识别位置参数和命名关键字参数：

  ```Python
  def person(name, age, city, job):
      # 缺少 *，city和job被视为位置参数
      pass
  ```

- 参数定义的顺序必须是：

  1. 必选参数
  2. 默认参数
  3. 可变参数
  4. 命名关键字参数
  5. 关键字参数

- 默认情况下，dict迭代的是key。如果要迭代value，可以用`for value in d.values()`，如果要同时迭代key和value，可以用`for k, v in d.items()`。

- 如果一个函数定义中包含`yield`关键字，那么这个函数就不再是一个普通函数，而是一个generator

- ```Python
  >>> from functools import reduce
  >>> def fn(x, y):
  ...     return x * 10 + y
  ...
  >>> reduce(fn, [1, 3, 5, 7, 9])
  13579
  ```

- `lambda` 匿名函数   ` lambda x: x * x `

- [Python内置函数](https://docs.python.org/3/library/functions.html)

- ```Python
  #!/usr/bin/env python3
  # -*- coding: utf-8 -*-

  ' a test module '

  __author__ = 'Michael Liao'
  ```

  第1行和第2行是标准注释，第1行注释可以让这个`hello.py`文件直接在Unix/Linux/Mac上运行，

  第2行注释表示.py文件本身使用标准UTF-8编码；

  第4行是一个字符串，表示模块的文档注释，任何模块代码的第一个字符串都被视为模块的文档注释；

  第6行使用`__author__`变量把作者写进去，这样当你公开源代码后别人就可以瞻仰你的大名

- 不能直接访问`__name`是因为Python解释器对外把`__name`变量改成了`_Student__name`，所以，仍然可以通过`_Student__name`来访问`__name`变量

- takes 0 positional arguments but 1 was given：解决方法
  在类方法的参数里加入`self`

- 判断一个变量是否是某个类型可以用`isinstance()`判断：

- ```PYthon
  >>> type(fn)==types.FunctionType
  True
  >>> type(abs)==types.BuiltinFunctionType
  True
  >>> type(lambda x: x)==types.LambdaType
  True
  >>> type((x for x in range(10)))==types.GeneratorType
  True
  ```

  `types`模块中定义的常量

- 获得一个对象的所有属性和方法，可以使用`dir()`函数


## 莫烦Part

- 如果想要使用顺序一致的字典，请使用 `collections` 模块 中的 `OrderedDict` 对象。

- 只要类中实现了 `__iter__`和 `next` 函数，那么对象就可以在 `for` 语句中使用。

- 没有&&只有and 

- ```Python
  try:
      file=open('eeee.txt','r+')
  except Exception as e:
      print(e)
      response = input('do you want to create a new file:')
      if response=='y':
          file=open('eeee.txt','w')
      else:
          pass
  else:
      file.write('ssss')
      file.close()
  """
  [Errno 2] No such file or directory: 'eeee.txt'
  do you want to create a new file:y

  ssss  #eeee.txt中会写入'ssss'
  ```

- ```
  >>> list(map(fun,[1,2],[3,4]))
  """
  [4,6]
  """
  ```
  ### Numpy

- Numpy官方教材 https://docs.scipy.org/doc/numpy-dev/user/quickstart.html

- `flatten`是一个展开性质的函数，将多维的矩阵进行展开成1行的数列。而`flat`是一个迭代器，本身是一个`object`属性。

- ```Python
  A[:,np.newaxis]
  ```

  可将一行元素转置

- `split()`是等量分割。`array_split()`可以不等量分割

- `=` 赋值会有关联性 `copy`赋值则没有

  ### Pandas

- ​

# Question


- ~~没有变量常量。数据类型声明？~~

- Key：选中一行

- 没有 ++ 语法？ Y

- `Iterator`:惰性序列 啥玩意

- 没有自动补全？Tab

- 返回函数--闭包

- ```
  def build(x, y):
      return lambda: x * x + y * y
  这段加labmda有什么用~
  答：返回了函数地址
  ```

- !不能取逆？Y

- 3-1 如果想对数据的 index 进行排序并输出:如果想翻转数据, transpose:

- loc iloc ix 的区别？

- 查看DataFrame()语法

