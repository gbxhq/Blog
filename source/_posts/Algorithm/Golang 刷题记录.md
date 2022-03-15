---
title: Go 刷题记录
date: 2020-03-08 21:32:39
categories: [Algorithm]
tags: [Go,Algorithm]
---

> 再刷洛谷试炼场，发现试炼场已经无了。开始以为找不到了，知乎上看到站长的回复才知道真的无了。我是从这个人整理的版本里刷的：
>
> https://www.luogu.com.cn/paste/66uuuvdr

大概刷了 10 道题之后，放弃洛谷。

原因是里面几乎都是 C++选手，遇到一些解不了的case实在不知道 Go 是哪里 A 不过的。


# 输入输出

> 才发现用 go 刷题连输入输出都不会

- `print` 在golang中 是属于输出到标准错误流中并打印,官方不建议写程序时候用它。可以debug时候用

- `fmt.print` 在golang中 是属于标准输出流,一般使用它来进行屏幕输出.

# 处理字符串

```go
func replaceSpace(s string) string {
	var res strings.Builder
    for i:=range s{
    	if s[i]==' '{
			res.WriteString("%20")
		}else {
			res.WriteByte(s[i])
		}
	}
	return res.String()
}
```
- [03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

交换法

# 快慢指针

快指针在前面探路，慢指针满足条件再走。

eg. 删除数组、链表中的重复元素

283 删除0

我的方法：遇到 非0 就填充，最后把没填充的再填充 0；

更优：遇到非 0，就交换。这样 0 会被不停地往后换。

# 前缀和

快速算区间和

![img](https://raw.githubusercontent.com/gbxhq/Pic/main/qianzhuihe.jpeg)

Sum(nums[i]--nums[j]) =  preSum[j+1]-preSum[i]

- 二维数组前缀和 https://leetcode-cn.com/problems/range-sum-query-2d-immutable/submissions/

  ```go
  func Constructor(matrix [][]int) NumMatrix {
  	l := len(matrix)+1
  	preSum := make([][]int, l)
  	for i:=0;i<len(preSum);i++{
  		preSum[i] = make([]int, l)
  		for j:=0;j<len(preSum[i]);j++ {
  			if i == 0 || j == 0{
  				preSum[i][j] = 0
  				continue
  			}
        //注意最后这个 - 
  			preSum[i][j] = preSum[i-1][j] + preSum[i][j-1]+ matrix[i-1][j-1] - preSum[i-1][j-1]
  			//println(i,j,":",preSum[i-1][j],preSum[i][j-1],matrix[i-1][j-1],"-",preSum[i-1][j-1],"=",preSum[i][j])
  		}
  	}
  	return NumMatrix{
  		Matrix: matrix,
  		PreSum: preSum,
  	}
  }
  
  
  func (this *NumMatrix) SumRegion(row1 int, col1 int, row2 int, col2 int) int {
  	//println(this.PreSum[row2+1][col2+1] , this.PreSum[row1][col2+1] , this.PreSum[row2][col1] , this.PreSum[row1][col1])
    // row1和 col1 都是不+1，row2 和 col2 都+1
  	return this.PreSum[row2+1][col2+1] - this.PreSum[row1][col2+1] -
  		this.PreSum[row2+1][col1] + this.PreSum[row1][col1]
  }
  
  ```



# 查分数组

频繁对区间进行删减的情况

![img](https://raw.githubusercontent.com/gbxhq/Pic/main/chafenshuzu.jpeg)

- `nums[i] = diff[i] + nums[i-1]`

- `nums[i..j]` 都 +3 等于 `diff[i]+=3 , diff[j+1]-=3`

  但是注意， nums 更新最后一个数字时，diff[j+1]会越界，所以不用再更新

- 遍历 diff 数组即可还原 nums 数组。

[1094. 拼车](https://leetcode-cn.com/problems/car-pooling/)

[1109.航班预订统计](https://leetcode-cn.com/problems/corporate-flight-bookings)

# 回文

# 二分

直接二分搜索

```go
// 关键两点
for i<=j { //1. <=
  m = i+1  //2, 边界 +1 / -1
  m = j-1
}
```



[34.在排序数组中查找元素的第一个和最后一个位置（中等）](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

## 二分变形

通过二分查找试出最佳值

- 取整技巧：` (x + n -1)/n == int(ceil(x/n))`

# 滑动窗口

我写的滑动窗口有思想问题

比如找无重复的最长子串，滑动[i..j]，我是 外循环 j++，j 不停地往后，发现重复则把 i 更新到出现过的位置。清空 map 重新记录一次。

标准的思想：[i..j]，外循环是 i ++， 每次以 i 为开头，内循环 j ++ 尝试找出 以 i 开头最长的。

每次外循环 i++时 删除 map 里的前一个元素 `delete(m, s[i-1])`

# container

go 里没有栈。但container 包里的 list、heap和 ring 也勉强够用。

只是用起来稍微有点绕（特别是不能定义容器的元素类型，遇到返回 Value 的题还要断言一下）

下面遇到某个 container 就整理一下

## list

链表就是一个有 prev 和 next 指针的数组了。它维护两个 type，( 注意，这里不是 interface)

```golang
type Element struct {
    next, prev *Element  // 上一个元素和下一个元素
    list *List  // 元素所在链表
    Value interface{}  // 元素
}

type List struct {
    root Element  // 链表的根元素
    len  int      // 链表的长度
}
```

基本使用是先创建 list，然后往 list 中插入值，list 就内部创建一个 Element，并内部设置好 Element 的 next,prev 等。具体可以看下例子：

```golang
// This example demonstrates an integer heap built using the heap interface.
package main

import (
    "container/list"
    "fmt"
)

func main() {
    list := list.New()
    list.PushBack(1)
    list.PushBack(2)

    fmt.Printf("len: %v\n", list.Len())
    fmt.Printf("first: %#v\n", list.Front())
    fmt.Printf("second: %#v\n", list.Front().Next())
}

output:
len: 2
first: &list.Element{next:(*list.Element)(0x2081be1b0), prev:(*list.Element)(0x2081be150), list:(*list.List)(0x2081be150), Value:1}
second: &list.Element{next:(*list.Element)(0x2081be150), prev:(*list.Element)(0x2081be180), list:(*list.List)(0x2081be150), Value:2}
```

list 对应的方法有：

```go
type Element
    func (e *Element) Next() *Element
    func (e *Element) Prev() *Element
type List
    func New() *List
    func (l *List) Back() *Element   // 最后一个元素
    func (l *List) Front() *Element  // 第一个元素
    func (l *List) Init() *List  // 链表初始化
    func (l *List) InsertAfter(v interface{}, mark *Element) *Element // 在某个元素后插入
    func (l *List) InsertBefore(v interface{}, mark *Element) *Element  // 在某个元素前插入
    func (l *List) Len() int // 在链表长度
    func (l *List) MoveAfter(e, mark *Element)  // 把 e 元素移动到 mark 之后
    func (l *List) MoveBefore(e, mark *Element)  // 把 e 元素移动到 mark 之前
    func (l *List) MoveToBack(e *Element) // 把 e 元素移动到队列最后
    func (l *List) MoveToFront(e *Element) // 把 e 元素移动到队列最头部
    func (l *List) PushBack(v interface{}) *Element  // 在队列最后插入元素
    func (l *List) PushBackList(other *List)  // 在队列最后插入接上新队列
    func (l *List) PushFront(v interface{}) *Element  // 在队列头部插入元素
    func (l *List) PushFrontList(other *List) // 在队列头部插入接上新队列
    func (l *List) Remove(e *Element) interface{} // 删除某个元素
```

下面演示一个模拟栈的 pop

```go
x,_ := this.stack.Remove(this.stack.Back()).(int)
return x
```

