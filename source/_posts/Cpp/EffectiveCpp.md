---
title: Effective C++ 笔记
date: 2019-09-26 09:16:05
categories: cpp
tags: [cpp,Note]
---



<!---more--->

# 导读

- 除非有好理由允许构造函数被用于隐式类型转化换。否则请声明称`explicit`。the你and那newandNo。
- lhs\rhs 含义是: left/right-hand side 左/右手端 （原来如此
- `{hashTable, shared_ptr, 正则,etc}`属于`tr1`(命名空间)属于`std`

# 一.习惯C++

## 2.替换`#define`
用`const,enum,inline`
总结：
- 单纯常量，const\enum替换 #defines
- 宏，inline替换#deines

细节：
类中的`const`
- `const`成员为确保最多一份，应定义成`static`

**enum hack**
如，某些编译器不允许static整数型class常量完成in class 初值设定，可另辟蹊径：
`enum{N = 5};` 使得N成为5的另一个记号名称

## 3.const

除了`const char* const p`这种用法，请注意在const修饰STL迭代器时：

```cpp
const std:vector<int>::iterator it = vt.begin();//it作用像个 T* const
*it = 10;//No problem.
it++;//Error！
//那怎么实现不允许更改迭代器指向的内容呢？
std::vector<int>::const_iterator cIt = vt.begin();//cIt作用像个const T*
*cIt = 10;//Error!
it++;//No problem.
```

- 加`mutable`的成员变量，总是会被更改，即使在const成员函数里。

const可以作重载依据，那岂不是要为了适配，要写出两个完全一样的函数，只不过一个有const一个没有？ 如何避免代码重复呢？
```cpp
class A{
    const int func() const {
        //xxxx在此定义
        return a;
    }
    int f(){
        return
            const_cast<int> func(
            static_cast<const A&>(*this)
            );
    }
}                                                                                                                                                                   
```
真机智啊，先把this指针强转const，保证可以传入`const func()`里调用，再去const化后return！代码就不用重写了！

> 思考：能不能先写f(),然后包装成const f()呢？
> 答。别啊。const函数承诺不会改这改那，但普通的f()并不承诺。

## 4.使用前初始化

内置类型声明时初始化。
类的构造函数保证每一个成员初始化。

使用初始化列表。（在构造函数体内只能算**赋值**，初始化列表才是**初始化**）

初始化顺序：base先于derived； 

而成员变量总是以声明的次序被初始化==》声明时要考虑顺序，如表数组大小的变量要在数组前声明。

### static重要技巧

>   之前高德二面时，面试官问我，什么时候把static放在全局，什么时候把static放在函数体内。
>   本小节提到的一点可作为一个选择的重要依据!

当两个不同的代码文件，需要相互调用。如果是有一个全局变量。允许被另一个模块所“利用”。这时候会有一个问题：A想利用B里的obj：b，可是万一b此时还没有被初始化咋整呢？

解决方法就是，把b放到一个函数体内声明成static。并返回其引用。这样调用函数的同时，一定能保证b的正常初始化。

这种方法也及其类似单例模式。进一步的思考就是在多线程下的完善。

总结：请以local static对象替换non-local static对象。

# 二.ctor/dtor/=

## 5.默认的

-   编译器自动生成的ctor/dtor/operator=都是public且inline的

本节走马观花mark

## 6.阻止dtor/=

很容易，就是把dtor和operator=设为`private`呗。但是书中提供了更好的方法，就是声明一个基类：

```cpp
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
}
//然后让class A 继承它，便也阻止了A的dtor和operator=
class A：private Uncopyable{};
//其实继承方式也无需多虑。怎么继承都可以的。
```

## 7.dtor设为virtual

老生常谈。

-   不要盲目加virtual。类中有虚函数，才这么做。否则相当于徒增一个vptr的体积。

-   设计了个抽象类（不允许实例化），却没设计纯虚函数，咋整？

    答，把dtor设计成纯虚的。

## 8.别让异常逃离dtor

 可以再dtor中加`try{}catch(...){}` 但这样无法对异常做出反应。

走马观花Mark

## 9. 不在ctor/dtor中调用virt

## 10.令=返回一个ref*this

为了方便连续赋值的书写习惯

## 11. 在=中处理自我赋值

侯捷讲过，重载=时先判断一下是不是和自己相等

## 12. copy时勿忘每个成分

总结：

-   copying函数应确保复制“对象内所有成员变量”及所有base class成分。

# 三.资源管理

## 

