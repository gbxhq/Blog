---
title: WebRTC06入门教程03
date: 2018-08-31 14:28:23
categories: [WebRTC]
tags: [tutorial,Demo]
---

信令服务器分析

<!---more--->

# Signaling

## 信令和协商Signaling and Negotiation

用户建立连接的过程以信令和协商为主。有下面几个步骤：

- 为peer连接创建一个潜在候选项的list
- 用户A或应用选择一个要连接的用户B
- 信令层通知用户B有人想和你连。他可以同意/拒绝
- 用户A被通知offer同意
- 用户A初始化与B的RTCPeerConnection
- 俩用户通过信令服务器交换软硬件信息
- 俩用户交换本地信息
- 连接成功/失败

## 建立服务器

我们现在来建立一个自己的信令机制。允许一个用户呼叫另一个。一旦一个用户被呼叫，服务器在他们之间传递offer,answer,ICE候选。然后建立连接。

![信令服务器](https://www.tutorialspoint.com/webrtc/images/building_the_server.jpg)

上个图是用户使用信令服务器时的信息流。

首先，每个用户在服务器注册。传一个简单的字符串username即可。注册后的用户可以相互呼叫。用户1发一个带有他想呼叫的用户id的offer。其他人应当answer。最后，在用户中间发送ICE候选直到他们建立连接。

去创建一个WebRTC连接服务器必须有能力在没有使用WebRTCpeer连接的情况下发送messages。因此我们使用HTML5 WebSockets—一个两端(一个web服务器一个web浏览器)的双向socket连接。现在我们开始使用WebSocket库。创建`server.js`文件并加入以下代码：

```javascript
//依赖ws库 声明一个WebSocketServer服务器
var WebSocketServer = require('ws').Server; 

//创建端口9090的WebSocket服务器
var wss = new WebSocketServer({port: 9090}); 
 
//当有一个用户接入服务器
wss.on('connection', function(connection) { 
   console.log("user connected");
	
   //服务器收到已接入用户的消息
   connection.on('message', function(message){ 
      console.log("Got message from a user:", message); 
   }); 
	
   connection.send("Hello from server"); 
});
```

先要求WebSocket库。再创建9090端口的socket服务器。下一步，监听connection事件。监听用户发来的任何消息。最后我们发送一个回复给已连接的用户说Hello from Server.

终端运行`node server`服务器就跑起来了。

为了测试服务器。我们用`wscat`这个程序。他可以直接连入服务器并测试命令。先在终端让服务器跑起来之后，再开一个终端，运行`wscat -c ws://localhost:9090`命令。

## 用户注册

在我们的信令服务器中，我们将使用基于字符串的username来让我们知道信息的去向。下面更改一下connection的句柄。

```javascript
connection.on('message', function(message) { 
   var data; 
	
   //只接收JSON
   try { 
      data = JSON.parse(message); 
   } catch (e) { 
      console.log("Invalid JSON"); 
      data = {}; 
   } 
	
});
```

这样我们就做到了只接收JSON。下一步我们需要存储所有连接到用户。使用一个简单的js对象。

在我们的文件头部增加一句`var users={};`。

**这个数组里存的都是connection,而下标就是name。**

现在我们还要为每一个从客户端发来的message增加一个*type*域。例如是登录就发*login* type的message。现在来定义。

```javascript
connection.on('message', function(message){
   var data; 
	
   //只接收JSON
   try { 
      data = JSON.parse(message); //是JSON就给它分组
   } catch (e) { 
      console.log("Invalid JSON"); 
      data = {}; 
   }
	
   //分开各种type 
   switch (data.type) { 
      //一个用户尝试登录
      case "login": 
         console.log("User logged:", data.name); 
			
         //存在这个name则拒绝登录
         if(users[data.name]) { 
            sendTo(connection, { 
               type: "login", 
               success: false 
            }); 
         } else { 
            //保存这个用户连接
            users[data.name] = connection; //connection进入users[]
            connection.name = data.name; 
				
            sendTo(connection, { 
               type: "login", 
               success: true 
            });
				
         } 
			
         break;
					 
      default: 
         sendTo(connection, { 
            type: "error", 
            message: "Command no found: " + data.type 
         }); 
			
         break; 
   } 
	
});
```

下面这一段代码是发送消息到连接的辅助函数。这个函数可以确保我们发送的消息都是JSON格式。

```javascript
function sendTo(connection, message) { 
   connection.send(JSON.stringify(message)); 
}
```

你可以在wscat发送一段json来测试一下了。

## 呼叫

登录后的用户想要呼叫就要做一个offer发给别人。现在我们来添加*offer*句柄。

```javascript
case "offer": 
   //for ex. A
   console.log("Sending offer to: ", data.name); 

   //如果B存在则发送A的offer细节
   var conn = users[data.name]; 
	
   if(conn != null){ 
      //设置A的连接对象是B
      connection.otherName = data.name;
       //A的offer发送给B
      sendTo(conn, { 
         type: "offer", 
         offer: data.offer, 
         name: connection.name 
      }); 
   }
	
   break;
```

## 接听

接听回话和*offer*句柄类似。在*offer*句柄后面加入*answer*，answer的内容无论是什么都会被发送。

```javascript
case "answer": 
   console.log("Sending answer to: ", data.name); 
	
   //for ex. UserB answers UserA 
   var conn = users[data.name]; 
	
   if(conn != null) { 
       //同理回了人家的answer你的连接对象也就是他了
      connection.otherName = data.name; 
      sendTo(conn, { 
         type: "answer", 
         answer: data.answer 
      }); 
   }
	
   break;
```

在例子中，offer和answer都是简单的字符串。但在真正的应用中他们会被SDP数据填充。

## ICE候选

最后一部分是处理用户之间的ICE候选。我们在用户中间用相同的机制通过message。主要的不同就是候选消息可能会多次、无序地发送给每个用户。添加*candidate*句柄：

```javascript
case "candidate": 
   console.log("Sending candidate to:",data.name); 
   var conn = users[data.name]; 
	
   if(conn != null) {
      sendTo(conn, { 
         type: "candidate", 
         candidate: data.candidate 
      }); 
   }
	
   break;
```

## 断开对话

为了让用户之间断开对话。我们要一个挂起函数。她同时会告诉服务器删掉所有的用户引用。添加*leave*句柄：

```javascript
case "leave": 
   console.log("Disconnecting from", data.name); 
   var conn = users[data.name]; 
   conn.otherName = null; 
	
   //notify the other user so he can disconnect his peer connection 
   if(conn != null) { 
      sendTo(conn, { 
         type: "leave" 
      }); 
   } 
	
   break;
```

同时吧leave事件发送给另一个用户，让他也你能相应的断开对话。

当用户从信令服务器中丢弃掉连接的时候我们还需要有*close*句柄。

```javascript
connection.on("close", function() { 

   if(connection.name) { 
      delete users[connection.name]; 
		
      if(connection.otherName) { 
         console.log("Disconnecting from ", connection.otherName); 
         var conn = users[connection.otherName]; 
         conn.otherName = null;
			
         if(conn != null) { 
            sendTo(conn, { 
               type: "leave" 
            }); 
         }  
      } 
   } 
});
```

信令服务器完成。

## 完整的代码

```javascript
//依赖ws库
var WebSocketServer = require('ws').Server;
 
//开9090端口。服务器名字叫wss
var wss = new WebSocketServer({port: 9090}); 

//用户群组。里面存的是connection。下标是name。
var users = {};
  
//有人要连接时 
wss.on('connection', function(connection) {
  
   console.log("User connected");
	
   //服务器收到了message
   connection.on('message', function(message) { 
	
      var data; 
      //只接收JSON 
      try {
         data = JSON.parse(message); //切分JSON存入data
      } catch (e) { 
         console.log("Invalid JSON"); 
         data = {}; 
      } 
		
      //用户消息的type 
      switch (data.type) { 
         //尝试登录
			
         case "login": 
            console.log("User logged", data.name); 
				
            //重名了 
            if(users[data.name]) { 
               sendTo(connection, { 
                  type: "login", 
                  success: false 
               }); 
            } else { 
               //可以登则存入数组 
               users[data.name] = connection; 
               connection.name = data.name; 
					
               sendTo(connection, { 
                  type: "login", 
                  success: true 
               }); 
            } 
				
            break; 
				
         case "offer": 
            //for ex. A想打给B 
            console.log("Sending offer to: ", data.name); 
				
            //B存在则发给B offer 
            var conn = users[data.name];
				
            if(conn != null) { 
               /A 的连接对象设为 B
               connection.otherName = data.name; 
					
               sendTo(conn, { 
                  type: "offer", 
                  offer: data.offer, 
                  name: connection.name 
               }); 
            } 
				
            break;  
				
         case "answer": 
            console.log("Sending answer to: ", data.name); 
            //for ex. B要接听A
            var conn = users[data.name]; 
				
            if(conn != null) { 
               connection.otherName = data.name; 
               sendTo(conn, { 
                  type: "answer", 
                  answer: data.answer 
               }); 
            } 
				
            break;  
				
         case "candidate": 
            console.log("Sending candidate to:",data.name); 
            var conn = users[data.name];  
				
            if(conn != null) { 
               sendTo(conn, { 
                  type: "candidate", 
                  candidate: data.candidate 
               });
            } 
				
            break;  
				
         case "leave": 
            console.log("Disconnecting from", data.name); 
            var conn = users[data.name]; 
            conn.otherName = null; 
				
            //notify the other user so he can disconnect his peer connection 
            if(conn != null) { 
               sendTo(conn, { 
                  type: "leave" 
               }); 
            }  
				
            break;  
				
         default: 
            sendTo(connection, { 
               type: "error", 
               message: "Command not found: " + data.type 
            }); 
				
            break; 
      }  
   });  
	
   //用户退出，比如关闭了浏览器窗口 
   //如果我们仍在offer\answer\candidate状态。则起作用。 
   connection.on("close", function() { 
	
      if(connection.name) { 
      delete users[connection.name]; 
		
         if(connection.otherName) { 
            console.log("Disconnecting from ", connection.otherName);
            //A的连接对B象存到Conn
            var conn = users[connection.otherName]; 
            //设置A为无连接状态
            conn.otherName = null;  
				//让B也leave会话
            if(conn != null) { 
               sendTo(conn, { 
                  type: "leave" 
               });
            }  
         } 
      } 
   });  
	
   connection.send("Hello world"); 
	
});  

function sendTo(connection, message) { 
   connection.send(JSON.stringify(message)); 
}
```

这篇文章一定要和入门教程02一起看~

