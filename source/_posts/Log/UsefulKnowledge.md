---
title: 小知识点「理论」
date: 2018-07-03 13:23:45
categories: Log
tags: [Note]
---

乱七八糟的东西。都是看博文啥的不懂现搜的~

<!---more--->

# 名词相关

## RESTful

http://www.cnblogs.com/wang-yaz/p/9237981.html

## i18n

i18n（其来源是英文单词 **i**<u>nternationalizatio</u>**n**的首末字符**i**和**n**，<u>18</u>为中间的字符数）是“国际化”的简称。通常与i18n相关的还有**L10n**（“**本地化”的简称**）。

## GP(Generic Programming)

泛型编程。Generic programming is a style of computer programming in which algorithms are written in terms of types to-be-specified-later that are then instantiated when needed for specific types provided as parameters.

## SGI STL

先介绍下 **GNU STL**

> 这是GCC带的STL实现，包含在libstdc++这个库里面，写C++一旦用到库函数是基本会链接这个库。GNU STL是在SGI的STL基础上开发的，所以SGI STL我就不再单独列出了。
>
> — 简书看到的一段

其中 SGI 就是 Silicon Graphics Computer Systems, Inc. 一个公司。

## GNU

https://zh.wikipedia.org/wiki/GNU

*GNU*的开发始于1983年，它是自由的类Unix操作系统，这使得计算机用户拥有了分享和改进其所用软件的自由。

## POSIX

**可移植操作系统接口**（英语：Portable Operating System Interface，缩写为**POSIX**）是[IEEE](https://zh.wikipedia.org/wiki/IEEE)为要在各种[UNIX](https://zh.wikipedia.org/wiki/UNIX)[操作系统](https://zh.wikipedia.org/wiki/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F)上运行软件，而定义[API](https://zh.wikipedia.org/wiki/API)的一系列互相关联的标准的总称，其正式称呼为IEEE Std 1003，而国际标准名称为[ISO](https://zh.wikipedia.org/wiki/ISO)/[IEC](https://zh.wikipedia.org/wiki/IEC) 9945。此标准源于一个大约开始于1985年的项目。POSIX这个名称是由[理查德·斯托曼](https://zh.wikipedia.org/wiki/%E7%90%86%E6%9F%A5%E5%BE%B7%C2%B7%E6%96%AF%E6%89%98%E6%9B%BC)（RMS）应IEEE的要求而提议的一个易于记忆的名称。它基本上是Portable Operating System Interface（可移植操作系统接口）的缩写，而**X**则表明其对Unix API的传承。

[Linux](https://zh.wikipedia.org/wiki/Linux)基本上逐步实现了POSIX兼容，但并没有参加正式的POSIX认证。[[1\]](https://zh.wikipedia.org/wiki/%E5%8F%AF%E7%A7%BB%E6%A4%8D%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F%E6%8E%A5%E5%8F%A3#cite_note-1)

[微软](https://zh.wikipedia.org/wiki/%E5%BE%AE%E8%BD%AF)的[Windows NT](https://zh.wikipedia.org/wiki/Windows_NT)声称部分实现了POSIX标准。

当前的POSIX主要分为四个部分[[2\]](https://zh.wikipedia.org/wiki/%E5%8F%AF%E7%A7%BB%E6%A4%8D%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F%E6%8E%A5%E5%8F%A3#cite_note-2)：Base Definitions、System Interfaces、Shell and Utilities和Rationale。

## VoIP  SIP

Voice over Internet Protocol 和 Session Initiation

## W3C

World Wide WebConsortium 万维网联盟

## IETF

Intenet Engineering Task Force 互联网工程任务组

# 二进制包和源代码安装的差距

源代码方式和二进制包是软件包的两种形式。二进制包里面包括了已经经过编译，可以马上运行的程 序。你只需要下载和解包（安装）它们以后，就马上可以使用。源代码包里面包括了程序原始的程序代码，需要在你的计算机上进行编译以后才可以产生可以运行程 序,所以从源代码安装的时间会比较长。  

source code 是程序員寫的碼， binary code 是機器跑的碼。

source code 得經過 compile 才能成為 binary code。

RPM 有分兩種：binary rpm 跟 source rpm。前者是編好的 binary，安裝就可用。  後者是還沒編好的 source ，需 rebuild 之後才能安裝。  

rpm格式很好区分，二进制格式的包名字很长，都带有版本号、适应平台、适应的硬件类型等，而源码格式仅仅就是一个版本号的tar包。 

mysql-5.0.45.tar.gz 是 源码包    

像这样的 mysql-5.0.45-linux-x86_64-glibc23.tar.gz   是二进制包  

如果你用过压缩工具就会明白，压缩包未必就是软件，它也可能是备份的许多图片，也可能是打包在一起的普通资料，要分辨它到底是什么最好的办法就是查看包里的文件清单，使用命令tar ztvf  * . 或者  tar ytvf  *.bz2   *

*源代码包里的文件往往会含有种种源代码文件，头文件*.h、c代码源文件*.c、C++代码源文件*.cc/*.cpp等；而二进制包里的文件则会有可执行文件（与软件同名的往往是主执行文件），标志是其所在路径含有名为bin的目录（仅有少数例外）

