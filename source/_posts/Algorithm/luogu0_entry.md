---
title: 洛谷0-入门
date: 2019-06-11 18:23:42
categories: Algorithm
tags: [luoguOJ,Cpp,Algorithm]
mathjax: true
---

新手场和普及场前6关

<!---more--->

# 新手场

## 顺序与分支

### P1422 小玉家的电费

控制输出精度：cout.xxx(); 待查询

---

### [**P1089** 津津的储蓄计划](https://www.luogu.org/problemnew/show/P1089)

注意 int 和 float 相乘，输出格式用 "%d" 数字会面目全非

---

### [**P1909** 买铅笔](https://www.luogu.org/problemnew/show/P1909)

INT_MAX存在<limits.h>里，不加.h也不行

## 循环

### P1035 级数求和

- 我写了一个求和的函数Sn(int x)，然后把x从1到n开始试。这样其实n=3的时候，又要从新从1加到3。n等于4的时候，又要重新从1加到4。上一次的结果就全部浪费了。导致最后超时。**所以要边加边判断。**
- **涉及到int和float夹杂在一起的运算**，特别是结果要是float的。一定要处处注意不要写整形参数，1要写成1.0  0要写成0.00 
- 仔细分析n++后，最后输出的那个n，是ans+1了还是就是ans。
- 用double别用float
- [x] 重刷标记

## 数组

### [**P1047** 校门外的树](https://www.luogu.org/problemnew/show/P1047)

数组声明后不遍历赋值，并不是默认都是0.(不同于Vector)

延伸：

> **局部数组：**没有默认值，如果声明的时候不定义，则会出现随机数（undefined）；如果声明的长度与赋值长度不相等，则有，声明的长度>赋值长度，后面用0补足，声明的长度>赋值长度，发生编译错误；
>
> **全局数组：**声明时不赋值，默认值为0 
>
> **指针new：**动态获取的内存，默认值undefined

## 简单字符串

### P1308 统计单词数

要高性能？怎么都做错了。

- [x] Mark

关键：在找单词出现的第一个位置时，因为有空格来区分单词，必须完全匹配。需要这样处理

```cpp
target = " "+target+" ";
article = " "+article+" ";
int ans = article.find(target);
```

## 过程函数与递归

### P1028 数的计算 

递归的方法我写出来了。但是超时。

我每次跑都会把之前算过的值重新跑一遍。最后相当于浪费了很多。

解决方法就是：用数组存每个n的结果，然后读取就可以了。

### P1036 选数

就是递归写排列组合，我竟写了这么久。

不写代码就是手生啊。

## Boss战入门1

### [**P2089** 烤鸡](https://www.luogu.org/problemnew/show/P2089)

走前就是写不出来思绪混乱。周末回来后，思路比较清晰。划重点：学会把递归的现有结果暂存到数组中！然后把数组当做变量传入下一次递归。思路清晰。

## Boss战入门2

### **P1464** Function

这题有个题解说用"记忆宏"，如下：(类似树状数组里定义左右孩子)

`#define W_MEM(x,y,z) (w_mem[x][y][z] ? w_mem[x][y][z] : w_mem[x][y][z] = w(x, y, z))`

### [**P1014** Cantor表](https://www.luogu.org/problemnew/show/P1014)

简单题，不看

### [**P1307** 数字反转](https://www.luogu.org/problemnew/show/P1307)

j—到i后的情况 是if(j>i)还是if(j>=i) 

最好模拟一下。不然有些极端情况还是考虑不到。

==>说白了不就是**如果j==i的时候要不要执行下面的语句**

# 普及练习场

## 简单模拟

### P1003 铺地毯

- 开数组开这么大干啥？没必要真的用数组模拟出一个地面。

  只需要用一个数组记录下来每次输入的四个坐标就行了啊。

  - 边输入(cin)，可以直接把数存到数组里

### [**P1067** 多项式输出](https://www.luogu.org/problemnew/show/P1067)

- 没考虑系数是1的情况 输出了 `1x`  `-1x`这种尴尬
- 没考虑x次数是1输出 `x^1` 

### [**P1056** 排座椅](https://www.luogu.org/problemnew/show/P1056)

贪心入门 涉及知识点主要：

-  结构体排序

  ```c++
  bool cmp(s a,s b){//注意这个比较函数一定要写全局里
    return a.value<b.value;//这就是小的放前面
  }
  ```

- 利用结构体排序，达到对一组数的值排序后，输出原下标的结果

  (因为**题目输出结果是下标从小到大输出**)开始我比较笨，先把结构体排序后。又把下标存起来。又排序。

  正解：直接写两个排序规则，第一个是按值，第二个是按下标：

  ```c++
  sort(ans1.begin(),ans1.end(),cmp);
  sort(ans1.begin(),ans1.begin()+K,cmp2);
  ```

  这样第一行对值排序了。 第二行拿出排序后的前K个(要求输出的)，再按下标排序就符合输出要求了。

## 交叉模拟

### [**P1031** 均分纸牌](https://www.luogu.org/problemnew/show/P1031)

- 想到思路很重要，这一题竟然只要每次都从左往右移动，就能成功。
- 在循环中，遇到可以跳过(`if(xxx)continue;`)的情况，记得要把一些标志位(如`flag`)清空掉。不然虽然循环continue了，但上一次循环的"脏数据"会继续影响下面的循环。

### [**P1042** 乒乓球](https://www.luogu.org/problemnew/show/P1042)

简单题Pass

### P1098 字符串的展开

这题繁琐不要重做，但要看看这几个要点

- `replace()`

  我是把`'a'`换成`str`，然后注意的就是，第二个参数是长度。

  所以要写成`s.replace(s.find(' '),1,str)`  开始把第二个参数当成了

- `transform(temp.begin(),temp.end(),temp.begin(),::toupper);` 这种写法要会。特别是最后一个参数。

### [**P1086** 花生采摘](https://www.luogu.org/problemnew/show/P1086)

花生这题简单的模拟。顺利AC。出了点小差错：

- if的情况写完没有对应的else。

  这题里，我对数组循环遍历。if(xxx)就继续往下执行。结果if不成立没有对循环break;导致循环继续跑下去。要谨慎！

## 排序

### [**P1177** 【模板】快速排序](https://www.luogu.org/problemnew/show/P1177)

惊喜啊！我写快排超时了！！！纳尼。。。太好了啊。如果没有洛谷OJ。我都不知道其实我的快排都是有问题的！！！赶紧去改了！

看了这篇题解，https://www.luogu.org/blog/adamding/solution-p1177 和这篇博客https://blog.csdn.net/hacker00011000/article/details/52176100说明了快速排序的几个问题：

- 已经有序的情况，每次只能安排好第一个元素 退化成O(n^2)的冒泡
- 区间分割较小时，还是会层层递归
- 大量重复数字时，(快排是不稳定的嘛)，也会处理。

针对上面三个情况，楼主提出三种优化：

- 随机比较
- 小区间直接插入排序
- **在一次分割结束后，可以把与Key相等的元素聚在一起，继续下次分割时，不用再对与key相等元素分割**

---

哎。我最后也没弄明白为啥它这个解法能过。

https://blog.csdn.net/u011815404/article/details/79889355

问了龙哥，果然好使。上面这个人的写法。更像归并！

主要思想：取中间的数做标杆。然后每一趟循环之后，数组的左右两侧，左边的一定小于右边的。

---

最后找到了我的错误：就是这种情况：

```c++
 int m = a[(i+j)/2];
```

是用m取出来和后面的比较呢。还是

```c++
int m = (i+j)/2;
a[m];
```

这样呢？

一定要看后面 i和j 会不会变啊！

然后根据情况决定。

---

排序这一组后面的题，借助于sort函数，基本都没写。但是基础的几个排序算法我还是很需要去加深的。就先这样吧继续往下刷了。

## 排序Ex

### **P1583** P1051 P1093

- [x] 不要重做标记 

  P1583本身很简单，只不过题意中有个序号，有个编号。要看清都用来做什么、输出什么。
  
  后面两个题一样没技术含量

## 字符串

### [**P1012** 拼数](https://www.luogu.org/problemnew/show/P1012)

令人窒息的操作

```c++
bool cmp(string s1,string s2){
  return s1+s2<s2+s1;
}
```

### [**P1603** 斯诺登的密码](https://www.luogu.org/problemnew/show/P1603)

虽然AC了。但我竟然之前傻傻地要把int转成string再比较。这题直接用int输出就行啊。

## 贪心

### [**P1090** 合并果子](https://www.luogu.org/problemnew/show/P1090)

开始我每次都用sort()对数组拍一次序，找到最小的2组合并。但是：超时了。

对啊。只要找到最小的两组就行了。为啥要对整个数组排序呢。那样复杂度怎么也是$\Theta(nlog_n)$及以上的啊。而我遍历整个数组找到最小的数只需要n次。

看到一个STL优先队列的解法(重点记一下声明时的三个参数

)：

```c++
priority_queue<int,vector<int>,greater<int> >q;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x,q.push(x);
    while(q.size()>=2){
        int a=q.top(); q.pop();
        int b=q.top(); q.pop();
        ans+=a+b;
        q.push(a+b);
    }
    cout<<ans<<endl;
    return 0;
}
```

看来proirty可以实现每次有插入删除的时候都执行换位操作。

**需要注意的是，优先队列里使用从greater排序，首元素最小（不同于sort里的调用）。所以题解中的`q.top`以及`q.pop`都是针对【首元素】的**

查了下：`priority_queue`比较方式默认用**operator<**，所以如果把后面2个参数缺省的话，优先队列就是大顶堆（降序），**队头元素最大**。

### [**P1181** 数列分段Section I](https://www.luogu.org/problemnew/show/P1181)

讨论：这题为何贪心是最优？

> 贪心多用反证法证明、如果这样划分不是最优，则假设有xxx解法是最优，最后推出矛盾。

### [**P1208** \[USACO1.3\]混合牛奶 Mixing Milk](https://www.luogu.org/problemnew/show/P1208)



用sort对结构体排序。结果呢，人家数据是5000个一样的。神奇的事情发生了。这个用例能不能过，竟然就在一=号只差：

```c++
bool cmp(farmer f1,farmer f2){
    if(f1.price!=f2.price)
        return f1.price<f2.price;
    else
        return f1.count>f2.count;//这样就能过
        return f1.count>=f2.count;//这样就不能过！！！
}
```

以后还是不要多加`=`号了！

猜测是。5000个一样的数据情况下，加了等号会导致相等的两个比较时仍做位置交换，导致时间变慢。