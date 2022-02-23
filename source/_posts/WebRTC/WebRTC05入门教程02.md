---
title: WebRTC05入门教程02
date: 2018-08-30 14:29:44
categories: [WebRTC]
tags: [tutorial,Demo]
---

p2p的核心**RTCPeerConnection APIs**的介绍

<!---more--->

# RTCPeerConnection APIs

简单样例：`var pc = RTCPeerConnection(config);`

config包含 key, iceServers。这是一个有着STUN和TURN服务器信息的URL对象数组，用于查找ICE候选。你可以在https://code.google.com找到一些可用的公共STUN服务器.

这是user's flow用户流的一个例子：

- 注册*onincecandidate*句柄。收到时发送ICE candidates给其他peer。
- 注册*onaddstream*句柄。一旦收到远端peer接收，则控制视频流的展示
- 注册*message*句柄。你的信令服务器应该也有一个句柄用于收消息。如果message包含*RTCSeesionDescription*对象，则使用*setRemoteDescription()*方法将其加入到<u>*RTCPeerConnection*</u><u>对象</u>。如果message包含*RTCIceCandidate*对象，使用*addIceCandidate()*方法将其加入到<u>*RTCPeerConnection*</u><u>对象</u>。
- 用*getUserMedia()*设置本地媒体流，用 *addStream()* 方法将其加入到<u>*RTCPeerConnection*</u><u>对象</u>。
- 开始 **offer/answer** 协商。这是唯一一个[主叫流caller flow]和[被叫callee]有所不同的一步。caller用**<u>*createOffer()*</u>**方法开始协商，注册一个接收 *<u>RTCSessionDescription</u>*对象的callback。这个callback应使用*setLocalDescriptionI()*方法添加这个*<u>RTCSessionDescription</u>*到你的*RTCPeerConnection*。  最后，caller应该用信令服务器发送这个*<u>RTCPeerConnection</u>*到远端peer。 callee注册相同的callback，但是用的是**<u>*createAnswer()*</u>**方法。仅在收到caller的**offer**后callee flow初始化完成。

## RTCPeerConnection API

### 特性

- **RTCPeerConnection.iceConnectionState (read only)** − 返回一个RTCIceConnectionState

  enum描述连接状态.  值改变时触发一个iceconnectionstatechange 事件。

  可能的值：

  - **new** − ICE代理在等待远程候选或收集地址。
  - **checking** − ICE 代理 有远程候选但还没有发现连接。
  - **connected** − ICE 代理已经发现了可用连接，但仍然在checking更远的候选以便更好地连接。
  - **completed** − ICE 代理已经发现了可用连接并停止检测远程候选。
  - **failed** − ICE 代理已经检查完所有的远程候选们但找不到一个可匹配的。
  - **disconnected** − 至少有一个部分不再工作。
  - **closed** − ICE 代理关闭。

- **RTCPeerConnection.iceGatheringState (read only)** − 返回一个 RTCIceGatheringState enum描述连接的ICE收集状态−

  - **new** − 对象刚被创建
  - **gathering** − ICE 代理在收集候选过程中
  - **complete** ICE 代理 已经完成收集

- **RTCPeerConnection.localDescription (read only)** − 返回一个RTCSessionDescription 描述本地节点。如果还没有被设置则为null

- **RTCPeerConnection.peerIdentity (read only)** − 返回一个 RTCIdentityAssertion. 包含一个idp(domain name) 和一个描述远程peer的name

- **RTCPeerConnection.remoteDescription (read only)** − 返回一个 RTCSessionDescription 描述远程节点. 没设置为null

- **RTCPeerConnection.signalingState (read only)** − 返回一个 RTCSignalingState enum描述本地连接的信令状态。这个状态描述SDP offer。值改变时触发一个signalingstatechange 事件。可能的值： 

  - **stable** − 初始状态。不存在 SDP offer/answer 交换。
  - **have-local-offer** − 连接的本地端已经在当地申请了一个SDP offer.
  - **have-remote-offer** − 连接的远程端已经在当地申请了一个SDP offer.
  - **have-local-pranswer** − 一个远程SDP offer已申请，本地已申请一个SDP pranswer.
  - **have-remote-pranswer** − 一个本地SDP已申请，远程已申请一个SDP pranswer.
  - **closed** − 连接关闭。

### 事件句柄

下面是常用的几个

|                                   Event Handlers | Description                                                  |
| -----------------------------------------------: | :----------------------------------------------------------- |
|                **RTCPeerConnection.onaddstream** | addstream 事件触发. 当MediaSteam被远程peer添加到连接中时发送这个事件。 |
|              **RTCPeerConnection.ondatachannel** | datachannel 事件触发. 当RTCDataChannel添加到连接中时发送这个事件。 |
|             **RTCPeerConnection.onicecandidate** | Icecandidate 事件触发. 当RTCIceCandidate对象添加到script中时发送这个事件。 |
| **RTCPeerConnection.oniceconnectionstatechange** | This handler is called when Iceconnectionstatechange 事件触发时. This event is sent 当value of iceConnectionState changes. |
|           **RTCPeerConnection.onidentityresult** | This handler is called when Identityresult 事件触发时. This event is sent when an identity assertion is generated during the creating of an offer or an answer of via getIdentityAssertion(). |
|        **RTCPeerConnection.onidpassertionerror** | This handler is called when Idpassertionerror 事件触发时. This event is sent when IdP (Identitry Provider) finds an error while generating an identity assertion. |
|            **RTCPeerConnection.onidpvalidation** | This handler is called when Idpvalidationerror 事件触发时. This event is sent when IdP (Identitry Provider) finds an error while validating an identity assertion. |
|        **RTCPeerConnection.onnegotiationneeded** | This handler is called 当negotiationneeded 事件触发时. This event is sent by the browser to inform the negotiation will be required at some point in the future. |
|             **RTCPeerConnection.onpeeridentity** | This handler is called 当peeridentity 事件触发时. This event is sent when a peer identity has been set and verified on this connection. |
|             **RTCPeerConnection.onremovestream** | This handler is called 当signalingstatechange 事件触发时. This event is sent 当value of signalingState changes. |
|     **RTCPeerConnection.onsignalingstatechange** | This handler is called 当removestream 事件触发时. This event is sent when a MediaStream is removed from this connection. |

### Methods

下面是常用的几个

| S.No. | Methods & Description                                        |
| ----- | ------------------------------------------------------------ |
| 1     | **RTCPeerConnection()**返回一个 new RTCPeerConnection object. |
| 2     | **RTCPeerConnection.createOffer()**Creates an offer(request) to find a remote peer. The two first parameters of this method are success and error callbacks. The optional third parameter are options, like enabling audio or video streams. |
| 3     | **RTCPeerConnection.createAnswer()**Creates an answer to the offer received by the remote peer during the offer/answer negotiation process. The two first parameters of this method are success and error callbacks. The optional third parameter are options for the answer to be created. |
| 4     | **RTCPeerConnection.setLocalDescription()**Changes the local connection description. The description defines the properties of the connection. The connection must be able to support both old and new descriptions. The method takes three parameters, RTCSessionDescription object, callback if the change of description succeeds, callback if the change of description fails. |
| 5     | **RTCPeerConnection.setRemoteDescription()**Changes the remote connection description. The description defines the properties of the connection. The connection must be able to support both old and new descriptions. The method takes three parameters, RTCSessionDescription object, callback if the change of description succeeds, callback if the change of description fails. |
| 6     | **RTCPeerConnection.updateIce()**Updates ICE 代理 process of pinging remote candidates and gathering local candidates. |
| 7     | **RTCPeerConnection.addIceCandidate()**Provides a remote candidate to ICE 代理. |
| 8     | **RTCPeerConnection.getConfiguration()**返回一个 RTCConfiguration object. It represents the configuration of the RTCPeerConnection object. |
| 9     | **RTCPeerConnection.getLocalStreams()**返回一个n array of local MediaStream connection. |
| 10    | **RTCPeerConnection.getRemoteStreams()**返回一个n array of remote MediaStream connection. |
| 11    | **RTCPeerConnection.getStreamById()**Returns local or remote MediaStream by the given ID. |
| 12    | **RTCPeerConnection.addStream()**Adds a MediaStream as a local source of video or audio. |
| 13    | **RTCPeerConnection.removeStream()**Removes a MediaStream as a local source of video or audio. |
| 14    | **RTCPeerConnection.close()**Closes a connection.            |
| 15    | **RTCPeerConnection.createDataChannel()**Creates a new RTCDataChannel. |
| 16    | **RTCPeerConnection.createDTMFSender()**Creates a new RTCDTMFSender, associated to a specific MediaStreamTrack. Allows to send DTMF (Dual-tone multifrequency) phone signaling over the connection. |
| 17    | **RTCPeerConnection.getStats()**Creates a new RTCStatsReport that contains statistics concerning the connection. |
| 18    | **RTCPeerConnection.setIdentityProvider()**Sets IdP. Takes three parameters − the name, the protocol used to communicate and an optional username. |
| 19    | **RTCPeerConnection.getIdentityAssertion()**Gathers an identity assertion. It is not expected to deal with this method in the application. So you may call it explicitly only to anticipate the need. |

### 建立一个连接

先把信令服务器跑起来。

代码：`server.js`

```javascript
//信令服务器代码请转到入门教程03
```
然后`node server` 把上面的信令服务器跑起来。

（教程01说过要安装好nodejs环境）

如果想测试是否跑起来了，可以用wscat命令：

`wscat -c ws://localhost:9090` 



然后是前端：`index.html`

```html
<html lang = "en"> 
   <head> 
      <meta charset = "utf-8" /> 
   </head>
	
   <body> 
	
      <div> 
         <input type = "text" id = "loginInput" /> 
         <button id = "loginBtn">Login</button> 
      </div> 
	
      <div> 
         <input type = "text" id = "otherUsernameInput" />
         <button id = "connectToOtherUsernameBtn">Establish connection</button> 
      </div> 
		
      <script src = "client.js"></script>
		
   </body>
	
</html>
```

这个不用解释吧。就是两个输入框两个按钮。



最后是客户端js文件：`client.js`

```javascript
var connection = new WebSocket('ws://localhost:9090'); 
var name = ""; 
 
var loginInput = document.querySelector('#loginInput'); 
var loginBtn = document.querySelector('#loginBtn'); 
var otherUsernameInput = document.querySelector('#otherUsernameInput'); 
var connectToOtherUsernameBtn = document.querySelector('#connectToOtherUsernameBtn'); 
var connectedUser, myConnection;
  
//当一个用户点击登录 
loginBtn.addEventListener("click", function(event){ 
   name = loginInput.value; 
   
   if(name.length > 0){ //发送一个message{ 
         type: "login", 
         name: name 
      }
      send({ 
         type: "login", 
         name: name 
      }); 
   } 
   
});
  
//handle messages from the server 
connection.onmessage = function (message) { 
   console.log("Got message", message.data);
   var data = JSON.parse(message.data); 
   
   switch(data.type) { 
      case "login": 
         onLogin(data.success); 
         break; 
      case "offer": 
         onOffer(data.offer, data.name); 
         break; 
      case "answer": 
         onAnswer(data.answer); 
         break; 
      case "candidate": 
         onCandidate(data.candidate); 
         break; 
      default: 
         break; 
   } 
};
  
//当用户登录
function onLogin(success) { 

   if (success === false) { //重名了
      alert("oops...try a different username"); 
   } else { 
      //创建RTCPeerConnection对象 
      
      var configuration = { 
         "iceServers": [{ "url": "stun:stun.1.google.com:19302" }] 
      }; 
      
      myConnection = new webkitRTCPeerConnection(configuration); 
      console.log("RTCPeerConnection object was created"); 
      console.log(myConnection); 
  
      //setup ice handling
      //当浏览器发现一个ICE候选我们就发送给其他人。 
      myConnection.onicecandidate = function (event) { 
      
         if (event.candidate) { 
            send({ 
               type: "candidate", 
               candidate: event.candidate 
            }); 
         } 
      }; 
   } 
};
  
connection.onopen = function () { 
   console.log("Connected"); 
};
  
connection.onerror = function (err) { 
   console.log("Got error", err); 
};
  
// 发送JSON格式message的Alias(别名) 
function send(message) { 

   if (connectedUser) { 
      message.name = connectedUser; 
   } 
   
   connection.send(JSON.stringify(message)); 
};

//setup a peer connection with another user 
connectToOtherUsernameBtn.addEventListener("click", function () { 
 
   var otherUsername = otherUsernameInput.value; 
   connectedUser = otherUsername;
   
   if (otherUsername.length > 0) { 
      //make an offer 
      myConnection.createOffer(function (offer) { 
         console.log(); 
         send({ 
            type: "offer", 
            offer: offer 
         });
         
         myConnection.setLocalDescription(offer); 
      }, function (error) { 
         alert("An error has occurred."); 
      }); 
   } 
}); 
 
//当有人想打给我们 
function onOffer(offer, name) { 
   connectedUser = name; 
   myConnection.setRemoteDescription(new RTCSessionDescription(offer)); 
   
   myConnection.createAnswer(function (answer) { 
      myConnection.setLocalDescription(answer); 
      
      send({ 
         type: "answer", 
         answer: answer 
      }); 
      
   }, function (error) { 
      alert("oops...error"); 
   }); 
}
  
//另一个用户要answer我们的offer
function onAnswer(answer) { 
   myConnection.setRemoteDescription(new RTCSessionDescription(answer)); 
} 
 
//当我们收到ICE候选
function onCandidate(candidate) { 
   myConnection.addIceCandidate(new RTCIceCandidate(candidate)); 
}
```



这样 **offer/answer**的过程就模拟完了。可以通过输入输出在控制台看到相关信息.



## 小知识点

`alisa`在 linux 中，alias 命令（注意全为小写）的功能是设置命令的别名，以简写命令，提高操作效率。根据参数的不同，该命令可查看已设定的别名，或为命令设置新的别名。对于用户自定义别名，仅当前登录期内有效；也可修改配置文件使其长期有效。

相关命令：`unalias`

参考链接：https://baike.baidu.com/item/Alias/3105303#viewPageContent