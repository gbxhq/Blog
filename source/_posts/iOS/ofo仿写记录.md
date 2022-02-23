---
title: ofo仿写记录
date: 2018-05-16 19:34:53
categories: iOS
tags: Swift
---

ofo不解释，教程同样来自小波。

<!---more--->

# 小知识点

- 解包 .car 文件：
https://github.com/insidegui/AssetCatalogTinkerer
仿写必备咯
- 很多时候Constrain不好加，可以先拖到合适的地方。比如拖得贴近边框
- ImageView没法调宽度（Table Session里）可以先放一个Container View
- 按比例添加Constarin：在控件总览栏右键从一个容器拖到上一层容器上，选的等宽，右侧属性改为0.25. 就是占上一层容器的1/4
- 把一个view放到顶层：`view.bringSubview(toFront: ___)`
- 在模拟器按住option可以双指
- dump()有点像print但是可以输出属性
- 加注释技巧:`// MARK: -这样可以在查看函数时快速定位`



# 加载网页
## WebView

网页自适应选项在这：
![](http://p66eruxmw.bkt.clouddn.com/15264706713494.jpg)

写法：

```Swift
let url = URL(string: "http://m.ofo.so/active.html")!
        
let requset = URLRequest(url: url)
        
webView.loadRequest(requset)
```
## WebKit


```Swift
import WebKit

var webView: WKWebView!
webView = WKWebView(frame: self.view.frame) //调大小
view.addSubview(webView) //加到视图里
    
let url = URL(string: "http://m.ofo.so/active.html")!
let requset = URLRequest(url: url)
    
webView.load(requset)
```

# 侧边栏
## 第三方库 初探
https://cocoapods.org

装 cocoapods:

```bash
sudo gem install cocoapods
```

## 安装SWRevealViewController

在podfile加入
`pod 'SWRevealViewController',2.3`
Terminal运行：
`pod install`

- 由于SWRevealViewController是OC写的，要做一个桥接：
新建一个OC文件，自动生成一个桥接.h文件。删除OC文件即可。

在桥接.h文件里加入
`# import "路径/SWRevealViewController.h"`
在要使用的场景里加入
`import SWRevealViewController`

## 使用 SWRevealViewController

1. 拖一个ViewController，类选择SWRevealViewController
2. 程序入口改成这个VC
2. 从这个ViewController右键拖到1场景和2场景，都选择SW-Set
3. 两个场景的路径设置Segue的id，前面的叫sw_front，后面（划出来）的叫sw_rear
4. 写代码

```swift
if let revealVC = revealViewController() {
    
    revealVC.rearViewRevealWidth = 300 //设宽度
    
    navigationItem.leftBarButtonItem?.target = revealVC
    navigationItem.leftBarButtonItem?.action = #selector(SWRevealViewController.revealToggle(_:))//这句是OC语法   `#selecot`是OC的一个方法
    view.addGestureRecognizer(revealVC.panGestureRecognizer())
}
```
在滑动菜单里点击按钮转场：
右键拖到场景里，选 r-v-c push 即可
再放上刚刚的代码（记得在场景里Embed in个导航）

```swift
if let revealVC = revealViewController() {
    
    revealVC.rearViewRevealWidth = 300 //设宽度
    
    navigationItem.leftBarButtonItem?.target = revealVC
    navigationItem.leftBarButtonItem?.action = #selector(SWRevealViewController.revealToggle(_:))//这句是OC语法   `#selecot`是OC的一个方法
    view.addGestureRecognizer(revealVC.panGestureRecognizer())
}
```

# 地图定位

安装包和引用头文件都在文档里。

引入mapView，先声明一个mapView变量：`var mapView: MAMapView!`
然后再viewDidload()里添加View：

```swift 
mapView = MAMapView(frame: view.bounds)//占满全屏
mapView.delegate = self //地图代理，以方便重写方法.     
view.addSubview(mapView)
view.bringSubview(toFront: panelView)
```
加了代理要改这里：
`class ViewController: UIViewController,MAMapViewDelegate{}`加一个继承

加Key加HTTPs啥的都在文档里了。比如这些放在`AppDelegate.swift`的`didFininshedLaunching()`中：

```swift
AMapServices.shared().enableHTTPS = true
AMapServices.shared().apiKey = "YOUR KEY"
```
        

## GPX文件制作

http://mygeoposition.com

Note：调用Google地图，需富强上网。

PS：经纬度数据可能不准确。在http://mygeoposition.com获取了GPX文件后可以再到http://lbs.amap.com/console/show/picker 查到对应的经纬度修改下。

## POI




