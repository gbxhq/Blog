---
title: UIDevice学习
date: 2018-04-16 18:43:23
categories: iOS
tags: Swift
---

iOS的UIDevice可以方便获取设备的硬件和系统的一些状态信息。写这篇文章是因为选修了《移动安全与测评》这门课。小作业让写一个APP获取系统和其他App的一些信息。在不越狱的iOS中我实在不知道怎么获取其他APP的信息，就借此机会了解下UIDevice吧。

<!---more--->

#准备

先列一下准备做的东西~对照文档查一下。

## 系统设备信息

根据UIDevice的文档。可以获取的信息有

- 设备名称
    - 用户给设备的命名
- 设备类型
    - iPhone、iPad、Apple watch、Apple TV等
- 系统名称
    - iOS、watchOS等
- 系统版本
    - 版本号
- UUID
    - 每个设备的唯一标示
- 电池状态
    - 是否充电、是否充满
- 电池情况
    - 即电量信息
- 多任务环境监测
    - 判断系统是否支持多任务

## 传感器相关

- 距离感应
- 设备方向
- 加速器
- 方位

## 行为侦听

- 剪贴板
- 截图

暂时就想到这么多，边做边想吧。

# 过程与分析
􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰞􏱔􏱾􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰡􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆􏰻􏰼􏱕􏱖􏰭􏰮􏰦􏱿􏲀􏲁􏰨􏰩􏰪􏰓􏰡􏰫􏰛􏱀􏰹􏱰􏱪􏱬􏱭􏱙􏱚􏰞􏱔􏰹􏱝􏰜􏲂􏰹􏲃􏲄􏰜􏲅􏲆
对照文档很容易就拿到了这些数据。

## 系统设备信息

```swift
//获取当前设备
let dev:UIDevice = UIDevice.current
//更新下这几个Label
    deviceNameLabel.text = dev.name
    deviceModelLabel.text = dev.model
    systemNameLabel.text = dev.systemName
    systemVersion.text = dev.systemVersion
//返回电池充电状态
    func batteryState(dev:UIDevice) -> String {
        dev.isBatteryMonitoringEnabled = true;//设置电池是否被监视
        var state = ""
        //判断当前电池状态
        if(dev.batteryState == UIDeviceBatteryState.unknown)
        {
            state = "未知状态"
        }
        else if(dev.batteryState == UIDeviceBatteryState.unplugged)
        {
            state =  "未充电"
        }
        else if(dev.batteryState == UIDeviceBatteryState.charging)
        {
            state =  "正在充电"
        }
        else if(dev.batteryState == UIDeviceBatteryState.full)
        {
            state = "正在充电，电量已满"
        }
        return state
    }
    // 更新Label
    batteryStateLabel.text = batteryState(dev: dev)
    batteryLevel.text = String(dev.batteryLevel)
    
```

> 其中如果可以不停地收集用户的充电状态，可以试着分析用户的生活或工作的习惯。

## 传感器相关

```swift 
//返回红外状态
    func proximityState(dev:UIDevice) -> String {
        var state = ""
        dev.isProximityMonitoringEnabled = true;
        
        if(dev.proximityState == true)
        {
            state = "红外被遮挡"
        }
        else{
            state = "红外未遮挡"
        }
        return state
    }
//返回设备方向
    func oritentationState() -> String {
        var state = ""
        switch (dev.orientation) {
        case .faceUp:
            state = "屏幕朝上平躺"
        case .faceDown:
            state = "屏幕朝下平躺"
        //倾斜？
        case .unknown:
            state = "未知方向"
        case .landscapeLeft:
            state = "屏幕向左横置"
        case .landscapeRight:
            state = "屏幕向右橫置"
        case .portrait:
            state = "屏幕直立"
        case .portraitUpsideDown:
            state = "屏幕直立，上下顛倒"
        default:
            state = "无法辨识"
            break;
        }
        return state
    }
```

通过设备的距离感应和设备方向。可以分析出用户是不是把设备放在口袋里。当然，获取这些数据面临的最大的问题，是App在后台运行的问题，iOS系统特殊的机制让这些收集行为只能，投机取巧。本文后面会提到。

## 行为侦听

```swift

//更改剪贴板的内容
 UIPasteboard.general.string = "Hello,\(UIDevice.current.name)"
//获取剪贴板的内容
let paste = UIPasteboard.general.string
```

剪贴板的内容是可以随意获取的。而且可以随意更改。
可以静默地更改了用户的剪贴板后，配合支付宝的口令红包，或者淘宝的商品分享来推广商品。

截图方便。一种方法是检测用户按下Home+Lock，这个方法系统提供了通知的接口，直接调用就可以获取。
但是在使用微信的时候我发现，微信经常在你刚刚截图后打开一个聊天对象的时候，询问你是否要发送那张图片。这应该是由于微信获取了相册的权限，然后通过最后一张照片的创建时间来判断的。本文不涉及这些权限不再分析。

## 获取其他APP信息

在GitHub找到一个项目，介绍是可以获取到系统中正在运行中的App。
使用后没啥效果，查了查，从iOS9开始就关闭了这个权限。

例外说一下，在开发iOS高版本的App时，你就要更新你的编译器Xcode。
比如**iOS12要出了，你不更新你的XCode你就不能适配iOS12**。你更新了xcode也就意味着很多漏洞从你开发者手里就被修复掉了。我认为这种开发的机制也是iOS这个系统更安全的一个很重要的原因吧！

## 后台运行问题

前面提到了，iOS安全的地方不仅在于对于权限的严格把控。而且想做到【真】后台都很难。

目前比较常用的可以实现“真后台”的方法:
1.VOIP 2.定位服务 3.后台下载 4.在后台循环播放无声音乐

而且貌似在上架应用到时候，会专门检查这方面。所以方法也只是个策略而已。

那么是否可以利用假后台来做一些事情呢。
假后台机制是：用户按Home之后，App转入后台进行运行，此时拥有180s后台时间（iOS7以后）或者600s（iOS6）运行时间可以处理后台操作

应该是可以的。因为我手机上装了个QQ同步助手，这软件只有一个读通讯录的权限，我也从不打开它，但它常常发来**云端通讯录已同步完成**的通知。猜测是利用调用通知激活后台180s，再利用这180s肆意妄为。当然只是猜测。
由于实力有限在这方面没有过多测试。

