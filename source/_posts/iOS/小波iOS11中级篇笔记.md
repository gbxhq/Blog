---
title: 小波iOS11中级篇笔记
date: 2018-04-07 12:53:54
categories: iOS
tags: [Note,Swfit]
---

中级篇啦🤣开心点咯。虽然最近有点低落，就当发泄了。

<!---more--->
# 小知识点

- `"""`三引号对`"""`可以保留复制来的文本换行
- 图片显示方式：
    - Scale to fill 拉伸 即拉到和框框一样的比例/大小
    - Aspect fit 居中 原图比例不变，但会有白边
    - Aspect fill 平铺 ，通常配合下面的裁边Clip to bounds使用
- 属性line设为0. 即自动控制行数
- 内容扩展优先级 Content Hugging Priority 大了就低
- Class 中的属性必须有值。如果你不想给值，可以加个 ！ 就是说它一定有值。
-  Btn.setTitle("改标题")
-  拖新文件到工程里记得选上`Copy item if needed`，不然只拖了个快捷方式
-  Didload只会执行一次
-  在整个Controller的属性中，选高度--》Freedom--》可以随意设置。方便查看。
-  转String可以不用`String(a)`用`a.description`

# 自定义导航条

## 颜色（直接改回报错，是Xcode的Bug。只好用代码。）：
 
```swift
navigationController?.navigationBar.largeTitleTextAttributes = [
                NSAttributedStringKey.foregroundColor : UIColor(named: "Theme123")
            ]
            //Theme123是自定义的Color Set名
```
## 背景透明（用一个空图片）

```swift
navigationController?.navigationBar.setBackgroundImage(UIImage(), for: .default)
navigationController?.navigationBar.shadowImage = UIImage()
```

## 隐藏返回标题
![](http://p66eruxmw.bkt.clouddn.com/15231886419894.jpg)
点标题。把Back button改成空格就好啦。

## 自定义状态栏字体颜色

```swift
    override var preferredStatusBarStyle: UIStatusBarStyle{
        return .lightContent
    }
//写了上面的发现还不行。因为有全局导航条样式

//新建一个swift文件： naviExt.swfit 写入以下内容
import UIKit
//扩展导航条
extension UINavigationController{
    open override var childViewControllerForStatusBarStyle: UIViewController?{
        return topViewController
    }
}
```

没有导航条怎么改状态栏颜色：
在AppDelegate.swift文件中，插入到application函数一行：
`UIApplication.shared.statusBarStyle = .lightContent`

# 动画
## 视差

新建一个UIView变量`var headerView : UIView!`来替换原生的`tableView.tableHeaderView`
代码如下

```swift
        headerView = tableView.tableHeaderView//取出HeaderView
        tableView.tableHeaderView = nil 
        tableView.addSubview(headerView)
        
        tableView.contentInset = UIEdgeInsets(top: 300, left: 0, bottom: 0, right: 0)
```

这时候整个Cell会下移300像素（可以通过输出`scrollView.contentOffset.y`的值看到是 -300），需要把headerView的位置上移300个像素。
代码如下

```swift
override func scrollViewDidScroll(_ scrollView: UIScrollView) {
        let offsetY = scrollView.contentOffset.y
        headerView.frame = CGRect(x: 0, y: offsetY, width: scrollView.bounds.width, height: -offsetY)
    }
```

## 模糊层

1. 新建模糊层的 ViewController 。背景选成透明（Clear Color）
2. 右键拖到新的 View Controller，选 Present Modally
3. 转场效果中选 Over Current Context


点击退场

拖一个手势到 **View层** 注意拖得不合适可能点击没效果。可以调试下。

然后拖着手势建一个IBAction：

```swift 
@IBAction func tapBackground(_ sender: Any) {
        self.dismiss(animated: true)
    }
```

## 入场动画

先在 didLoaded 时把它放到800里之外
`stackView.transform = .init(translationX: 800, y: 0)`

再在 didApeal时 让它飞进来

```swift
override func viewDidAppear(_ animated: Bool) {
        let  animator = UIViewPropertyAnimator(duration: 3, curve: .easeIn){
            self.stackView.transform = .identity
        }
        animator.startAnimation()
    }
```
进阶版
按钮组在这里拖按钮。
![按钮组](http://p66eruxmw.bkt.clouddn.com/15233413710890.jpg)

然后把变量分别拖到各个按钮上，这些按钮就是一组的了。

```swift
override func viewDidLoad() {
        super.viewDidLoad()
        
        let startPostion = CGAffineTransform(translationX: 500, y: 0)
        
        for button in rateItemBtn{
            button.transform = startPostion
            button.alpha = 0 //把他们都设透明
        } 
    }

    override func viewDidAppear(_ animated: Bool) {
UIViewPropertyAnimator(duration: 0.4, dampingRatio: 0.5) {
            self.rateItemBtn[0].transform = .identity
            self.rateItemBtn[0].alpha = 1
            }.startAnimation(afterDelay: 0.1)//第一个按钮0.1秒后出现
    }
```

## 拖拽手势

```swift
    @IBAction func dragStackView(_ sender: UIPanGestureRecognizer) {
        switch sender.state {
        case .changed:
            let translate = sender.translation(in: view)
            let position = CGAffineTransform(translationX: translate.x, y: translate.y)
            let angle = sin(translate.x / stackView.frame.width)
            stackView.transform = position.rotated(by: angle)
        case .ended:
            UIViewPropertyAnimator(duration: 0.4, dampingRatio: 0.5) {
                self.stackView.transform = .identity
            }.startAnimation()
        default:
            break
        }   
    }   
```

##  反向转场
先写一个转场函数：

```
@IBAction func backToDetail(segue: UIStoryboardSegue){}
```
![](http://p66eruxmw.bkt.clouddn.com/15233456161140.jpg)
把按钮拖到这个Exit上。选择上面的函数就好啦。


# JSON
## Encode JSON

```swift
 func saveToJson() {
        let coder = JSONEncoder()
        
        do {
            let data = try coder.encode(weapons)
            let saveUrl = URL(fileURLWithPath: NSHomeDirectory()).appendingPathComponent("weapons.json")
        
            try data.write(to: saveUrl)
            print("保存成功！路径：",saveUrl)
        } catch {
            print("编码错误: ",error)
        }
    }  
```
## Decode JSON

    func loadJson()  {
        let coder = JSONDecoder()
        
        do {
            let url = Bundle.main.url(forResource: "weapons", withExtension: "json")!
            let data = try Data(contentsOf: url)
            weapons = try coder.decode([Weapon].self, from: data)
        } catch  {
            print(error)
        }
    }

# 数据录入
## Picker View

1. 每个Picker加一个tag用来标识
2. ctrl拖到Controller上选上Delegate和DataSource
3. 新建一个PickerViewFill.swift写入以下内容：

```swift
import UIKit

extension 你要扩展的面controller:UIPickerViewDelegate,UIPickerViewDataSource{
}
```
会自动填充出两个函数。
一个控制行，一个控制列。

如何区分不同的列呢。
`component`就是列数 （从0开始）

联动：打didselect联想出这个函数：

```swift
func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if pickerView.tag == 12 {
            if component == 0 {
                pickerView.reloadComponent(1)
            }
        }
    }
```

## Stepper

```swift
@IBAction func mvStepper(_ sender: UIStepper) {
        textFieldMv.text = Int(exactly: sender.value)!.description
    }
```

# 点击单元格
**didSelect**

```swift
override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
// indexPath就是坐标 [0,0] 第一个是session号，第二个是行
}
```


## Alert

### Alertsheet
  
```swift
 let actionSheet = UIAlertController(title: "总标题", message: nil, preferredStyle: .actionSheet)
            
            let action1 = UIAlertAction(title: "111", style: .default ) { (_) in
            }
            let action2 = UIAlertAction(title: "222", style: .default) { (_) in

            let cancel = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
            
            actionSheet.addAction(action1)
            actionSheet.addAction(action2)
    
            present(actionSheet,animated: true)
```

