---
title: Swift Demo1 秒表
date: 2018-03-31 15:17:10
categories: iOS
tags: [Swift,Demo]
---

这是阅读项目[30Days of Swift](https://github.com/allenwong/30DaysofSwift.git)源码的仿写记录，该项目受到国外一个教程：[Swift100天](http://samvlu.com/index.html)的启发。

<!---more--->
# Demo 1 StopWatch
第一个小demo是个秒表。功能简单就是点击Play计时。Pause暂停。Reset重置。
# 载入
设一个计数器`counter`初值0.0.然后用String()方法转成字符串传给Label。
# Play

一个`Timer`对象。
点下Play时：

```swift

timer = Timer.scheduledTimer(
    timeInterval: 0.1, 
    target: self,
    selector: #selector(ViewController.UpdateTimer),
    userInfo: nil,
    repeats: true)

```
其中`UpdateTimer`方法是更新Label的。也就是每个时间间隔`timeInterval: 0.1`都会执行 `counter+=1`

运行测试。没问题。点击Play后。每0.1s时间标签会累加。
如果想更规范可以这么写String以控制数字显示格式：

```
timeLabel.text = String(format: "%.1f", counter)
```
# Pause
只需要一个方法：
`timer.invalidate()`
timer对象停止计时。

而此时我们的秒表有了**跑**和**不跑**两种状态。
我们新建一个Bool变量isPlaying。方便进行状态的检测。

`isPlaying = True `时，
`playBtn.isEnabled = false`Play按钮失效
`pauseBtn.isEnabled = true`Pause按钮有效。
FALSE时同理。

## isPlaying作用
这时候已经发现小bug：多次点击Play按钮则会多次激活Timer计时器--》多次执行updateTimer方法-->时间增加变快。
解决方法：
在Play按钮的Action中增加一个判断：

```
if(isPlaying){
    return
}
```

# Reset
没什么特别的了。Counter置0.传到Label就ok。

# 思考
- 关于状态isPlaying的控制极为重要。
- 按钮的布局忘了怎么加**限制**了。不过暂时是小问题找个视频学学就好啦~

# GitHub地址
https://github.com/ixsim/Swift30demos.git


