---
title: WebRTC02查基础资料
date: 2018-08-26 14:40:33
categories: [WebRTC]
tags: [Note]
---

本来第一站是要查资料先了解下知识点的。但是王老师直接就给了我iOS的源码，这样又了Demo对着，了解更好了。不多说了。最近的任务就是多看WebRTC的相关文章。把该知道的多学一点。

<!---more--->


# 服务器

## Room Server

房间服务器。创建、管理通话状态。
是双方还是多方通话。加入离开房间等等。

## Signaling Server

信令服务器。
管理和协助终端建立p2p通话。

- 任务

    - 控制通信[发起/结束]的连接控制消息。
    - 发生错误时，相互通告
    - 媒体流 元数据【解码器、带宽、媒体类型等等】
    - 两两之间建立安全连接的关键数据
    - 外界能看到的网络上的数据【ip、端口等】

## STUN/ TURN/ ICE Server

> 参考阅读：
> [《P2P技术详解(一)：NAT详解——详细原理、P2P简介》](http://www.52im.net/thread-50-1-1.html)
> [《P2P技术详解(二)：P2P中的NAT穿越(打洞)方案详解》](http://www.52im.net/thread-542-1-1.html)
> [《P2P技术详解(三)：P2P技术之STUN、TURN、ICE详解》](http://www.52im.net/thread-557-1-1.html)

防火墙打洞服务器

![](http://webrtc.org.cn/wp-content/uploads/2016/06/nat-network.png)

如图所示，由于有网络防火墙或配置NAT的路由器。导致我们的计算机ip地址不是广域网的ip地址。因此需要打洞～

- STUN (Simple Traversal of UDP over NATs)
NAT的UDP简单穿越

确定**内网终端**暴漏在**广域网** 的ip、端口、NAT信息。

协助**不同内网**之间的计算机建立p2p的**UDP通讯**

解决了家用路由环境的打洞问题。但是对于大部分企业的网络环境就不是很好了

> 为什么呢？企业的网络环境有什么不一样？


这是就需要TURN协议了。

- TURN（Traversal Using Relay NAT）
允许在TCP或UDP的连线上跨越 NAT 或防火墙.
> Relay--中继动作

Client-Server协议。

**【[客户]】**在通讯前先与**服务器**交互，要求**服务器**产生[relay port]**接口**，这就是中继跨越**新地址**。这时**服务器**会建立**[peer]**，即**remote endpoints远方终端**，开始**relay中继**动作。**【[客户端]】**利用**接口**将资料传送至**[peer]**，再由**[peer]**传给另一个**【[终端]】**。通过服务器产生新的**[peer]**来进行数据的中转。

- ICE协议

综合前两种的方案。

通过offer/answer模型建立基于UDP的通讯。 ICE是offer/answer模型的扩展，通过在offer和answer的SDP(Session Description Protocol)里面包含多种IP地址和端口，然后对本地SDP和远程SDP里面的IP地址进行配对，然后通过P2P连通性检查进行连通性测试工作，如果测试通过即表明该传输地址对可以建立连接。其中IP地址和端口（也就是地址）有以下几种：本机地址、通过 STUN服务器反射后获取的server-reflexive地址（内网地址被NAT映射后的地址）、relayed地址（和 TURN转发服务器相对应的地址）及Peer reflexive地址等。

- 概览

| 特性                   | STUN                                                         | TURN                                                         | ICE                                                          |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 实现复杂度             | 实现简单                                                     | 难于实现。TURN的安全性设计增加终端设置的复杂度               | 一般                                                         |
| TCP穿透支持            | 不支持                                                       | 支持                                                         | 支持                                                         |
| 对现有设备的要求       | 要求客户端支持，对现有NAT设备无改动要求，需增加STUN服务器    | 对现有NAT设备无要求，要求客户端支持，需增加TURN服务器        | 对NAT设备无要求，支持所有类型的NAT设备。客户端必须支持，网路结构中需增加STUN/TURN服务器 |
| 可扩展性               | 可扩展性好，与具体协议无关                                   | 可扩展性好，与具体协议无关                                   | 可扩展性好，与具体协议无关                                   |
| 安全性                 | 一般                                                         | 一般                                                         | 较好                                                         |
| 健壮性                 | 差，不支持symmentric型NAT                                    | 好，支持所有类型的NAT                                        | 好，适用与所有NAT及NAT拓扑类型，且由于存在中继服务器，NAT 穿透一般总是能成功 |
| 穿透一般总是能成功其他 | 支持自动检测NAT类型，使用户即使在使用STUN协议无法实现NAT穿透时还可以根据NAT类型自主选择其他可使用的NAT穿透方案 | 与P2P穿透方式相比，性能是relay穿透方式的弱点。另外TURN无法实现负载分担，解决的方式是把media relay服务器的分配工作放在 SIP proxy完成 |                                                              |

# 小知识点

## GAE

Google App Engine
谷歌的Web应用开发、托管平台。支持Python、Java和Php。

## HLS(HTTP Live Streaming)

https://en.wikipedia.org/wiki/HTTP_Live_Streaming
https://baike.baidu.com/item/HLS/8328931

## H.264
国际上制定视频编解码技术的组织有两个，一个是“国际电联（ITU-T）”，它制定的标准有H.261、H.263、H.263+等，另一个是“国际标准化组织（ISO）”它制定的标准有MPEG-1、MPEG-2、MPEG-4等。而H.264则是由两个组织联合组建的联合视频组（JVT）共同制定的新数字视频编码标准，所以它既是ITU-T的H.264，又是ISO/IEC的MPEG-4高级视频编码（Advanced Video Coding，AVC）的第10 部分。因此，不论是MPEG-4 AVC、MPEG-4 Part 10，还是ISO/IEC 14496-10，都是指H.264。

## Scaledrone

Scaledrone is a realtime messaging service and platform. Send live updates, create chatrooms and collaborative tools.

一个平台。
这是这个平台的Demo
https://scaledrone.github.io/webrtc/index.html#12345房间号   貌似不太行啊。

https://www.scaledrone.com/blog/webrtc-tutorial-simple-video-chat/
基础教学

# 总结

了解了打洞的定义。路还很长啊。

