---
title: MacLiveSettingNote
date: 2022-05-05 15:39:09
tags: [Mac]
---

# Mac 直播、录屏问题记录

## 音频录制问题

- 安装BlackHole

  （之前都是用 SoundFlower，不过这个神器现在已经不适配 M1 了，所以我们也开始使用 BlackHole）

- 安装好后，在MIDI 设置这个软件里设置

  ![image-20220505154508617](https://cdn.jsdelivr.net/gh/gbxhq/Pic/image-20220505154508617.png)

- 左侧选中 BlackHole，下方添加多输出设备

  <img src="https://cdn.jsdelivr.net/gh/gbxhq/Pic//image-20220505160126899.png" alt="image-20220505160126899" style="zoom:33%;" />

  把你想同时输出的设备都添加上(打钩)、比如音箱+耳机+BlackHole

  > 这一步的意思就是让音频输出到多个地方

  - 点击小喇叭切换输出设备到“多输出”，这样我们解决了多输出问题，

  <img src="https://cdn.jsdelivr.net/gh/gbxhq/Pic//image-20220505160503562.png" alt="image-20220505160503562" style="zoom:33%;" />

  > 选了多输出后，可以实现你的音箱出声，同时别人看你直播也能听到电脑的声音，或者你录屏也把电脑原声给录进去。

  ---

  但是还有个问题没解决，就是麦克风的声音没有被混入 BlackHole。

- 我们再添加一个聚集设备：选择麦克风和 BlackHole

  <img src="https://cdn.jsdelivr.net/gh/gbxhq/Pic//image-20220505160858087.png" alt="image-20220505160858087" style="zoom:33%;" />

  最后到音频设置里选择这个聚集设备，这样就把麦克风的声音也混到BlackHole 了

最后说明一点，多输入和多输出设备都不具备控制（调节音量大小）的能力，需要换到音箱调完再调回去。这个其实点一下菜单栏的小喇叭也很方便。
