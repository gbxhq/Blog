<<<<<<< Updated upstream
---
title: 小米 Root 记录
date: 2022-07-09 23:13:00
categories: Note
tags: [Android]
---
=======
- 安装 SDK

  [SDK 平台工具版本说明  | Android 开发者  | Android Developers (google.cn)](https://developer.android.google.cn/studio/releases/platform-tools?hl=zh-cn)

- 下载面具

  [Releases · topjohnwu/Magisk · GitHub](https://github.com/topjohnwu/Magisk/releases)
>>>>>>> Stashed changes

- 下载对应的固件以提取boot文件

  固件从这找

  https://xiaomirom.com

  记得找线刷包，解压就有`boot.img`文件了

  
  
  手机安装面具。打开选择安装。从修复文件。选择上面的boot.img，会导出一个新的 xxxx.img
  
- 

❯ ./fastboot devices
JB6PUWLJOBV4GEBU	 fastboot
❯ ./fastboot flash boot magisk_patched-26100_tSedC.img
ERROR: could not clear input pipe; result e0005000, ignoring...
ERROR: could not clear output pipe; result e0005000, ignoring....
Sending 'boot_a' (65536 KB)                        OKAY [  1.492s]
Writing 'boot_a'                                   OKAY [  0.284s]
Finished. Total time: 1.869s