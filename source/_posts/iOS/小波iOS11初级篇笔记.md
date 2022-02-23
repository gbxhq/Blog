---
title: 小波iOS11初级篇笔记
date: 2018-01-08
categories: iOS
tags: [Note,Swift]
---

这份Swift4.0的教程来自[小波说雨燕](http://xiaoboswift.com/my/course/90) 是能搜到的第一份Swift 4.0开发**中文教程** 
我要是英语好早去听YouTube了

<!---more--->

# 小知识点

- IB : Interface Builder 界面构建器

- 这种写法来防止id出错

```swift
  let id = String(describing: CardCell.self)
  withIdentifier: "id"	
```

- ctrl + B 光标左移 
- 点行号前面是加断点。去断点把它拖到外面就好了。
- 加 ！是强制


# 导航和转场
## 新场景

1. 拖一个新的UITableViewController，就要新建对应的场景控制器。
2. New File --> Cocoa Class --> 起个名,父类选择UITableViewController
3. 在StoryBoard中，identity栏讲场景与类绑定

## 添加导航：
菜单栏-Editor-->Embed in-->Nav~

- 怎么转到新场景：
控件上ctrl拖到新场景 选择 Show (Present是模态展示，没有层级关系)

## 转场
自动生成的代码中找到// MARK: - Navigation 解除注释
# Table View[代理模式]
在ViewControler场景后加上`UITableViewDataSource`就支持了TableView的数据源协议。
加上后会报一个当前不支持的错，点Fix自动填写两个方法。
第一个是说Table中有多少行。Ex:`return 10`
第二个方法设置每个单元格的模板。Ex:

```swift
func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "WeaponCell", for: indexPath)
        cell.textLabel?.text = weapons[indexPath.row]
        return cell
    }
```
为什么要重复使用模板呢？
> 答：这样可以在滑动的时候，把消失的单元格从内存回收

协议连接：在TableView上ctrl拖到ViewControler上，选DataSource：
![](http://p66eruxmw.bkt.clouddn.com/15230037794942.jpg)


## 识别单元格
点击的是第几个单元格呢？

```
@IBAction func favBtnTap(_ sender: UIButton) {
//点击的坐标（相对于TableView）
        let btnPos = sender.convert(CGPoint.zero, to: self.tableView)
//所在的行
        let indexPath = tableView.indexPathForRow(at:btnPos)!
}
```

- indexPath有两个属性[session,row] 
就是第几列第几行 [横坐标,纵坐标]

## 左/右滑动

```swift
//←  左滑 输入leading就能联想出
override func tableView(_ tableView: UITableView, leadingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
    let aaa = UIContextualAction(){
    ...//操作内容
    completion(true)//点完收起来
    }
   //分享按钮
    let shareAction = UIContextualAction(style: .normal, title: "Share") { (_, _, completion) in
            let text = "这是一把\(self.weapons[indexPath.row])xue"
            let image = UIImage(named: self.weaponImages[indexPath.row])!
            
            let ac = UIActivityViewController(activityItems: [text,image], applicationActivities: nil)
            
        //解决iPad用模态框不好看的问题
            if let pc = ac.popoverPresentationController{
                if let cell = tableView.cellForRow(at: indexPath){
                    pc.sourceView = cell
                    pc.sourceRect = cell.bounds
                }
            }
            self.present(ac, animated: true)
            
            completion(true)//点完收起来
    }
        
        shareAction.backgroundColor = UIColor.orange
        
        let config = UISwipeActionsConfiguration(actions: [aaa,shareAction])//告诉系统有几个按钮
        return config
}
//→ 右滑改成 trailingSwipe
```


# 属性监视器[观察者模式]
变量后加大括号就是属性监视器 。

```swift
var favorite = false {
//属性变化之前
        willSet {
            if newValue{ //即 if newValue == True
                favBtn.setImage(#imageLiteral(resourceName: "fav"), for: .normal)
            }else{
                favBtn.setImage(#imageLiteral(resourceName: "unfav"), for: .normal)
            }
        }
    }
```

