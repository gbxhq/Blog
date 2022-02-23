---
title: OJ刷题注意事项
date: 2019-06-06 21:18:13
categories: Algorithm
tags: 
---



<!---more--->

# Problems

本蒟蒻犯过的错

- 报错：`type does not provide a call operator`

  解决：给报错那句的变量换个名字吧。冲突了~

- [ ] 初始化一个map，我还没往里存东西。它的end()是什么值？

- 防止下标溢出要先判断下标。例子：

  ```c++
  //下面的循环：i++到array溢出时，循环无法进行，最终卡死在这里。
  while (array[i]<target && i<n)
              i++;
  //正解：把控制i溢出的表达式i<n放在前面
  while (i<n && array[i]<target )
              i++;
  ```

- 

- 传入空vector情况不考虑

  `m = array[0].size();`这么写如果传入空数组直接溢出

- 二维数组考虑传入一个元素的情况，即传入形如[[x,x,x,x]]这种

- 循环读输入用：`while(cin>>x)` 

  或 `while(scanf()!=EOF)`
  
  一行一行地读：
  
  ```c++
  string line;
  while(getline(cin,line));
  ```
  
  在程序中`scanf（"%d",%i）` 或`cin>>i` 时输入Ctrl+Z，会返回0，所以可以作为循环条件。
  
- 判断素数：i*i<=n 忘记写=

  - [ ] 线性筛法

- 多个if后加一个else，else只会和前一个if匹配。

- 这个情况不好归纳，直接看例子：

  ```c++
  if(a<=0||b<=0||c<=0) //规则1
  {
      a=0;b=0;c=0;
  }
  if(a>20||b>20||c>20) //规则2
  {
      a=20;b=20;c=20;
  }
  ```

  这时候如果输入(-1,21,-1)，符合规则1和2. 要考虑这种情况！防止规则2把规则1覆盖，尽量在第二个`if`前加`else`!

- 刚声明一个vector。没指定大小。是不能用vt[0]=1赋值的==》越界

- If(xxx) return;要慎重。是return就等于是break了。而不是continue;

- Vector效率真不行

-  **reference to non-static member function must be called**

    报这个错是因为sort(a,a+n,cmp)时，传的cmp里表面看2个参数，实际是3个参数（this指针），造成了参数不匹配。把cmp函数设成static即可（不含this指针了）

# 知识点

- 一位一位的读01可以用`scanf %1d`

- 范围问题

- ```c++
  unsigned   int
  0～4294967295   (10位数，4e9)
  
  int
  -2147483648～2147483647  (10位数，2e9   2^31 - 1)   
  
  long long
  -9223372036854775808～9223372036854775807  (19位数， 9e18 ) 2^63 - 1
  
  unsigned long long
  0～18446744073709551615  (20位数，1e19)  2^64 - 1
  ```

## 取模运算法则

模运算与基本四则运算有些相似，但是除法例外。其规则如下：

(a + b) % p = (a % p + b % p) % p
(a - b) % p = (a % p - b % p) % p
(a * b) % p = (a % p * b % p) % p
a ^ b % p = ((a % p)^b) % p
结合律：

((a+b) % p + c) % p = (a + (b+c) % p) % p
((a*b) % p * c)% p = (a * (b*c) % p) % p

交换律：

(a + b) % p = (b+a) % p
(a * b) % p = (b * a) % p

分配律：

(a+b) % p = ( a % p + b % p ) % p
((a +b)% p * c) % p = ((a * c) % p + (b * c) % p) % p

重要定理

若a≡b (% p)，则对于任意的c，都有(a + c) ≡ (b + c) (%p)；
若a≡b (% p)，则对于任意的c，都有(a * c) ≡ (b * c) (%p)；
若a≡b (% p)，c≡d (% p)，则

(a + c) ≡ (b + d) (%p)，(a - c) ≡ (b - d) (%p)，
(a * c) ≡ (b * d) (%p)，(a / c) ≡ (b / d) (%p)；

## 附：OJ 使用技巧

1. OJ 首页上有 OJ 使用手册（guide）、视频教程（video guide）、本编程作业说明（PA handbook）。
2. 在黑盒测试结果页面，有解释评测结果的含义的链接 http://dsa.cs.tsinghua.edu.cn/oj/static/submission_result_explanation.html 。
3. Runtime Error 的 signal 同样反映了某种信息，可以查阅相关资料了解0各个 signal 的意义。参考 http://dsa.cs.tsinghua.edu.cn/oj/static/unix_signal.html 。
4. 几种主要的读入数据方法，大多数情况下性能是 fread > getchar > scanf > cin 的顺序。
5. OJ 上的编译器采用的是 gcc（g++），对于 Linux 和 Mac 用户可以无缝衔接，而如果使用 Windows 的同学希望能够在本地编译与 OJ 编译之间较快衔接的话，可以考虑使用 MinGW。
6. 评测所依赖的输出流是 stdout，而使用 stderr 的输出不会被纳入最终评测——但如果你使用 stderr 进行调试却没有在提交中移除，这将显著地拖累你程序的性能。
7. Windows 和 Linux 上换行符有 "\r\n" 跟 "\n" 的差别，你的程序最好有一定鲁棒性，能处理两种情况。
8. Linux 文件系统区分大小写，因此 `#include "foo.h"` 不能与 `Foo.h` 对应。
9. 常用的调试工具包括 gdb、MSVC debugger、室友、小黄鸭。
10. 如果不确定某一特性是否为 OJ 所支持，不妨动手试一试。

# 清华OJ上写的的有用技巧

## 附：输入输出技巧

1. 判断输入结束

   有些编程作业题并未指明测试数据的组数，此时需要自己判断输入结束。其实，根据题意正确处理输入数据也是同学们在这门课中需要练习的编程能力之一。

   处理输入的方法很简单，使用 C++ 风格的 cin，可以这样写

   ```
   int a, b, c;
   while (cin >> a >> b >> c)
   { /* blablabla */ }
   ```

   如果使用 C 风格的 scanf() 函数，则可根据其返回值做出判断，具体地可以这样写：

   ```
   int a, b, c;
   while (scanf("%d%d%d", &a, &b, &c) != EOF)
   { /* blablabla */ }
   ```

   当格式输入流读到文件末尾时会返回 EOF，于是 while 退出。

2. 过滤空白字符 有些题目是这样的输入格式：

   ```
   E 6
   M
   E 2
   M
   ```

   即字母、数字混输。如果用 getchar 或 scanf 的 %c 参数，会受到行末空白符（比如空格、换行等）的困扰。cin 到字符串、scanf 的 %s 参数都会自动过滤空白符。使用标准库的功能来过滤空白符，会使程序逻辑更清晰。示例代码：

   ```
   char buf[8];
   int x;
   while (scanf("%s", buf) != EOF) {
     switch (buf[0]) {
     case 'E':
       scanf("%d", &x);
       /* balabala */
     }
   }
   ```

3. I/O 缓存加速

   使用 cstdio 中的 setvbuf 函数，设置一个较大的 I/O 缓冲区，有时有很好的加速效果。用法示例：

   ```
   setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
   setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
   ```

   注意：一、必须在所有 I/O 操作前调用这个函数，不能在已读入一些数据后再设置缓存；二、如果设置了 I/O 缓存，控制台输入输出可能失效。

4. 重定向

   为便于反复测试及再现运行过程，可采用输出、输入重定向的方法。 你只需事先将输入数据存成文件，运行时系统会自动从中获取输入。其效果完全等同于你从（作为默认输入流的）键盘逐项输入。 类似地，你也可以指定另一文件，并使运行的结果自动存入其中。其效果完全等同于从（作为默认输出流的）屏幕截取输出结果。 重定向的好处很多：可以避免手工输入的出错，忠实可靠地重复测试；可以实现大规模数据的输入；可以完整精确地记录程序的输出，以便事后的对比分析；可以省去默认输入、输出流占用的大量时间，更加准确地测量程序的执行效率。

   1. 方法一：修改源文件，指定重定向的输入、输出文件

      例如，若希望从文件 input.txt 中获取输入，将输出保存到文件 output.txt 中，则可在主程序开头增加如下语句：

      ```
      #ifndef _OJ_
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
      #endif
      ```

      注意：如果用 C++ 风格的 cin / cout 的话，还要在前面引用头文件的部分加入 `#include <cstdio>`。

      OJ 在编译程序的时候会定义名为 `_OJ_` 的宏，所以上面这段语句会在 OJ 运行的时候被跳过。

   2. 方法二：在 IDE 中通过设置命令行，重定向输入、输出文件 以 Visual Studio 为例，可打开对应工程的“属性页”，在“配置属性”下的“调试”页，设置“命令行参数”。

      输入参数不多时，可直接键入。例如 ADD 一题，键入“100 200”即可。若其中包含特殊字符，则需以'^'引导，或者使用一对半角括号消除歧义。

      若输入参数多，且不止一行，则可将其存成一个文件。比如，可在“命令行参数”中键入:

      `< D:\test\input.txt`（注意起始字符"<"不能省略）

      为将程序的输出保存至指定文件，可在“命令行参数”中继续键入：

      `> D:\result\output.txt`（同样地，起始字符">"也不能省略）

      若不希望覆盖文件原有的内容，只需用">>"替换以上的">"，即可将每次运行的输出追加至 D:\result\output.txt。

      输入、输出的重定向可同时采用并生效。比如可在“命令行参数”中键入：

      `< D:\test\input.txt >> D:\result\output.txt`

      重定向文件的具体路径与文件名可自行选择，但若包含空格，则需使用一对半角引号消除歧义，比如：

      `< "D:\my test\input.txt" >> "D:\my result\output.txt"`

5. 帮助资料

   关于输入输出的进一步问题，可以自己查阅相关手册或资料。

   也可参考标准手册，以上输入输出方法都是 C / C++ 标准输入输出，在 manual 中都有详细介绍。

   cin：http://www.cplusplus.com/reference/iostream/cin/

   scanf：http://linux.die.net/man/3/scanf

   对比：http://www.byvoid.com/blog/fast-readfile/



## 附：一些常见逻辑错误

1. swtich 里忘记加 break，导致多个case 后的语句都被执行。

2. `int *a = new int[n]` 误写成 `int *a = new int(n)`。前者申请了 n 个 int 的空间；而后者只申请了一个 int 的空间，并初始化为 n。

3. 在函数里开了很大的数组，导致运行时栈溢出。错误示例：

   ```
   int main() {
     int a[10000000];
     return 0;
   }
   ```

   可以使用动态内存分配，避免栈溢出，例如：

   ```
   int main() {
     int *a = new int[10000000];
     delete[] a;
     return 0;
   }
   ```

4. 计算溢出。错误示例：

   ```
   int a = 1000000, b = 1000000;
   long long c = a * b;
   ```

   程序会先在 int 范围内计算 `a * b`，最后把溢出后的结果赋值给 c。正确写法是 `c = (long long)a * (long long)b`。

5. 有返回值的函数漏 return 语句。

   行为是不确定的，有的编译器会恰巧返回你想要返回的变量，而一般不会。

6. memcpy 的源地址和目标地址有重叠。



## 附：Visual Studio msvc 与 GNU gcc 的差异

1. msvc 可能会自动 include 一些头文件，gcc 编译提示函数找不到。
2. 使用 scanf 等函数会警告 `not safe(warning 4996)`，msvc 推荐使用 scanf_s ，但是这个不属于 C / C++ 标准，gcc 没有。
3. gcc 也没有 itoa（数字转换为字符串的函数）。
4. gcc 上，模板类继承模板类，two phase name lookup，调用父类函数会提示找不到，需要用 this-> 调用。
5. gcc 禁止 void main。main 函数必须 return 0，如果返回值非 0，也会被认为是运行时错误，不得分。
6. http://dsa.cs.tsinghua.edu.cn/oj/static/submission_result_explanation.html 列出了一些常见编译错误的解决方法。