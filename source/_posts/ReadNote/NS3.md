---
title: NS3学习笔记
date: 2019-03-20 09:53:20
categories: Network
tags: NS3
---

要做网络仿真，老师让我搞一搞这个NS3（Network Simulator version 3）。

<!---more--->

# Problems

- [ ] https://www.nsnam.org/docs/release/3.29/doxygen/index.html doxygen编译报错`waf configure did not detect doxygen in the system -> cannot build api docs`

  需要做两个工作：

  (1)安装doxygen:

  ```
  sudo apt-get install doxygen
  ```

  (2)重新配置waf，这个步骤参见谷歌的ns3论坛 

  ```
  ./waf configure --enable-examples --enable-tests
  ```

- [ ] PyViz不会弄

- [ ] 

# 初探

参考这篇文章。整个过程很清楚了。<https://www.jianshu.com/p/85ed25003e30>

我主要做简要的记录以便自己以后查看。

环境：Ubuntu 18

- 装依赖包的shell文件:  `install.sh`  `-y`自动确认

  ```sh
  #!/bin/sh
  sudo apt-get install gcc g++ python -y
  sudo apt-get install gcc g++ python python-dev -y
  sudo apt-get install mercurial -y
  sudo apt-get install bzr -y
  sudo apt-get install gdb valgrind -y
  sudo apt-get install gsl-bin libgsl0-dev libgsl0ldbl -y
  sudo apt-get install flex bison libfl-dev -y
  sudo apt-get install g++-3.4 gcc-3.4 -y
  sudo apt-get install tcpdump -y
  sudo apt-get install aqlite aqlite3 libsqlite3-dev -y
  sudo apt-get install libxml2 libxml2-dev -y
  sudo apt-get install libgtk2.0-0 libgtk2.0-dev -y
  sudo apt-get install vtun lxc -y
  sudo apt-get install uncrustify -y
  sudo apt-get install doxygen grphviz imagemagick -y
  sudo apt-get install texlive texlive-extra-untils texlive-latex-extra -y
  sudo apt-get install python-sphinx dia -y
  sudo apt-get install python-pygraphviz python-kiwi python-pygoocanvas libgoocanvas-dev -y
  sudo apt-get install libboost-signals-dev libboost-filesystem-dev -y
  sudo apt-get install openmpi* -y
  ```

- 装NS3

- 第一遍编译的时候，记得加上 test 和 example两个参数

- eclipsee安装前装好JDK

- eclipse安装mercurial插件参考这个：
  [http://wireframesketcher.com/support/install/installing-mercurial-plugin.html](https://link.jianshu.com/?t=http://wireframesketcher.com/support/install/installing-mercurial-plugin.html)
  关键的一部就是在源里添加这个网址：<https://bitbucket.org/mercurialeclipse/update-site/raw/default/>

  加上就能在下面pending出mercurial。

  > Mercurial是一个分布式版本控制的跨平台工具。这里为什么要用到这个，我也不知道。官方的手册中也安装了这个Eclipse插件。以后懂了会补上。

- 基本上上面的教程全部涵盖了。主要是自己跟着做一遍之后理解每个地方配置的东西是啥。其实整个配置eclipse的过程就是在调一些编译build的参数。

- 不使用eclipse，直接终端 `./waf —xxxx`也是可以build的

  > 后从书中得知，编译源码时，build.py这个文件使用一次就不能再用了。想更改编译的配置只能用waf了

- 关键代码Mark：

  ```c++
  ./waf clean
  
  ./waf -d debug --enable-examples --enable-tests configure
  
  ./waf --run hello-simulator
  ```

  

对着博客搭好之后，往下懵逼了。不知道该干啥了。

---

还好下到了中文版的书。

---

# 《NS-3网络模拟器基础与应用》

章节介绍：

1. 介绍
2. 快速上手
3. 基础
4. 结果分析
5. 内核-》加深理解
6. 其他模块，几个重要的通用模块，自己设计模块
7. 示例

# 二 快速上手

这一章作者解读了ns3自带的first样例。

比较不错。

通过跑通这个样例，我便了解了ns3仿真的过程(而不是只输出一个Hello)。从其丰富的APIs中我可以看出，这只是我们用来仿真的工具。继续学习！

# 三 ns-3基础

## 3.1 关键概念

- 节点

  理解成计算机即可

- 应用

  客户端、服务器即Application

- 信道

  信道实例可以模拟一条简单的线缆

  CSMA(≈以太网)、P2P(点对点)

  WiFi(甚至可以模拟三维障碍物)

- 网络设备

  ≈网卡。网络设备安装在节点上，使得节点通过信道和其他节点通信。像真实的计算机一样，一个节点可以通过多个网络设备同时连接到多条信道上。

- 拓扑帮助

  对每个节点、网络设备等连接起来都要进行很多独立的核心操作。(繁琐)

  Helper类帮助我们更方便地配置这些。(整合)

## 3.2 优化技术

对数据的记录很分析有两类方法：

- Logging

  在命令行中，便于调试脚本

- Tracing

  采集到的数据存在文件中，便于后期处理

本章主要讲Logging。Tracing后面还会细说。

### 3.2.1 Logging

这一节我按照书上代码。稍稍了解了打LOG的方法，但也没完全明白。

### 3.2.2 命令行参数

把下列代码加入到脚本中。即可在命令行中访问 代码中的全局变量 和 ns-3中的属性系统。

```c++
Int main (int argc, char*argv[]){
  ···
    CommandLine cmd;
  cmd.Parse (argc, argv);
  ···
}
```

### 3.2.3 Tracing系统

- 输出ascii格式

  ```c++
  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll (ascii.CreatreFileSteam ("myfirst.tr"));
  ```

  这两句加在`Simulator::Run()`前面。就会在ns根目录生成myfirst.tr文件。

  `p2p.EnableAsciiAll`的作用就是通知helper  所有关于 p2p设备的 仿真信息 都打印成ASCII Tracing格式。

- PCAP

  这个格式可以用Wireshark打开分析。加这行代码：

  `pointToPoint.EnablePcapAll (myfirst);`

## 3.4 Demo

解读了example里的second.cc

# 4 统计结果分析

### 4.1.1 PyViz

如果visualizer模块没有编译，需在http://code.nsnam.org/gjc/ns-3.9-pyviz/下载pyviz软件包，解压后放在/NS3_install/ns-allinone-3.28/ns-3.28/目录下，再需重新编译如下命令：

$ ./waf clean

$ ./waf --build-profile=optimized--enable-examples --enable-tests configure

该编译阶段需要花一段时间。。。。待到编译完成进入第4步。

参考文章：https://blog.csdn.net/xiao_sheng_jun/article/details/79837984 

**最后，没弄成这个。 —vis不好使**

### 4.1.2 NetAnim

关于对NetAnim的编译书上不详细。

先装QT： `apt-get install qt4-dev-tools` 

cd到netanim的文件夹执行：

```shell
sudo make clean
sudo qmake NetAnim.pro
sudo make
ls
#看见NetAnim就成功了
sudo ./NetAnim #打开仿真界面
```

使用方法：

- 头文件：`#include "ns3/netanim-module.h"`

- 添加代码：

  ```c++
  AnimationInterface anim ("animation.xml"); //生成animation.xml文件
  ```

  其他的一些设置节点的位置、颜色等各种配置的不多介绍了。查文档吧！

## 4.2 分析数据

介绍了两个网络分析工具

### 4.2.1 TcpDump

读取输出pacap文件

介绍了TcpDump命令的格式

然后用first这个例子做了个演示

### 4.2.2 Wireshark

界面友好功能强大。

## 4.3 统计模块status

这一节介绍了自带的example里对status框架的使用。

还有一个shell了用于自动往里输入。

具体的内容我也看得懵懵。

而且这个模块是用来干啥的啊。和之前的分析数据的模块有啥不一样啊。

先往下看吧。

## 4.4 绘图工具 Gnuplot

介绍了这个工具咋用。把捕获的数据变成图表。

# 5 ns-3内核

## 5.1 组织结构

## 5.2 随机变量

讲了生成随机种子的方法

> 这章没看出啥来。毕竟我连入门都还没有。继续往下看了

# 6 ns-3其他模块

没具体讲模块的用法。而是说了很多这些模块的源代码。赶紧看过去吧。

## 6.4应用层模块

讲了UdpClientServer。

first.cc例子中的echo应答协议是，接收到什么原封发回。主要用于调试和检测。因此我们基本用不到。