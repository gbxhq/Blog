---
title: iOS 圆角、阴影通用配置
date: 2018-02-09
categories: iOS
tags: [Note,Swift]
---
这是在小波老师的课上学到的一劳永逸地给控件添加圆角、阴影效果的代码。保存备用。
<!---more--->

```swift
import UIKit
//圆角
extension UIView {

  @IBInspectable //让它可见
  var cornerReadius: CGFloat { //打var选get-set模板 //图形相关属性CG开头
      get {
          return layer.cornerRadius
      }
      set {
          layer.cornerRadius = newValue
      }
  }
//阴影圆角
  @IBInspectable
  var shadowRadius: CGFloat {
      get {
          return layer.shadowRadius
      }
      set {
          layer.shadowRadius = newValue
      }
  }
//阴影透明度
  @IBInspectable
  var shawodOpacity: Float {
      get {
          return layer.shadowOpacity
      }
      set {
          layer.shadowOpacity = newValue
      }
  }
//阴影颜色
  @IBInspectable
  var shadowColor: UIColor? {
      get {
          return layer.shadowColor != nil ? UIColor(cgColor: layer.shadowColor!) : nil
      }
      set {
          layer.shadowColor = newValue?.cgColor
      }
  }
//阴影大小
  @IBInspectable
  var shadowOffset: CGSize {
      get {
          return layer.shadowOffset
      }
      set {
          layer.shadowOffset = newValue
      }
  }

}
```


