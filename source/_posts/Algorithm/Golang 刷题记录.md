---
title: Go 刷题记录
date: 2020-03-08 21:32:39
categories: [Algorithm]
tags: [Go,Algorithm]
---

刷了大概 50 道题，我个人的结论：在中等难度题中，使用 Golang 的效率完全是不输于 C++的，特别是在 Golang 没有 C++这么完善的 STL 库的情况下，只借助 container 包里的三种数据结构，大部分题时间、空间复杂度都可以媲美 C++。当然这个 hard 题是啥情况我这个蒟蒻就不知道咯。

<!--more-->

> 再刷洛谷试炼场，发现试炼场已经无了。开始以为找不到了，知乎上看到站长的回复才知道真的无了。我是从这个人整理的版本里刷的：https://www.luogu.com.cn/paste/66uuuvdr 用 Go 大概刷了 10 道题之后，放弃洛谷。原因是洛谷几乎都是 C++选手。
>
> 继续用 Go 在 LeetCode 刷题。遇到什么写什么吧。纯纯的笔记。非专题性内容。

## 输入输出

> 才发现用 go 刷题连输入输出都不会

- `print` 在golang中 是属于输出到标准错误流中并打印,官方不建议写程序时候用它。可以debug时候用

- `fmt.print` 在golang中 是属于标准输出流,一般使用它来进行屏幕输出.

## 处理字符串

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
- [03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/) 交换法

## 快慢指针

快指针在前面探路，慢指针满足条件再走。

eg. 删除数组、链表中的重复元素

283 删除0

我的方法：遇到 非0 就填充，最后把没填充的再填充 0；

更优：遇到非 0，就交换。这样 0 会被不停地往后换。

## 前缀和

**快速算区间和**

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

## 差分数组

**☆☆☆频繁对区间进行删减的情况☆☆☆**

![img](https://raw.githubusercontent.com/gbxhq/Pic/main/chafenshuzu.jpeg)

- `nums[i] = diff[i] + nums[i-1]`

- `nums[i..j]` 都 +3 等于 `diff[i]+=3 , diff[j+1]-=3`

  但是注意， nums 更新最后一个数字时，diff[j+1]会越界，所以不用再更新

- 遍历 diff 数组即可还原 nums 数组。

[1094. 拼车](https://leetcode-cn.com/problems/car-pooling/)

[1109.航班预订统计](https://leetcode-cn.com/problems/corporate-flight-bookings)

## 回文

## 二分

直接二分搜索

```go
// 关键两点
for i<=j { //1. <=
  m = i+1  //2, 边界 +1 / -1
  m = j-1
}
```

**二分一定记得不要重复使用已经判断过的边界m，下次循环一定要m+1、m-1** 

[34.在排序数组中查找元素的第一个和最后一个位置（中等）](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

### 二分变形

通过二分查找试出最佳值

- 取整技巧：` (x + n -1)/n == int(ceil(x/n))`

## 滑动窗口

我写的滑动窗口有思想问题

比如找无重复的最长子串，滑动[i..j]，我是 外循环 j++，j 不停地往后，发现重复则把 i 更新到出现过的位置。清空 map 重新记录一次。

标准的思想：[i..j]，外循环是 i ++， 每次以 i 为开头，内循环 j ++ 尝试找出 以 i 开头最长的。

每次外循环 i++时 删除 map 里的前一个元素 `delete(m, s[i-1])`

## container

go 里没有栈。但container 包里的 list、heap和 ring 也勉强够用。

只是用起来稍微有点绕（特别是不能定义容器的元素类型，遇到返回 Value 的题还要断言一下）

下面遇到某个 container 就整理一下

### list

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

## 使用注意

```go
this.Lst.MoveToFront(ele)
不等于
this.Lst.Remove(ele)
this.Lst.PushFront(ele)
为啥呢?
看Remove()源码得知，这里面为了防止内存泄漏，在 remove ele后就会吧 e 的指针全部置nil，这样 e 就已经作废了。没法再进行PushFront

还有这里
if ele.Prev() == nil {
		//	head, update value
			p := ele.Value.(pair)
			p.v = value
  这里并不能改变 p 的 v 值
		} else {
			// remove and insert to head
			this.Lst.Remove(ele)
			this.InsertToHead(key, value)
		}
```

## heap

- 注意，heap 只是保证顶部是最小。不会保证按顺序输出是最小

- 实现 interface 时只需要注意 Pop() 方法的写法 ，比如最简单的 []int 类型：

  ```go
  func (p *PriorityQ) Pop() interface{} {
  	n := len(*p)
  	old := *p
  	x := old[n-1]
  	*p = old[:n-1]
  	return x
  }
  ```

  

# 单调栈、单调队列

「单调栈」 Next Great Number 类问题

「单调队列」滑动窗口相关的问题

# 二叉树

## [114.二叉树展开为链表（中等）](https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list)

这里有一点需要注意就是递归的去处理 root 的左右子树 x 和 y 时，

```go
root.Left = nil #左子树指向 nil
root.Right = x # 右指向 x 没毛病
# x.Right = y #这样就错了
应该是循环往下找到最右下角的节点z，把 z 的right 指向 y
# 比如下图， root = 1， x=2, y=5，1.right=2 没毛病，但不应该 2.right=5，应该是 4.right=5
		 1
	/ 		\
  2			 5
   \      \
    3		   6
     \
      4
```

root.Left = nil 

## 二叉搜索树的变更

三种情况

- 叶子节点，没啥牵挂
- 一个孩子，方便
- 俩孩子，不好管理

# BFS

LeetCode752，我的 BFS 为啥超时呢。

- 首先，queue队列用数组就可以实现，没必要用container 包里的 list（但这个影响也不大）

- 比较重要的一点，慢的 BFS 是用了层序遍历思想，每次把同级别的符合条件的都入队，

  其实这样也可以实现。但是这会导致什么情况：

  - 入队的数量呈指数级别上升。比如这次入队 2 个，下次入队就这 2 个的下一种情况4 个，然后就是 8、16

    最终就会发现队列超级长

  而只需要每次都只取队列里的头部 1 个！1 个！1 个元素！，这样就大大降低了队列的长度。（只是循环次数会增加）

  **但是有一说一。我只分析出这两种方案这里会不同。还是没法分析出为啥那个就可以秒出结果。**

# 回溯

- 全排列

go 的这个切片这一块，回滚是真的麻烦。

比如你先把第 i 个元素给 remove，再接 i 回来就得这样：

```go
x:=nums[i] //存下 i
nums = append(nums[:i], nums[i+1:]...) //删了 i
f(nums, one, ans)
nums = append(nums[:i],append([]int{x},nums[i:]...)...) //再接上，关键这个接上也太扯淡了
```

没办法，要么就重新开辟一个切片做深拷贝：

```go
# 深拷贝笨方法
for j,k:=0,0; j<len(nums); j++ {
  if j==i {
    continue
  }
  tmp[k] = nums[j]
  k++
}
# 深拷贝
slice1 := []int{1,2,3,4,5}
slice2 := make([]int,5,5)
copy(slice2,slice1)
```

这里注意一个切片append的细节：

```go
x := []int{1,2,3}
y := append(x[:0], x[1:]...)
out("x", x) //Notice
out("y", y)
println(len(x))
输出：
x:2 3 3 注意 x 本身也已经发生了改变,说明啥，虽然append后赋给了新变量 y ，但操作还是基于x的内存地址的。切片全是引用操作。
y:2 3 
len(x): 3
```

# DP

有最优子结构的问题：

- 可以【自顶向下】，使用递归来做。拆分问题。其中递归的过程里可以使用【记忆化】的技巧，避免多次计算。

  更进一步

- 直接【自底向上】，使用一个结果数组，一步步推导上去。比如求ans[n]，我从 ans[0]开始一直求到ans[n]，反正你上面递归的方法也是一层层都求过一遍的。

# 排序

go 倒序

```golang
sort.Sort(sort.Reverse(sort.IntSlice(coins)))
```

