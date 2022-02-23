---
title: HackIntosh安装记录
date: 2019-04-08 09:01:50
categories: fun
tags: Hackintosh
---

紫玉要做生信，最近一直在自学R和Linux相关的东西。还说要买个Macbook。于是周末给紫玉的联想小新潮7000装了黑苹果让她先体验。写下这篇文章记下关键的东西~

<!---more--->

# EFI

其实只要整个Clover的EFI配置好了。黑苹果装起来是很简单的。

紫玉的电脑是联想小新潮7000，在远景看了下已经有完美的EFI。直接打包下了下来。

---

# 安装

安装的过程肯定是用U盘。

由于我本身有Mac，先用原版镜像和命令：`sudo /Users/lixs/Desktop这里是目录/Install\ macOS\ Mojave.app/Contents/Resources/createinstallmedia --volume /Volumes/Mojave这里是U盘的名` 把U盘制作成macOS安装盘。

然后应该会自带一个EFI分区。

把下载好的完整的EFI文件夹放进EFI分区里。

## BIOS设置

- 安全启动关闭 不然进不去Clover
- ACHI开启 不然看不到本机的硬盘(还得格成GPT这个不用多说了)

这样基本就可以正常安装了。

# EFI迁移

进入了Mac的系统后。把EFI分区放在硬盘上。

这个操作在Mac下比较方便：

记住两个命令：


```shell
sudo diskutil list #看下EFI分区是disk几s几
sudo diskutil mount disk4s1  # 挂载USB的EFI分区
```

然后EFI分区就可以在Finder里看到了。

把U盘里能用的Clover整个放进去就完事。

# 装好后配置

## 开启HiDPI

刚装了黑苹果会发现显示效果特别不清楚。开启HiDPI后可以在显示器设置里选择缩放效果。字的显示啥的会变得清晰很多。具体开启HiDPI的方法网上有人制作了shell。项目地址：

[https://github.com/xzhih/one-key-hidpi/blob/master/README-zh.md](https://github.com/xzhih/one-key-hidpi/blob/master/README-zh.md)

## Clover的配置

用Clover Config那个软件配置很方便。注意这个软件是实时保存的。所以要备份好之前的plist文件。

- Boot栏有个选项是使用上次的启动项挺好。还能设置等待时间。
- GUI栏依次添加Recovery,Preboot,FileVault可以把这些分区在Clover隐藏掉。F3是显示/隐藏 快捷键。

# 再装Windows

对紫玉来说Windows有时候也是必要的。

我就给紫玉在机械盘上装了个Windows。

这时候出现一个问题。Windows安装后，EFI分区多了Microsoft的文件夹。

**但是Clover进不去了。**

改用U盘里的Clover打开了macOS，跳了半天EFI文件夹还是不行。

**正解：**

在Windows下一个**EasyUEFI**，手动添加Clover文件夹下的一个`x64.efi`到UEFI启动项搞定。


# 存在的问题

## WiFi&Bluetooth

这个英特尔的无解。目前采用外挂WiFi。蓝牙则没有。

后续准备换DW1560吧。

## 时间显示

应该是还有时间不同步的问题没解决  但是周末时间不够了也没去解决。

这是我电脑上保存的解决这个问题的方法：

> windows虽然为了兼容性，一直沿用本地时间，但是在注册表中有一个设置可以让它使用UTC，这个正是我们需要的，修改注册表就好了。
> 让windows也使用Universal Time，这样即使在不联网的情况下，时钟仍然是正确的特别注意的是：取消Boot Camp的Apple时间服务，不然时不时Apple时间服务会把时间调正回去。
> 1）开始菜单，运行regedit
> 2）打开TimeZoneInformation，位置
> HKEY_LOCAL_MACHINE＼SYSTEM＼CurrentControlSet＼Control＼TimeZoneInformation
> 3）右击->创建一个新的DWORD，数值名称 RealTimeIsUniversal 数值数据 1 (十六进制) 注意大小写，修改完成确定并且把regedit关了。
> 4）打开时间设置，取消“自动与Internet时间服务器同步”
> 5）取消Apple时间服务，控制面板->管理工具->服务，里面有个“Apple时间服务”，右击它然后选择属性，启动类型选择禁用、停止

# 总结

黑苹果的安装总体来说最难的就在EFI整个的配置上，有前人的栽树，安装起来就算是很简单的了。

以后组台式机可以参考这里的配置[https://www.tonymacx86.com](https://www.tonymacx86.com/)

