---
title: vue组件传值
date: 2020-03-08 21:32:39
categories: [WebSite]
tags: [FE,Vue]
---

<!---more--->

# [vue 组件传值](https://www.cnblogs.com/sunshine-wy/p/10819652.html)

　　我们的场景是在父组件点击按钮弹出子组件，子组件里对数据进行编辑操作以后通知父组件操作完成。弹窗效果是框架自带的，这里只说一下组件之间如何传值。

　　子组件: dtls.vue

　　父组件: Service.vue

------

　　首先父组件要调用子组件：import dtls from './dtls.vue' （注意，两个vue文件在同一个文件夹下则前面路径给 ./ 即可，不在一个文件夹下的自行科普路径问题）

　　导入以后添加到当前vue的实例里，如图：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506143159736-1337913029.png)

　  父页面调用的时候直接使用名称做的标签即可：<dtls></dtls>

　  到此可以访问到子组件的html了，但是我需要把父组件的数据给子组件，是个对象：

　　首先我在父组件里的子组件标签上定义并赋值一个变量：<dtls :editObject=editObject ></dtls>

　　注意，:editObject是我定义的名称（用于子组件的取值，你可以理解为形参），等号右边的editObject是我父组件里的一个对象，可以理解为实参，就是实际的值，要传递给子组件的值，名称可以不一样。

　　到这一步父组件的事就完成了，该子组件接收值了：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506143956370-1656976391.png)

　　在子组件的实例里通过props来获取我在父组件传递的editObject对象，这个时候，子组件已经取得了editObject的值。注意，此时不必再在子组件里定义一个editObject对象，传递过来的参数editObject已经是当前子组件的一个对象了，按正常使用即可，比如我要在子组件的页面上显示具体的值：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506144251988-480523364-20220524195401570.png)

　　通过:model就能绑定值，下面访问的时候，v-model即可：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506144346628-1225045443.png)

　　由于label标签无法 v-model赋值，所以通过{{对象.属性}}即可显示具体字段值。

　　现在父组件调子组件完成传值了，轮到子组件完成某个操作反馈信息给父组件了：

　　首先我们在子组件的某个操作完成事件里（比如保存方法的最后一行）定义一个函数并携带上一个对象作为参数：this.$emit('Success', "OK")，图示：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506144754329-1329003539.png)

　　Success你可以理解为回调函数名，这个是子组件自定义的一个名称，$emit方法可以理解为定义一个回调函数名称，并传递一个实参，可以是任何字符串、数组、或者对象。我这里只需传个OK字符串。

　　好了，子组件的事情完成了，剩下的就是父组件对子组件定义的回调函数进行监听。

　　现在我们回到父组件的页面上，在dtls标签上加上事件绑定：v-on:Success="Success"，完整的dtls标签如下：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506145317096-158364349.png)

　　最后一步，在父组件里定义一个函数，名为Success：

　　![img](https://cdn.jsdelivr.net/gh/gbxhq/Pic/784108-20190506145406910-583735274.png)

　　同理，父组件里的函数名可以和子组件不同，等号左边和右边应该是分别对应一个，我这里没必要写成不一样的，就没去尝试了，大家有自己需求的可以试试。

　　到此整个组件传值就完成了，从父组件调用子组件并传递对象，到子组件完成操作以后定义事件，最后父组件对子组件的事件进行监听。

作者：[ 默卿](https://www.cnblogs.com/sunshine-wy/)

出处：https://www.cnblogs.com/sunshine-wy/p/10819652.html

# 子组件调用父组件的方法：

```js
onChangeNav(){
    this.$parent.switchNav()
},
```
