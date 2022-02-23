---
title: WebRTC03入门教程01
date: 2018-08-27 09:23:39
categories: [WebRTC]
tags: [tutorial]
---

[WebRTC教程](https://www.tutorialspoint.com/webrtc/index.htm)

<!---more--->

# Home

WebRTC（网页实时通讯）技术可以很容易地让人们在网页实现音频、视频连接。这个教程中，我们会解释如何用WebRTC快速建立一个peer-to-peer的连接。

**受众**
开发者。
**条件**
WebRTC用于赋予浏览器和移动App实时通信的能力。

# 概览

尽管WebRTC发布于2011年5月，但它至今仍在发展和改进。
**IETF (Internet Engineering Task Force)**网页浏览器组在RTC做了一系列协议的标准化。
http://tools.ietf.org/wg/rtcweb/
**W3C (World Wide Web Consortium)**在APIs上做了标准化。
http://www.w3.org/2011/04/webrtc/

## 基本格局



WebRTC可以让你快速建立p2p连接。你需要有框架和一些能力来处理一些典型的问题比如，数据丢失，连接中断和NAT跨越。这在都在http://www.webrtc.org/的开源资源中。



`WebRTC应用` --> `WebRTC API` `媒体捕捉` `编码解码音视频` `传输层` `节点管理` 

WebRTC的API包括 

- 媒体捕捉

- 编码解码音视频

  这种算法叫做**codec**，有很多很多，这些**codecs**由不同的公司在维护用于不同的商业目的。WebRTC中有几种**codec**比如H.264,iSAC,Opus和VP8。当两个浏览器连接起来，他们为用户选择最匹配最合适的**codec**。

- 传输层

  管理包的顺序。处理丢包。连接用户。

- 节点管理

  管理，打开，阻止连接。



## 浏览器兼容

在这里检测

https://caniuse.com/#feat=rtcpeerconnection

## 使用场景

- 实时交易
- 实时广告
- 下班后交流
- HR管理
- 社交网络
- 数据服务
- 在线医疗
- 金融服务
- 监视
- 多人游戏
- 在线广播
- 在线教育



# 结构体系

![](https://www.tutorialspoint.com/webrtc/images/architecture.jpg)

三个不同层：

- web开发者API
- 浏览器厂家API
- 浏览器厂家可以hook的可覆盖的API



## WebRTC API

包括一些主要的js对象

- RTCPeerConnection

  建立连接用的

  例子：

  ```javascript
  var conn = new RTCPeerConnection(conf); 
  conn.onaddstream = function(stream) { 
     // use stream here 
  }; 
  ```

  

- MediaStream

  音视频处理

  例子：

  创建一个HTML网页：

  ```html
  <html>
     <head> 
        <meta charset = "utf-8"> 
     </head>
  	
     <body> 
        <video autoplay></video> 
        <script src = "client.js"></script> 
     </body> 
  	 
  </html> 
  ```

  再加一个`client.js`文件：

  ```javascript
  //checks if the browser supports WebRTC 
  
  function hasUserMedia() { 
     navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia 
        || navigator.mozGetUserMedia || navigator.msGetUserMedia; 
     return !!navigator.getUserMedia; 
  }
   
  if (hasUserMedia()) { 
     navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia
        || navigator.mozGetUserMedia || navigator.msGetUserMedia;
  		
     //get both video and audio streams from user's camera 
     navigator.getUserMedia({ video: true, audio: true }, function (stream) { 
        var video = document.querySelector('video'); 
  		
        //insert stream into the video tag 
        video.src = window.URL.createObjectURL(stream); 
     }, function (err) {}); 
  	
  }else {
     alert("Error. WebRTC is not supported!"); 
  }
  ```

  然后打开那个HTML网页就能看到你自己啦~

- RTCDataChannel

  通过RTCPeerConnection对象来创建信道

  例子：

  ```javascript
  var peerConn = new RTCPeerConnection(); 
  
  //establishing peer connection 
  //... 
  //end of establishing peer connection 
  var dataChannel = peerConnection.createDataChannel("myChannel", dataChannelOptions); 
  
  // here we can start sending direct messages to another peer 
  ```

  

# 环境

这里作者用的就是 HTML+JS+Node.js

安装好后。在终端输入 `node`测试nodejs工作了。

然后用Node.js的WebSockets库来搭建信令服务器。

`npm install ws`安装WebSocket

为了测试信令服务器，`npm install -g wscat`安装wscat.

| S.No | Protocols & Description                                      |
| ---- | ------------------------------------------------------------ |
| 1    | [WebRTC Protocols](https://www.tutorialspoint.com/webrtc/webrtc_protocols.htm)WebRTC applications use UDP (User Datagram Protocol) as the transport protocol. Most web applications today are built with the using of the TCP (Transmission Control Protocol) |
| 2    | [Session Description Protocol](https://www.tutorialspoint.com/webrtc/webrtc_session_description_protocol.htm)The SDP is an important part of the WebRTC. It is a protocol that is intended to describe media communication sessions. |
| 3    | [Finding a Route](https://www.tutorialspoint.com/webrtc/webrtc_finding_route.htm)In order to connect to another user, you should find a clear path around your own network and the other user's network. But there are chances that the network you are using has several levels of access control to avoid security issues. |
| 4    | [Stream Control Transmission Protocol](https://www.tutorialspoint.com/webrtc/webrtc_sctp.htm)With the peer connection, we have the ability to send quickly video and audio data. The SCTP protocol is used today to send blob data on top of our currently setup peer connection when using the RTCDataChannel object. |

  

# MediaStream APIs

这个API用于轻松从本地的摄像头麦克风获取流媒体。`getUserMedia()`方法是最常用的。

关键点：

- 一个流对象（音频/视频）呈现一个实时媒体
- 在抓取这些媒体流之前，会询问用户的授权
- 输入设备的选择是可用API规定的。

每个MediaSteam对象包含多个MediaSteamTrack对象。他们展示不同输入设备输入进来的音频、视频。

每个MediaSteamTrack对象可能包含多个频道（左/右声道）。

---

输出MediaSteam对象有两种方法，1，输出到一个video或audio元素中。2，发送输出给RTCpeerConnection对象，它可以再发送给更远的peer。

## 使用

又举了一遍上面举过的html+client.js的例子。

## API

### 特性

- **MediaStream.active(read only)** 如果激活了返回true
- **MediaSteam.ended(read only,deprecated)** 如果流没有到达，返回<u>false</u>；如果事件对象已经被解除（说明流已经被读完），返回<u>true</u>
- **MediaSteam.id(read only)**对象的唯一id
- **MediaSteam.label(read only, deprecated)**  根据用户代理分配的唯一标识
  你可以在浏览器中console查看这些特性

![image-20180829102518714](../../../../../../../var/folders/r1/fl4npcxs78q5kh714tg987wm0000gn/T/abnerworks.Typora/image-20180829102518714.png)

### 事件句柄

- **MediaStream.onactive** −  一个MediaStream 对象变成激活的*active* 事件的句柄 
- **MediaStream.onaddtrack** − 添加了新的* *MediaStreamTrack* 对象后的句柄
- **MediaStream.onended (deprecated)** − 结束并解除的句柄
- **MediaStream.oninactive** − 一个 *MediaStream*对象变成激活状态后的 *inactive* 时间句柄
- **MediaStream.onremovetrack** −  一个 *MediaStreamTrack* 对象被激活后的 *removetrack*事件句柄

### 方法

- **MediaStream.addTrack()** − 添加 *MediaStreamTrack* 对象到MediaStream. 如果这个Track已经添加则什么都不做。
- **MediaStream.clone()** − 返回一个有新ID的MediaStream对象。
- **MediaStream.getAudioTracks()** − 从*MediaStream* 对象中返回一个list音频 *MediaStreamTrack* 对象 
- **MediaStream.getVideoTracks()** − 类比上一个
- **MediaStream.getTrackById()** − 返回trackID。 如果argument为空返回null。如果多个tracks ID相同返回第一个。
- **MediaStream.getTracks()** − 返回一个 *MediaStream*对象的所有 *MediaStreamTrack*对象
- **MediaStream.removeTrack()** − 从MediaSteam中移除 *MediaStreamTrack*对象。如果这个track已经被移除则什么也不做

例子

```html
<!DOCTYPE html> 
<html lang = "en">
 
   <head> 
      <meta charset = "utf-8" /> 
   </head>
	
   <body> 
      <video autoplay></video> 
      <div><button id = "btnGetAudioTracks">getAudioTracks()
         </button></div> 
      <div><button id = "btnGetTrackById">getTrackById()
         </button></div> 
      <div><button id = "btnGetTracks">getTracks()</button></div> 
      <div><button id = "btnGetVideoTracks">getVideoTracks()
         </button></div> 
      <div><button id = "btnRemoveAudioTrack">removeTrack() - audio
         </button></div> 
      <div><button id = "btnRemoveVideoTrack">removeTrack() - video
         </button></div> 
      <script src = "client.js"></script> 
   </body> 
	
</html>
```

```javascript
var stream;
  
function hasUserMedia() { 
   //check if the browser supports the WebRTC 
   return !!(navigator.getUserMedia || navigator.webkitGetUserMedia || 
      navigator.mozGetUserMedia); 
} 
 
if (hasUserMedia()) {
   navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia
      || navigator.mozGetUserMedia; 
		
   //enabling video and audio channels 
   navigator.getUserMedia({ video: true, audio: true }, function (s) { 
      stream = s; 
      var video = document.querySelector('video'); 
		
      //inserting our stream to the video tag     
      video.src = window.URL.createObjectURL(stream); 
   }, function (err) {}); 
	
} else { 
   alert("WebRTC is not supported"); 
}
  
btnGetAudioTracks.addEventListener("click", function(){ 
   console.log("getAudioTracks"); 
   console.log(stream.getAudioTracks()); 
});
  
btnGetTrackById.addEventListener("click", function(){ 
   console.log("getTrackById"); 
   console.log(stream.getTrackById(stream.getAudioTracks()[0].id)); 
});
  
btnGetTracks.addEventListener("click", function(){ 
   console.log("getTracks()"); 
   console.log(stream.getTracks()); 
});
 
btnGetVideoTracks.addEventListener("click", function(){ 
   console.log("getVideoTracks()"); 
   console.log(stream.getVideoTracks()); 
});

btnRemoveAudioTrack.addEventListener("click", function(){ 
   console.log("removeAudioTrack()"); 
   stream.removeTrack(stream.getAudioTracks()[0]); 
});
  
btnRemoveVideoTrack.addEventListener("click", function(){ 
   console.log("removeVideoTrack()"); 
   stream.removeTrack(stream.getVideoTracks()[0]); 
});
```

# RTCDataChannel APIs

WebRTC不仅擅长发送音频和视频，还可能是任意数据。这就是RTCDataChannel对象的功能。

## RTCDataChannel API

### 特性

- **RTCDataChannel.label (read only)** − 返回一个数据信道名的字符串

- **RTCDataChannel.ordered (read only)** − 如果消息投递顺序有保障返回true。没保证返回false。

- **RTCDataChannel.protocol (read only)** −返回这个信道使用的子协议名的字符串。

- **RTCDataChannel.id (read only)** − 返回RTCDataChannel对象创建时的唯一id

- **RTCDataChannel.readyState (read only)** − 返回 RTCDataChannelState enum描述连接状态。

  可能的值：

  - **connecting** − 候选的连接还没有激活. 这是初始化状态.
  - **open** − 候选的连接正在运行.
  - **closing** − Indicates that the connection正在关闭ing. The cached messages are in the process of being sent or received, but no newly created task is accepting.
  - **closed** − Indicates that the connection could not be established or has been shut down.

- **RTCDataChannel.bufferedAmount (read only)** − Returns the amount of bytes that have been queued for sending. This is the amount of data that has not been sent yet via RTCDataChannel.send().

- **RTCDataChannel.bufferedAmountLowThreshold** − Returns the number of bytes at which the RTCDataChannel.bufferedAmount is taken up as low. When the RTCDataChannel.bufferedAmount decreases below this threshold, the bufferedamountlow event is fired.

- **RTCDataChannel.binaryType** − Returns the type of the binary data transmitted by the connection. Can be “blob” or “arraybuffer”.

- **RTCDataChannel.maxPacketLifeType (read only)** − Returns an unsigned short that indicates the length in milliseconds of the window in when messaging is going in unreliable mode.

- **RTCDataChannel.maxRetransmits (read only)** − Returns an unsigned short that indicates the maximum number of times a channel will retransmit data if it is not delivered.

- **RTCDataChannel.negotiated (read only)** − Returns a boolean that indicates if the channel has been negotiated by the user-agent, or by the application.

- **RTCDataChannel.reliable (read only)** − Returns a boolean that indicates of the connection can send messages in unreliable mode.

- **RTCDataChannel.stream (read only)** − Synonym for RTCDataChannel.id

### Event Handlers

- **RTCDataChannel.onopen** − This event handler is called when the open event is fired. This event is sent when the data connection has been established.
- **RTCDataChannel.onmessage** − This event handler is called when the message event is fired. The event is sent when a message is available on the data channel.
- **RTCDataChannel.onbufferedamountlow** − This event handler is called when the bufferedamoutlow event is fired. This event is sent when RTCDataChannel.bufferedAmount decreases below the RTCDataChannel.bufferedAmountLowThreshold property.
- **RTCDataChannel.onclose** − This event handler is called when the close event is fired. This event is sent when the data connection has been closed.
- **RTCDataChannel.onerror** − This event handler is called when the error event is fired. This event is sent when an error has been encountered.

### Methods

- **RTCDataChannel.close()** − Closes the data channel.
- **RTCDataChannel.send()** − Sends the data in the parameter over the channel. The data can be a blob, a string, an ArrayBuffer or an ArrayBufferView.



未完。




<Center>翻译自https://www.tutorialspoint.com/webrtc/index.htm没有全文翻译。侵权删。</Center>