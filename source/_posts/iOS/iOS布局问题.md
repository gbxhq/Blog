---
title: iOS布局问题入门
date: 2018-04-01 09:26:15
categories: iOS
tags: [Design,Swift]
---

昨天重拾iOS发现，怎么加Constraints等设计Layout的问题全忘了。赶紧复习一下。

<!---more--->

# Alignment 居中
![](http://p66eruxmw.bkt.clouddn.com/15225461854172.jpg)
这两个√解决
# AutoLayout 自动布局
![](http://p66eruxmw.bkt.clouddn.com/15225464765593.jpg)
注意。边界要选Safe Area。
# Stack View
选中多个组件。
![](http://p66eruxmw.bkt.clouddn.com/15225472613960.jpg)
点击按钮即可组合成一个StackView。
StackView里内容的居中、各项间距、平铺等在右侧设置：
![](http://p66eruxmw.bkt.clouddn.com/15225473613893.jpg)

# 等宽登高
两个View等宽。点住一个右键（或Ctrl）拖到另一个View：
![](http://p66eruxmw.bkt.clouddn.com/15225471342124.jpg)
选择等宽。一般是和Safe Area等宽
# 竖屏/横屏的布局切换问题
## Size Class
横屏竖屏布局必须先了解iOS的SizeClass机制。
R = Regular 正常 
C = Compact 紧凑

|   | iPad |
| --- | --- |
| 高 | R |
| 宽 | R |

| iPhone | 竖屏 | 横屏 |
| --- | --- | --- |
| 高 | R | C |
| 宽 | C | C/R(Plus) |

Note：iPhone X在横屏下竟然全是紧凑：
![](http://p66eruxmw.bkt.clouddn.com/15225480367581.jpg)

也就是说只有Plus是在横屏下的宽是R。
设计时可以在iPhone X的布局下适配。
## 增加变体
懂了Size Class这个这时候就可以增加新的变体Constraints：
![](http://p66eruxmw.bkt.clouddn.com/15225484528282.jpg)

-------
Note：
双击约束可以编辑。并增加变体约束。
![](http://p66eruxmw.bkt.clouddn.com/15225489037498.jpg)

-------

最后的Installed可以设置这个Constraints在此Size Class下是否√生效：![](http://p66eruxmw.bkt.clouddn.com/15225491484322.jpg)


OK。这些布局差不多够入门的了。


