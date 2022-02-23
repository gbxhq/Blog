---
title: Mac Useful Tips
date: 2018-11-15 16:01:54
categories: Log
tags: [tips,Mac]
---

个人记录Mac使用的一些姿势。遇到的问题、需求就记下来。

<!---more--->

# Mac打开SSH服务

mac本身安装了ssh服务，默认情况下不会开机自启

启动sshd服务：

`sudo launchctl load -w /System/Library/LaunchDaemons/ssh.plist`

停止sshd服务：
`sudo launchctl unload -w /System/Library/LaunchDaemons/ssh.plist`

---

查看是否启动：
`sudo launchctl list | grep ssh`

如果看到下面的输出表示成功启动了：

`0 com.openssh.sshd`

---

# Mac改hosts

Finder前往:

/private/etc/hosts

把hosts文件先复制出来。改完替换回去。

# Mac下制作macOS安装盘

- 先用磁盘工具抹掉U盘。格式选日志式，方案选GUID分区图。

- `sudo Install\ macOS\ Mojave.app/Contents/Resources/createinstallmedia --volume /Volumes/Mojave Install\ macOS\ Mojave.app --nointeraction`

  其中两次出现的`Install\ macOS\ Mojave.app`是解压dmg包出来一个.app安装程序。

  `--volume /Volumes/Mojave`这个就是你的Volumes名。
  
# macOS 10.14 取消4位数密码限制

打开终端输入：

` pwpolicy -clearaccountpolicies `

然后去设置里改吧


# 环境变量问题

1. 在`.bash`的文件中加路径
   - zsh则是添加到 `.zshrc`中 
2. 手动放快捷方式到`usr/bin`或`usr/local/bin`目录下

> 延伸：Mac系统的bash环境变量，加载顺序为：
> /etc/profile
> /etc/paths
> ~/.bash_profile
> ~/.bash_login
> ~/.profile
> ~/.bashrc

设置PATH的语法都为：

```bash
#中间用冒号隔开
export PATH=$PATH:<PATH 1>:<PATH 2>:<PATH 3>:------:<PATH N>
```

# 显示/隐藏文件

在Finder：`Command+Shift+.`

# .app已损坏 打不开 

`sudo spctl --master-disable`

# 打开macOS原生的NTFS

**PS:这方法不咋好使。老老实实用Tuxera Disk Mananger吧**

- `diskutil list` 找到你要写入的磁盘名

- **开启读写NTFS：**

  `sudo vim /etc/fstab`

  在这个fstab文件里加入一句：

  **`LABEL=你的磁盘名字 none ntfs rw,auto,nobrowse`**

   `:wq `  保存退出

- 重新插入U盘  （此时桌面上看不到了）

  在Finder里 ⌘+⇧+G 输入 `/Volumes` 

# Mac终端下出现bogon的解决办法

`sudo scutil --set HostName your-hostname`

# Mac更改MAC地址（外接网卡）

`sudo ifconfig en9 ether aa:bb:cc:dd:ee`

但是我外接了Type-C转网线的口，找到对应的也是en9，命令运行后，再用`ifconfig`看发现mac地址并没有更改成功。
在网上又搜了搜，原来需要**装驱动**。
这篇文章对这个问题写得相当明白了：https://blog.csdn.net/u014051620/article/details/75050934

# 配置网络：无效的服务器地址 BasicIPv6ValidationError

```
networksetup -listallnetworkservices //列出所有网络服务信息;
networksetup -setv6off "Ethernet 2"  //停止对应网卡的ipV6服务;
networksetup -setmanual "Ethernet 2" 10.10.22.222 255.255.255.0 10.10.22.1 //手动设置
```

# 10.14以后Safari装扩展

cd到有 `.safariextz`文件的目录。

执行`xar -xf 拓展名.safariextz` 就可以解包

然后添加扩展，运行即可。详细教程：https://sspai.com/post/47303

# 外接显示器开启HiDPI

如果你看到这里。我想对你说一句，别想别的了。

老老实实上4K。不差那点钱。在Mac上得到的效果远超你强开HiDPI

~~<https://comsysto.github.io/Display-Override-PropertyList-File-Parser-and-Generator-with-HiDPI-Support-For-Scaled-Resolutions/>~~

# 命令行

Mac下的一些实用的命令行 [https://github.com/chinsyo/commandline](https://github.com/chinsyo/commandline)

隐藏/显示

`chflags hidden abc`
`chflags nohidden abc`

# Launchpad

-   对于默认的 Launchpad 的显示大小进行了调整。可以使用终端进行修改。

    defaults write com.apple.dock springboard-columns -int 8;defaults write com.apple.dock springboard-rows -int 8;defaults write com.apple.dock ResetLaunchPad -bool TRUE;killall Dock

-   数字部分可以更换为你希望的每行图标数和每列的图标数。