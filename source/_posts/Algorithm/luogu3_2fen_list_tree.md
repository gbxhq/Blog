---
title: 洛谷训3-二分/链表/树
date: 2019-06-30 22:22:05
categories: Algorithm
tags: [luoguOJ,Cpp,Algorithm]
mathjax: true
---

知识点：【[**P1182** 数列分段`Section II`](https://www.luogu.org/problemnew/show/P1182)答案二分、前缀和】

<!---more--->

# 递推与递归二分

台阶问题和数的划分。其实就代表了排列和组合两种情况。排列，和顺序有关。组合，不管顺序只看元素。所以要彻底搞清下面的两个问题！

## [**P1192** 台阶问题](https://www.luogu.org/problemnew/show/P1192)

k=2时，其实就是斐波那契。

其他情况就算是斐波那契的变形吧。

举个例子，k=3

$f(n)=f(n-1)+f(n-2)+f(n-3)$

上8层的方法数等于上7\6\5层的方法数之和。

因为最后一步只需要分别再上1\2\3层就是8层了。

---

然后分析一下，当小于k时的情况。

比如k=8。求f(7)

$f(7)=f(6)+f(5)+f(4)+f(3)+f(2)+f(1)$ ?错了

$f(7)=f(6)+f(5)+f(4)+f(3)+f(2)+f(1)+f(0)$ 

**因为7<k，可以之前走0层，最后一步上7层。所以说f(0)=1**

---

有了以上两点就解决了。

## [**P1025** 数的划分](https://www.luogu.org/problemnew/show/P1025)

开始用正常的递归做。输入200的时候过不了。

和上一题一样开始使用数组保存答案了。因为这种题都是可以用记忆化搜索的。

用递归模拟的思路调试很久都很难找到规律。

后来看到这个题解：看成排列组合。n个🍎分k组就是放到k个箱子里。有两种情况

- 有一个箱子里仅1个🍎的情况

  **就等于n-1个🍎分到k-1组的分法**

- 每个箱子至少有2个🍎的情况

  **等于：每个箱子都拿出一个🍎，n-k个苹果分k组的分法**

或者：因为不允许重复，数字都是递增排列的。可以看成这两种情况：

- 第一个数是1，剩下n-1分k-1组
- 第一个数不是1，==每个数都-1，总数变为n-k，分k组。

## [**P1057** 传球游戏](https://www.luogu.org/problemnew/show/P1057)

模拟法和以前一样，不过（来来回回递归内存受不了）

### 找递推方程

f(i,j)表示第j次传到第i个人上的次数。很明显开始只有f(1,0)=1。

就是不传球的时候球在第一个人的情况有1种。

其余情况 f(i,j)=f(i-1,j-1)+f(i+1,j-1)

//等于第j-1次在他左边那个人的情况数+在他右边那个人的情况数

### 控制下标

另外需要一个技巧来把下标控制在1-n之间：用的方法是 -1%n+1

先减1，然后模n再加1.如果防止减1变成0，那就再加个n

Ex:

$10\mod10=10$  -->  $9mod10+1=9+1=10$

$0\mod10=10$  -->  $0+10-1\mod10+1=10$

1~9 模10也不会受影响：

1-1+10%10+1=0+1=1

9-1%10+1=8+1=9

### 最终代码

这题遍历过程外层要从j开始。因为要求`a[i][j]`，必须所有的`a[·][j-1]`都是已知的。

```cpp
ans[i][j]=ans[i-1+n-1%n+1][j-1]+ans[(i+1-1)%n+1][j-1];
```

## [**P1135** 奇怪的电梯](https://www.luogu.org/problemnew/show/P1135)

BFS一次过。简单题

## [**P1182** 数列分段`Section II`](https://www.luogu.org/problemnew/show/P1182)

之前的几道题。用二分的思路。把问题一步步缩小规模。很容易想到思路。

到了这题我就想不明白了。原来这是“答案二分”。

所谓答案二分，就是先确定一个【答案区间】。然后二分地查找。取一个中间值看能实现吗。然后控制【答案区间】变化。直到找到答案。

下面关于二分答案再抄一段别人的分析：

> 我们把这个方法叫做“二分答案”。顾名思义，它用二分的方法枚举答案，并且枚举时判断这个答案是否可行。但是，二分并不是在所有情况下都是可用的，使用二分需要满足两个条件:
>
> 1.有上下界
>
> 2.区间有单调性
>
> 二分答案应该是在一个单调闭区间上进行的。也就是说，二分答案最后得到的答案应该是一个确定值，而不是像搜索那样会出现多解。二分一般用来解决最优解问题。刚才我们说单调性，那么这个单调性应该体现在哪里呢？
>
> 可以这样想，在一个区间上，有很多数，这些数可能是我们这些问题的解，换句话说，这里有很多不合法的解，也有很多合法的解。我们只考虑合法解，并称之为可行解。考虑所有可行解，我们肯定是要从这些可行解中找到一个最好的作为我们的答案， 这个答案我们称之为最优解。
>
> 最优解一定可行，但可行解不一定最优。我们假设整个序列具有单调性，且一个数x为可行解，那么一般的，所有的 x′(x′<x)*x*′(*x*′<*x*) 都是可行解。并且，如果有一个数y是非法解，那么一般的，所有的 y′(y′>y)*y*′(*y*′>*y*) 都是非法解。
>
> **那么什么时候适用二分答案呢？注意到题面：使得选手们在比赛过程中的最短跳跃距离尽可能长。如果题目规定了有“最大值最小”或者“最小值最大”的东西，那么这个东西应该就满足二分答案的有界性（显然）和单调性（能看出来）。**

然后我们再来看一道同类型的。

## [**P1316** 丢瓶盖](https://www.luogu.org/problemnew/show/P1316)

和上一题是一个模板。就是：

```cpp
//1.确定答案范围
//2.二分答案
int ans;
while(l<=r){//!!!这里一定要注意。是<=！
  m=(l+r)/2;
  if(judge(m)){//判断是否是解
    //根据是找最大值还是找最小值填充这里，比如找最大值
    ans=m;//能走到这，说明m是解
    l=m+1;//二分区间继续找解
  }else{
    r=m-1;
  }
}
```

- 特别注意`while(l<=r)`的`<=`
- 

# 线性数据结构

## P1996 约瑟夫问题

竟然是用链表做的。很无聊啊。

- [ ] 为何公式法不行？

## P1115 最大子段和

哎。一毛一样的代码。吃饭前RE。吃了饭回来我调了半天不知道为啥。结果重新提交，AC了。这样的洛谷真的让人体验极差。

## [**P1739** 表达式括号匹配](https://www.luogu.org/problemnew/show/P1739)

本来很简单的一道题。结果4个数据点就是不过。RE

后来在讨论版看到一位红名大佬的箴言：“pop前要判断非空” 加上这个判断条件就过了！哎。还是自己的问题！

```
//if(stk.top()=='(') 错误写法！
if(!stk.empty()&&stk.top()=='(')
    stk.pop();
```

## [**P1449** 后缀表达式](https://www.luogu.org/problemnew/show/P1449)

简单题

# 树形数据结构

**P1082**FBI树 **P1305**新二叉树

简单题

## [**P1030** 求先序排列](https://www.luogu.org/problemnew/show/P1030)

找到规律即可：

- 中序遍历的每个点，左边都是它的左孩子，右边都是它有孩子
- 前序里第一个是根
- 后序里最后一个是根

## [**P5018** 对称二叉树](https://www.luogu.org/problemnew/show/P5018)

- 我本以为可以在递归地判断是不是对称二叉树的同时统计几点个数。后来看了几篇题解并不是。另外他们竟然一直地采用了，数组来做。完全没有用树。还是很神奇的。