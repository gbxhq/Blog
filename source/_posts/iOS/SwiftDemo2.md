---
title: Swift Demo2 查天气
date: 2018-04-02 14:02:52
categories:
tags:
---

通过API查天气。

<!---more--->

# 载入
界面简单，
三个Label（地址、温度、描述）
一个Btn。

先把Btn写出来。
弹出Alert，附带一个文本输入框，把输入框的值传给通过Api获取天气数据的函数。代码如下：

```swift
@IBAction func setCityBtn() {
//先来个alert
        let alert = UIAlertController(title: "Set City", message: nil, preferredStyle: .alert)
        //加Cancel按钮   
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
        //加OK按钮，如果文本不为空则传给tf(TextField)，再用tf传给cityName，再用city传给getWeatherData函数
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action) in
            if let tf = alert.textFields?.first{
                if let cityName = tf.text{
                    self.getWeatherData(cityName: cityName)
                }
            }
        }))
        //加个文本框
        alert.addTextField(configurationHandler: { (tf) in
            tf.placeholder="Please input city"
        })
        //显示Alert
        self.present(alert,animated:true,completion: nil)
    }
```
# 天气Api

用了知心天气的API。https://api.seniverse.com/v3/weather/now.json?key=123456&location=jinan&language=zh-Hans&unit=c

其中如果要处理非HTTPS的网址，会报错。需要在info.plist文件中添加下面的选项：
![](http://p66eruxmw.bkt.clouddn.com/15226535153796.jpg)

## SwiftyJSON

~~说实话我遇到问题了。等我读了SwfityJSON的文档回来研究明白再说吧。有点尬了。撤了撤了。~~

根据我滴最新查询，使用Swift 4.0的Codable暂时可以舍弃SwiftyJSON。
我们走起。

先解决怎么读Url的内容问题：

## 读url


