---
title: C++语法笔记
date: 2018-07-06
categories: cpp
tags: [cpp,Note]
---

语法的笔记。用到啥就复制点。仅供个人查阅~

<!---more--->


# 基本

- printf的格式化输出 ：https://www.jianshu.com/p/fdb537c40a9d

- (int)(3*1.5)` 默认向下取整得到4

- char：字符型与整型相比只是更加节省内存。（在所有数据类型中，char类型占用的内存空间最少）所以可以用来代替int使用

- 计时

    ```cpp
    #include<ctime>
    clock_t start = clock();
    cout<<clock()-start;
    ```

- inline

    内联函数，在函数被调用时就展开。比较快，开销小。

    但会使代码膨胀，尤其是内联函数处理复杂，尽可能少用。

- const

    ```cpp
    const int* a = x;
    int* const b = y;
    const int* const c = z;
    ```

    a不能修改所指的内容。但是能指向其他地方。

    b能修改所指的内容。但是禁止修改b本身（不能指向其他地方）。

    c都不能。

    ```cpp
    const int& a = x;
    //这种写法可以禁止引用修改它所指向的变量
    //注意，不可以利用这一点来达到“传入引用，并肆无忌惮地修改，最终不破坏原值”的目的。因为const引用，做了内容修改会导致，编译器报错。
    ```

- void指针

    **void**的字面意思是“无类型”，**void**则为“无类型指针”，**void**可以指向任何类型的数据。
    
    作用：
    　　（1）对函数返回的限定；
    　　（2）对函数参数的限定。
    
    使用:
    
    ​	在C语言中，可以给无参数的函数传送任意类型的参数，但是在C++编译器中编译同样的代码则会出错。在C++中，不能向无参数的函数传送任何参数，出错提示“’fun’:functiondoesnottake1parameters”。
    　　所以，无论在C还是C++中，若函数不接受任何参数，一定要指明参数为void。
    

## 数组

**局部数组：**没有默认值，如果声明的时候不定义，则会出现随机数（undefined）；如果声明的长度与赋值长度不相等，则有，声明的长度>赋值长度，后面用0补足，声明的长度>赋值长度，发生编译错误；

**全局数组：**声明时不赋值，默认值为0 

**指针new：**动态获取的内存，默认值undefined

关于数组初始化，这里写的很详细！https://www.cnblogs.com/bluecagalli/p/9511126.html

### 函数参数传数组但不改变数组值

以下做法是否可行并未测试

```cpp
int sum(const int *a[]);/*形参为常量指针数组, 数组aa的每个元素都是常量指针, 不会改变实参的值*/
```



## Char* 字符串数组

参考：https://www.cnblogs.com/kungfupanda/archive/2012/06/15/2456931.html

我就抄点我用到的     定义与初始化

```cpp
char str[ ]={"I am happy"}; //可以省略花括号，如下所示
char str[ ]="I am happy";
```

注意：上述这种字符数组的整体赋值只能在字符数组**初始化**时使用，不能用于字符数组的**赋值**。但是字符串指针就可以这么赋值：

```cpp
char *a;
a = "I love China."
```

输出方式

```cpp
char str[] = "http://c.biancheng.net";
printf("%s\n", str);  //通过变量输出
puts(str);  //通过变量输出
cout << str ; //C++可以这样
```

### Note！关于声明时赋值

c++ 里面 如果你写

```cpp
char *af ="bbbb";
```

会报错` Conversion from string literal to 'char *' is deprecated`  

这是什么原因呢，书上是这么写的：

c++从c语言继承下来的一种通用结构是c风格字符串，char 字符串字面值就是这中类型的实例，而字符串字面值的类型是const char 类型的数组，是以空字符null结束的字符数组。

    char ca1[] = "hello";//正确 包换null
    char ca2[] = {'h','e','l','l','o'};//不含null
    char ca3[] = {'h','e','l','l','o','\0'};//包含null

代码可以看出，ca1和ca3是属于c风格字符串。
现在回到问题中，那么正确的写法是什么呢？

```cpp
char af[] = "hello";
char const *af = "hello";
```

以上两种方式都是正确的，而为什么要加上const，因为char字符串字面值是不允许修改的，原因如下：

```cpp
char const *ak ="ffff";
ak = "hello";
```

ok，编译正确，这里并木有修改 * ak的值，而是把ak重新指向了“hello”

```cpp
char const *ak ="ffff";
*ak = "h";
```

编译有错误“Read-only variable is  not assignable”

## String

- string 转 char*: 

    ```cpp
    string a = "123";
    int x = atoi(a.c_str());
    ```

- [头文件string与string.h的区别](http://www.cnblogs.com/Cmpl/archive/2012/01/01/2309710.html)https://www.cnblogs.com/curo0119/p/8304924.html

- 这篇文章后面对string基操介绍挺全https://www.luogu.org/blog/co2021/solution-p1032

- string之间相比较，只有同长度才返回结果。（先判断一下谁长

- string对象的操作

  ```cpp
  istringstream os
  os<<s   //s写入到输出流os中。返回os
  is>>s	//从输入流is读取字符串赋给s，返回is。
  s.empty()
  s.size()
  ```
  
- ```c++
  //std::string的大小写转换
  transform(strA.begin(), strA.end(), strA.begin(), ::toupper);
  ```
  
### sprintf

```c++
int a, b;
scanf("%d%d", &a, &b);
sprintf(buf, "%d", a + b);
puts(buf);
```

可以把数据输出到字符串中  

c++11标准增加了全局函数std::to_string:

`string s = to_string(123);`

**一.利用stringstream类**

字符串到整数

```cpp
stringstream sstr(str);
int x;
sstr >> x;（即从sstr中提取数据)
```

 整数到字符串

```cpp
stringstream sstr;
int x;
sstr << x;
string str = sstr.str();
```

缺点：处理大量数据转换速度较慢。stringstream不会主动释放内存，如果要在程序中用同一个流，需要适时地清除一下缓存（用stream.str("")和stream.clear()).

### npos

- 用法

  ```c++
  //find 函数 返回jk 在s 中的下标位置 
  position = s.find("jk");
   if (position != s.npos)  //如果没找到，返回一个特别的标志c++中用npos表示，npos取值是4294967295，
   {
    cout << "position is : " << position << endl;
   }
   else
   {
    cout << "Not found the flag" + flag;
   } 
  ```

- 原理：

在MSDN中有如下说明：

> basic_string::npos
> static const size_type npos = -1;//定义
> The constant is the largest representable value of type size_type. It is assuredly larger than max_size(); hence **it serves as either a very large value or as a special code**.

以上的意思是npos是一个常数，表示size_t的最大值（Maximum value for size_t）。许多容器都提供这个东西，**用来表示不存在的位置**，类型一般是`std::container_type::size_type`。

```cpp
#include <iostream>  
#include <limits>  
#include <string>  
using namespace std;  
  
int main()  
{  
    size_t npos = -1;  
    cout << "npos: " << npos << endl;  
    cout << "size_t max: " << numeric_limits<size_t>::max() << endl;
}
```

执行结果为：

​                 **npos:        4294967295**

​                 **size_t max:  4294967295**

可见他们是相等的，也就是说npos表示size_t的最大值

## stream

```cpp
#include<sstream>
stringstream ss;
int a = 10;
ss>>a;
string s = ss.str(); //stream转string
```

用这个可以实现各种转string。需要注意的是：

**ss一直不会清空。ss一直不会清空。ss一直不会清空。**要这么清空：

`ss.str("")` 就是把空字符串赋值给它

### 分割单词

```cpp
#include <sstream>
void func(string s) {//s是一个句子。有空格有单词
    istringstream is(s);//把String s变成一个输入流is
    string word = "";
    while (is >> word)
    {
        //对word进行操作
    }
}
```



## 类

-   禁止在栈中实例化的类：

    栈空间有限。如果一个类中有大量数据。应尽可能在栈中实例化它，而只允许在堆上创建其实例。做法：

    ```cpp
    class A{
    private:
        //大量的数据
        ~A();
    };
    ```

    没错。就是把析构函数设为私有。这时候在main中声明一个A a,由于编译器会在main()末尾调用析构函数，而私有不可用。编译报错。

    那怎么析构？

    ```cpp
    class A{
        ...//略
    public:
        static void DestroyInstance(MonsterDB* pInstance){
            delete pInstance;
        }
    }
    A* a = new A();
    A::DestroyInstance(a);
    ```

-   与struct不同：

    struct中成员默认为共有。class默认为私有。

    除非指定了，否则struct以公有方式继承基struct。class为私有。

-   友元

    ```cpp
    class A{
    private:
        //...data...
        friend void DisplayAge(const A& a){
            show(a.data);
        };
        friend class B;
    };
    class B{
    public:
        void func(const A& a){
            show(a.data);
        }
    };
    //友元函数和类都可以访问到private数据
    ```

### 关于继承

派生类重载了基类的一个方法后，若又想调用一下父亲的方法：

```cpp
B.A::func();
```

-   应避免写与基类同名但参数不同的func，以免隐藏基类func。

-   私有继承：

    基类中的方法、成员全部不可访问。从继承层次结构来看，私有继承并非is-a关系。私有继承使得只有子类才能使用基类的属性和方法，因此也被成为has-a关系。

-   保护继承：

    也表示has-a。在继承层次结构外，也不能通过派生类实例访问基类的成员。
    
-   虚继承：

    ```cpp
    A; 
    B:public A; C:public A; D:public A; 
    E:public B,public C,public D;
    ```

    这时候构造一个E，够构造一个B\C\D和**三**个A！显然不科学，正确做法是采用虚继承：

    如果派生类 可能被用作基类， 派生他最好使用关键字 `virtual`

    ```cpp
    A; 
    B:public virtual A; C:public virtual A; D:public virtual A; 
    E:public B,public C,public D;
    ```

    

### 多态

基类A，派生类B。现在声明一个A* p,并指向B的object：b.

然后delete p. 会发现，仅仅析构了A，而没有析构B。发生内存泄漏。

如果将A的析构函数声明成virtual的，则delete p时，析构A完会自动析构B。

如果A中存在纯虚函数`virtual void func()=0;`这个A是不能被实例化的。也叫抽象基类。



## 读写文件

https://www.cnblogs.com/liaocheng/p/4371796.html

```c++
//写文件实例
#include<fstream>

ofstream File("xxx/xxx.txt",ios::out); //打开，没有回创建
if(File.fail()){
  cout<<"ERROR"<<endl;
  exit(0);
}
else
  cout <<"Opened"<<endl;

File << "Hello." <<endl; //写入。若有内容会清空
```



# STL

## Vector

容器是连续的内存区。有1.5倍的容量大小。可以避免开数组设置大小的问题。

### 初始化

- 默认构造函数

  ```cpp
  vector<int> vt(10); //10个0
  vector<int> vt(10,1); //10个1
  ```

- 数组地址初始化

  ```cpp
  int a[3] = {1,2,3};
  vector<int> vt(a,a+3);
  ```

- 文档中看到的方法，编译过不了?

  ```cpp
  std::vector<int> v1{1, 2, 3};
  ```
  
- 二维初始化：

  ```cpp
  vector<vector<int>> vt(n,vector<int>(m,0));
  ```

  


### 遍历

- 迭代器

  ```cpp
  ST tmp;
  vector<ST>:: iterator iter;
  for(iter = vt.begin();iter != vt.end();iter++){
      tmp = *iter;
      //取到了
  }
  ```

- `at()` 括号里是下标。跟数组一样访问就行了。`tmp=vt.at(5);`

### 去重

```cpp
 v.erase(unique(v.begin(), v.end()), v.end());
```

unique()函数**将重复的元素放到vector的尾部** 然后返回指向第**一个重复元素的迭代器**再用erase函数擦除从这个元素到最后元素的所有的元素

### 统计

```cpp
count(a.begin(),a.end(),value)
```

## Queue

优先队列`priority_queue` 默认排序方式是<,且注意`q.top()`是最大值。如果想让`q.top()`是最小值，比较函数应使用`greater()`，和sort是反着的。

下面重点说一下队列里的元素是自定义结构体的情况（需要重载运算符）

```cpp
struct cmp1{
    bool operator()(node x,node y){
        return x.num>y.num;
    }
};//优先队列小的在前面
priority_queue<node,vector<node>,cmp1>q;//初始化
```



## Map

遍历

```cpp
map<int, int>::iterator iter;
iter = _map.begin();
while(iter != _map.end()) {
    cout << iter->first << " : " << iter->second << endl;
    iter++;}
```

查找：

```c++
if(map.find('x')!= _map.end())
  找到了;
else
```



## Set

```cpp
int numList[6]={1,2,2,3,3,3};
//1.set add
set<int> numSet;
for(int i=0;i<6;i++){    //2.1insert into set
    numSet.insert(numList[i]);
}
//2.travese set
for(set<int>::iterator it=numSet.begin() ;it!=numSet.end();it++){
    cout<<*it<<" occurs "<<endl;
}
//3.set find useage
int findNum=1;
if(numSet.find(findNum)!=numSet.end())
    cout<<"find num "<<findNum<<" in set"<<endl;
else
    cout<<"do not find num in set"<<findNum<<endl;	
//set delete useage
int eraseReturn=numSet.erase(1);
if(1==eraseReturn){
	cout<<"erase num 1 success"<<endl;
else
    cout<<"erase failed,erase num not in set"<<endl;
return 0;
}
```

# Algorithm.h

## Sort()

**注意：经测试，比较函数必须写在全局函数里**

```c++
struct stu{
    int id;
    int grade;
    stu(int a=0,int b=0):id(a),grade(b){}//这么初始化很方便 但是参数一定别忘记赋初值！！！！！！！！！！
};//比较函数，对结构体进行排序 
bool cmp(stu s1,stu s2){
    if(s1.grade!=s2.grade)
        return s1.grade>s2.grade;//大的放前面
    else
        return s1.id<s2.id;//成绩一样学号小的在前
}
sort(stu,stu+number,cmp);
//sort应该是在#include<algorithm>中
```

```c++
#include<algorithm>
bool sortApple(struct apple a, struct apple b){
        return a.y < b.y; //升序排列
}
sort(vt.begin(), vt.end(), sortApple);
```

然后如果是基本类型假如是int,第三个参数可以使用系统自带的`less<int>()`或者`greater<int>()`

然后说说sort的前两个参数: 第一个是数组基地址，第二个是长度+1。

如对a[0..i]排序需要传入sort(a,a+i+1)才行。

## unique

可以提出所有连续的数并缩减到一个.

```cpp
#include<iostream>
#include<algorithm>//unique in <algorithm>
using namespace std;
int main(){
    int ints[]={1,1,1,1,2,2,2,3,5,5,10};
    unique(ints,ints+11);
    for(int i=0;i<5;i++)cout<<ints[i]<<' ';
}
```

最后输出:`1 2 3 5 10`

# 其他

- `void func(char * arr, int x)` 你在定义的这个函数里 写 `x++` 这种句子。会报错? x是个形参，怎么能 变来变去呢？

  但是我觉得应该可以变啊。我得去试试再。

- cout<<oct<<x<<dec<<x<<hex<<x<<endl; //oct、dec、hex类似格式控制符，控制其后的变量

- if里定义的变量不能在if外使用。

- 枚举类型成员都是整型变量。可以为负。不设初值就是上一个变量+1。`enum a {sum=9,mon=-1,tue};` 打印tue的值就是0.

- `cin`怎么结束输入

  Mac下是`ctrl + D` Win 下是 `ctrl + Z`


## #ifdef和#endif

选择性编译

```c++
#include<iostream>  
#include<cstdio>  
    
#define DEBUG  //至于这个DEBUG的名字，可以随心定义 如果注释掉这一句，下面的输出语句则不会编译！
    
using namespace std;  
int main(){  
#ifdef DEBUG  //如果你前面改掉了DEBUG的名字，这里记得要改
    cout<<"Hello World"<<endl;  
#endif  
    return 0;  
}  
```

