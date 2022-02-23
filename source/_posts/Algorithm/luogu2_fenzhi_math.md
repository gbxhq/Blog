---
title: 洛谷2-分治/数学
date: 2019-07-11 09:50:46
categories: Algorithm
tags: [luoguOJ,Cpp,Algorithm]
mathjax: true
---

知识点：快速幂 高精 负进制

<!---more--->

# 分治

## [**P1226** 【模板】快速幂||取余运算](https://www.luogu.org/problemnew/show/P1226)

https://www.luogu.org/blog/costudy/base-2

就看这一篇题解！！！

然后下面备份一下代码：

```c++
int quickPow(int a,int b){
	int ans=1;
  while(b){
     if(b&1)//b是奇数吗？(最后一位是1)
    		ans*=a;
  	a*=a;
    b>>=1;//b/2 这里千万别忘了加b=
  }
	return ans;
}
```

## [**P1908** 逆序对](https://www.luogu.org/problemnew/show/P1908)

以单独开贴 [逆序对](../逆序对)

# 简单数学问题

## [**P1088** 火星人](https://www.luogu.org/problemnew/show/P1088)

- Algorithm.h里有个`next_permutation(beg,end,comp)`的方法，可以查看排序的下一个序列。通过这个方法。这题不用写就过了

- [ ] https://www.luogu.org/blog/abc123-yummy/solution-p1088

  上面的大神思路，再刷一遍。

## [P1045 麦森数](https://www.luogu.org/problemnew/show/P1045)

### 求2^p-1位数

- 求$2^p-1$位数等于求$2^p$位数，因为$2^p$最后一位不可能为0。

- 数$10^n$位数一定是$n+1$,因此考虑改写成以10为底的x次幂

  问题变成：$10^x=2^p，求x$

- 解得,$x=log_{10}{2^p=p·log_{10}2}$， 所以位数为 $p·log_{10}2+1$

### 高精乘法

先想明白这个问题：一个数a[20]位，一个数b[20]位。相乘结果最多有多少位？

> 40位。小学生都会的你不会。

下面看具体的高精度乘法：

- 首先每个数在数组里都是倒着存的。这一点一定要想明白啊。比如25存在高精里就是`{5,2,0，……,0}` 倒着看就是00025了。

- 求a=a*b 看代码

  ```c++
  a[10]={5,2,0};b[10]={5,2,0},c[10];
  
  memset(c,0,sizeof(c));//c清零用于临时计算结果
  //如果直接用a存a*b的值，a本身就在变化
  
  for(i:0..10){
    for(j:0..10){
      c[i+j]+=a[i]*a[j];//注意这里是 += 啊！！！！！！
    }
  }//不带进位乘完了
  for(i:0..10){
    c[i+1]=c[i]/10;
    c[i]%=10;
  }//处理进位
  
  memcpy(a,c,sizeof(a));//计算完毕
  ```

### 本题其他细节：

- `<cmath>`头文件中有`log10()`方法。前面记得加`(int)`把double转成int

- `memset(a,0,sizeof(a))` 给数组赋值（关于这个函数请注意看下题，只能用于初始化内存）

  `memcpy(a,b,sizeof(a))` 把**b**复制到a

  这两个方法在`cstring`头文件



## [P1403 [AHOI2005]约数研究](https://www.luogu.org/problemnew/show/P1403)

- 问题来了：`memset(a,2, sizeof a);`怎么不能用啊

  > 答

  memset() 是按字节拷贝。一个字节8位

  而一个int是4个字节。就是32位。

  现在对数组a[]的每个字节赋值2。就是每8位变成: 00000010

  那数组里的每个数字都变成了：

  00000010 00000010 00000010 00000010

  所以说`memset()`这东西就初始化内存赋值0的时候好使。其他时候反而不好用了！

- 使用`fill()`赋值:

  ```c++
  fill(a,a+n,2);
  ```

然后这题逻辑上比较简单，和用筛法求素数一个道理。**简单题。**

## [**P1017** 进制转换](https://www.luogu.org/problemnew/show/P1017)

知识点：负进制

简述：负进制转换和正进制一样都是相除取余数再倒着输出就是结果。

其关键在于：余数是负数时，总不能1011-100-1这么拼接吧。

因此让 **负余数-进制**得到**正余数**，同时**商要+1**。

$ x \div y = n ···m$   ==化成==>  $ x \div y = n+1 ···m-y$

正确性证明： 

$$y\times n+m=x$$

$$y\times (n+1)+m-y=y\times n+y+m-y=y\times n+m=x$$

领悟一下吧。下面循环代码直观地复现了这个过程

```cpp
while (n){
        int m=n%r;
        n/=r;
        if(m<0)//余数为负时需要处理
        {
            m-=r;//余数化为正
            n++;//商+1
        }
        if(m>=10)
            ans=(char)('A'+m-10)+ans;//倒输出 新位放在前
        else
            ans=(char)('0'+m)+ans;
}
```

## **P1147** 连续自然数和

经典题，剑指Offer 41、LeetCode 829. 其中LeetCode最难。

### 尺取法。

此方法过不了LeetCode: 数据太大超时，$O(n)$都不过。必须优化成$O(log_n)$

思路看代码：

```c++
for (int i = 0,j=1,sum=1; i <=m/2;) {
  //初始队列[0，1]，终止条件，队头数字为m/2，加上后面的肯定超了。
  //可不可取m/2呢。是可以的。因为奇数/2向下取整。
    if(sum==m){
        cout<<i<<' '<<j<<"\n";//符合
        sum-=i;//去掉第一个数
        i++;//去掉第一个数后 第一个数变成i++
    }
    if(sum<m){//不够
        j++;	//先加长序列
        sum+=j;//再更新和
    }
    if(sum>m){//超了
        sum-=i;//这次要先去掉第一个数
        i++;	//去掉第一个数后 第一个数变成i++
    }
}
```

### 公式法

设端点为【L,R】，有$(L+R)(R-L+1)/2=M$，即求x,y

令 $L+R=X,R-L+1=Y$,

即求$X\times Y=2M$满足的X、Y值。

有了满足条件的两个因子X、Y后。可解得：

$L=(X-Y+1)/2 $ , $R=(X+Y-1)/2 $

L和R都是整数，从R的式子可推出X、Y必须一奇一偶。

X先取$\sqrt{2M}$。随着X减小，Y会不断增大。

代码：

```cpp
int ans=1;
for(int x=(int)sqrt(2*N);x>1;x--){
    if(2*N%x==0){
        int y=2*N/x;
        if((y-x+1)%2==0&&(x&1)^(y&1))
            ans++;
    }
}
```

可过LeetCode

## [**P1029** 最大公约数和最小公倍数问题](https://www.luogu.org/problemnew/show/P1029)

- 辗转相除法

```cpp
int gcd(int a,int b){
    if(b==0)
        return a;
    return gcd(b,a%b);
}
```

- $a\times b =(a和b的最大公约数) \times（a和b的最小公倍数）$


