---
title: Python廖雪峰练习
date: 2018-03-21
categories: Python
tags: Python
---
这是刚学Python的第一天，对着Python廖雪峰的教程做的练习。
莫烦的教程虽然简单上手快，但是廖雪峰的这个练习还是不错的，让我回想起当初学C的一个寒假，我对着OJ和一个同学做那些“无聊”的题目。一晃就是四年啊！

<!---more--->

## 函数的参数

```Python
def product(*number):	
  if number == ():
     raise TypeError 
  a = 1
  for x in number:
      a = x*a
  return a
```
## 递归函数

```Python
def move(n, a, b, c):
    if n == 1:
        print ( a , '-->' , c)
    else:
        move(n-1,a,c,b) #假设move函数没问题，A上前n-1个会被移动至B
        move(1,a,b,c) #此时把最大的放到C
        move(n-1,b,a,c)
#move(4,'A','B','C')
```
## 切片

```python
def trim(s):
    if s == '':
        return s
    while s[0] == ' ':
        s = s[1:]
        if s == ' ':
            return ''
    while s[-1] == ' ':
        s = s[0:-1]
    return s
```
## 迭代

```Python
def findMinAndMax(L):
    if L == []:
        return (None,None)
    else:
        a = L[0]
        b = L[0]
        for i in L:
            if i < a:
                a = i
            if i > b:
                b = i
    return (a,b)
```
## 列表生成式

```Python
L1 = ['Hello', 'World', 18, 'Apple', None]
L2 = [ x.lower() for x in L1 if isinstance(x,str) ]
```
## 生成器

```Python
def triangles():
    n = 2
    a = [1,1]
    b = [1]
    yield [1]
    yield [1,1]
    while 1:
        for i in range(1,n):
            b.append(a[i] + a[i-1])
        b.append(1)
        n = n+1
        a = b
        b = [1]
        yield a
```
## map/reduce

```Python
def normalize(name):
    return name[0].upper() + name[1:].lower()
```

```Python
def cheng(x,y):
    return x*y
return reduce(cheng,L)
```

```Python
from functools import reduce
def str2float(s):
    DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '.': 999}
    def fn(x, y):
        if y == 999:
            return x
        return x * 10 + y
    def char2num(s):
        return DIGITS[s]

    n = s.index('.')

    return reduce(fn, map(char2num, s))/(10**n)

#跳过小数点：
#我把 '.' 转换成 999 当遇到999 不做计算 return x 。像个傻子 🤪
#正确方法：
#s[:n]+s[n+1:] n是小数点位置。取 前n个和第n+1个开始往后的字符串即可。
```
## fliter 

跳过

## sort

```Python
def by_name(t):
	return t[0]
```

```Python
def by_score(t):
	return -t[1]
```
​

