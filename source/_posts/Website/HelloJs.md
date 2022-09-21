---
title: HelloJs
date: 2018-08-14 16:13:20
categories: [Website]
tags: [js,Note]
---

高铁上没事干，入门一波Js。

<!---more--->

# Tips

- 分号`；`可选
- 标识符以字母、下划线和美元符号开始
- 大小写敏感

# Grammar

## Var

`var a = 10` 声明变量

`docunment.write(a)` 输出

赋值为null可清除变量

- 点击运算

```html
<p id = "sumid"></p>
<button onclick="mysum()">结果</button>
<script>
function mysum(){
    var i = 10;
    var j = 10;
    var m = i + j;
    document.getElementById("sumid").innerHTML = m;
}
</script>
```
## Operator

`+ - x / % ++ --`

`= += -= *= /= %=`

`== === != < > <= >=`

`&& || ! `

`?:`三目

- 任何类型和字符串运算都会被转成字符串类型


这就是`==`和`===`的区别：

```
"5"==5?
true
"5"===5?
false
```

## Condition

`if else`

```
switch(i){
case 1: break;
case 2: break;
default: break;
}
```

## Loop

`for(;;){}`和C中一样

`for (j in i)`

`while` `do while`

# Function

## 调用

- 在`<script>`中
- 在Html中

# 异常捕获

```
try{
    //此处插入测试代码块
}catch(err){
    //发生错误会触发下面的代码
    alert(err);
}
```
# 事件

## 常用

| 事件 | 描述 |
| :-- | :-- |
| onClick | 单击 |
| onMouseOver | 鼠标经过 |
| onMouseOut | 鼠标移出 |
| onChange | 文本内容改变 |
| onSelect | 文本框选中 |
| onFocus | 光标聚集 |
| onBlur | 移开光标 |
| onLoad | 网页加载 |
| onUnload | 网页关闭  |

## 例子

```javascript
<html>
<head>
	<title>事件</title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
//注意传递的 this
	<div class="div" onmouseout="onOut(this)" onmouseover="onOver(this)">	
	</div>

	<script type="text/javascript">
		function onOver(ooj){
			ooj.innerHTML = "Hello";
		}
		function onOut(ooj){
			ooj.innerHTML = "World";
		}
	</script>
</html>
```

# DOM

网页被加载时，浏览器会创建页面的文档对象模型(Docunment Object Model)

## DOM操作HTML

- 改变HTML输出流
    `document.write()`
    
    > 注意不要在文档加载完成之后使用，会覆盖文档。
- 寻找元素
    - 通过id

```javascript
<script>
    function demo(){
        var a = document.getElementById("pid");
    }
</script>
```

- 通过标签名ByTagName···

    返回的是一个数组
    
- 改变内容

```javascript
<script>
    function demo(){
        var a = document.getElementById("pid").innerHTML="Changed";
    }
</script>
```

- 改变属性

```javascript
<script>
function demo(){
var a = document.getElementById("aid").href="http://oo1.win";
}
</script>   
```

- `removeChild() insertBefore()`添加删除子节点

## DOM操作CSS

```javascript
<button onclick="demo()">按钮</button>
<script>
    function demo(){
document.getElementById("pid").style.background="blue";}
</script>
```

## DOM EventListerner
事件句柄

- 方法：
- - `addEventListener()`

    向指定元素添加事件句柄
```javascript
<script>
    document.getElementById("btn").addEventListener("click",function(){
        alert("hello")
    })
</script>
```
这样就不需要写一个函数，再从button的属性中更改`onclick="xxx()"`
    
> 添加多个句柄**不会覆盖**

```javascript
<script>
    x = document.getElementById("btn");
    x.addEventListener("click",func1);
    x.addEventListener("click",func2);
    func1(){alert("hello");}
    func2(){alert("world");}
</script>
```

- 
    - `removeEventListener()`

移除方法添加的事件句柄

`x.removeEventListener("click",func2);`

# 事件详解

## 事件流

- 事件冒泡

    由最具体的元素接收，然后逐级冒泡至最不具体的元素的节点。
- 事件捕获

    由最不具体的.
    
## 事件处理

- HTML事件处理
  
    直接添加到HTML结构中
- DOM 0级事件处理
  
    ```javascript
    var x = document.getElementById("btn1");
    btn1.onclick = function(){xxx;}
    ```
    > 这种事件处理**会被覆盖**
    
- DOM 2级事件处理
    - 即`addEventListener("事件名”,“事件处理函数”,“布尔值");`
    true: 事件捕获、
    false: 事件冒泡
    
    ？？？：缺省值是true还是false？
    
- IE 事件处理程序

## 事件对象

1. 事件对象
  
    在触发DOM事件的时候都会产生一个对象 
2. 事件对象event
    1. type: 获取事件类型
    2. target: 获取事件目标
    3. stopPropagation(): 阻止事件冒泡
    4. preventDefault(): 阻止事件默认行为
    
    - 例子
    
```javascript
<script>
document.getElementById("btn1").addEventListener("click",showType);
function showtype(event){
    alert(event.type);
    event.stopPropagation();//阻止事件冒泡 就是上一级不再响应了。比如在button上一级的div中也有一个click点击事件。不阻止就也会执行。
    //阻止事件行为就是啥也不干了。比如a标签不跳转了。
}
</script>
```

# 内置对象

1. 什么是对象：字符串、数组、数值、函数.所有事物都是对象。每个对象都有属性和方法。
2. 自定义对象

- 定义并创建对象实例例子

```javascript
<script>
    people = new Object();
    people.name = "xy";
    people.age = 30;
    //或
    //people = {name:"xy",age:"30"};
    
document.write("name:"+people.name+",age:"+people.age);
</script>
```
- 使用函数定义对象，然后创建对象实例

例子

```javascript
<script>
    function people(name,age){
    this.name = name;
    this.age = age;
    }
    
document.write("name:"+people.name+",age:"+people.age);
</script>
```

## String字符串对象

方法：

- 字符串中查找字符串 `indexOf()`
有则返回位置。无则返回-1
- 匹配内容 `match()`
- 替换内容 `replace()`
- 字符串大小写转换 `toUpperCase()``toLowerCase()`
- 字符串转为数组 `strong>split()`

剩下的查文档吧。

## Date日期对象

- 获取当前Date

```javascript
<script>
    var date = new date();
    document.write(date);
</script>
```


- 常用方法
    - `getFullyear()` 获取年份
    - `gettime()` 获取毫秒
    - `setFullyear()` 设置具体的日期变量赋值
    - `getDay` 获取星期

例子

```javascript
<script>
starttime();
function starttime(){
    var today = new Date();
    var h = today.getHours();
    var m = today.getMinutes();
    var s = today.getSeconds();
    
    m = checktime(m);
    s = checktime(s);
    document.getElementById("timetxt").innerHTML = h+"-"+m+"-"+s;
    t = settimeout(func,1000);
}
function checktime(i){
    if(i<10){i = "0"+i;}
    return i;
}
function func(){
    starttime()
}
</script>
<div id = "timetxt">
<script>starttime()</script>
</div>
```



## 数组

常用方法

- `a.concat(b)` 合并数组a+b
- `sort()` 排序
- `push()` 末尾加元素
- `reverse()` 翻转
.
降序排列：

```javascript
<script>
var a = [5,2,4,1,3];
document.write(a.sort(function(a,b){
    return b-a;}));
</script>
```

**???**这里不太懂为啥sort里传了个函数。
> 搜到了解答：
> `arrayObject.sort(sortby`)如果不传参数而默认按Ascii编码字母序排序。否则传入的就是**比较函数**。
> 比较函数应该具有两个参数 a 和 b，其返回值如下：

> 若 a 小于 b，在排序后的数组中 a 应该出现在 b 之前，则返回一个小于 0 的值。
> 若 a 等于 b，则返回 0。
> 若 a 大于 b，则返回一个大于 0 的值。
> 通过调试发现默认情况下，随机参数a b的值总是a比b小。所以a-b是升序。 b-a是降序。


## Math对象

不多解释了`Math.round(四舍五入) Math.random(0-1随机数).max().min().abs()`

# Js浏览器对象

## window对象

`window.open(,,)`
可以设置打开的对象，窗口名，大小+位置
`window.close()`关闭

docunment\DOM啥的都是window的对象。可缺省。

## 计时器

- `setInterval()` 间隔一定毫秒 不停地执行 指定代码
  `clearInterval()` 终止
- `settimeout()` 暂定一定毫秒后执行指定的代码 (就是延时执行，如果想不停执行还要递归调用。)
  `cleantimeout()`
  
  例子
  
```javascript
<button id="btn" onclick="stopTimer()">停止时间</button>
<p id="ptime"></p>
<script>
var mytime = setInterval(func(){
    getTime();
},1000);
function getTime(){
    var d = new Date();
    var t = d.toLocaleTimeString();
    document.getElementById("ptime").innerHTML = t;
}
function stopTimer(){
    clearInterval(mytime);
}
</script>
```

## History对象、Location对象、Screen对象



