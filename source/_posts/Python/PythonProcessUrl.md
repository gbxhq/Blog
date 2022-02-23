---
title: Python批量解析短连接
date: 2019-05-27 10:53:08
categories: Python
tags: [Python,正则表达式,Spider]
---

自己的需求。微信机器人接收一个消息后，需要**提取一串字符串中的链接**。

然后这些链接都是短连接。我需要获取到这些短连接跳转过去的真实链接。

就是做一个**识别网址，批量解析短连接，还原真实网址**的Demo。

<!---more--->

# 还原短连接的真实链接

根据逻辑，还原短网址的真实链接作为一个子模块可以先完成。网上搜了下思路说什么，在302跳转后看一下headers，里面就有相关信息。这个我用浏览器查了一下headers果然是可以看到。但是用`request.` `get(url)`后，打印headers就是没有。

最后一个timeout的参数。设成10，直接打印 `r.url` 就是真实链接了，也算是比较笨的方法吧。

代码：

```python
import requests
http_headers = { 'Accept': '*/*','Connection': 'keep-alive', 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.116 Safari/537.36'}
def get_real_url(url):
    rs = requests.get(url,headers=http_headers,timeout=10)
    return rs.url
```

# 正则提取链接

下一步就是在字符串里找出来网址了。正则表达式嘛，我只能说是了解。规则也不是自己写的，不多介绍了。

代码：

```python
ptn = re.compile(r'http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+')
```

# 正则表达式 sub()函数的使用

下面就是对提取到的url都做上面的获取真实链接的处理。

刚开始用的是 `findall()` ，然后循环处理。这时候我就觉得，每次循环进行爬虫的时候都有一个`timeout=10`的参数限制，整个循环跑起来肯定很慢。如果用MapReduce的思路来处理就快多了，搜了下，可以用 `Process` 里的多进程来完成。

为啥没第一时间用 `.sub()` 呢？其实刚开始也是用了 `.sub()`，结果替换完打印一下发现并没有变化。很纳闷。

---

## sub()函数的一个坑

查了一下，原来是 `.sub`  不会操作原来的字符串。

所以要写成 `msg = re.sub(ptn,'xxx',msg)` 这样的形式。

## sub() 的第二个参数是函数

`sub()`可以用了，就不用再写循环了。把第一节写的那个`get_real_url()`放进去就行了。

但是放进去报错，大体意思就是说传进去的参数是一个match后的结果。

就去网上搜了个别人用 `sub()`防了一下，把上面的 `get_real_url()` 函数改成了这样：

```python
def get_real_urls(match):
    url = match.group(0)
    rs = requests.get(url,headers=http_headers,timeout=10)
    return rs.url
```

这样传到 `sub()` 的第二个参数里就好啦~

<center>完工！过几天写成API用网页或者服务器调，就更方便啦</center>>