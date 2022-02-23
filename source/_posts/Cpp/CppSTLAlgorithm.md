---
title: C++STL算法相关
date: 2019-07-23 15:06:49
categories: cpp
tags: [cpp,Note]
---



<!---more--->

算法看不见Containers，对其一无所知。算法的提问，由迭代器Iterators来回答。

所以Iterators必须能够回答算法的所有提问（记得之前看过的5大Traits）。

如果算法问到了迭代器不会的，编译到那一行，报错。

# 迭代器的分类

```cpp
struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};
struct output_iterator_tag {};
```

除了output,其余四个struct层层继承。

其中input和output这两种类型分别对应的是istream和ostream。

而STL容器用的都是其余三种。（单向、双向、可跳跃）

-   typeid

    ```cpp
    #inclde<typeinfo>
    template <typename I>
    void display_category(I itr){
        cout<<tpyeid(itr).name();
    }
    ```

29 **分类对算法的影响** 这节课还是很重要的。

计算distance时

`input`: 从头走到尾  `random`的则可以`用last-first`

# 30 Example

```cpp
struct myClass{
    int operator(int x,int y){ return x+y; }
}myObj;
```

仿函数。myObj就可以当函数参数传入。

-   sort

```cpp
sort(vt.rbegin(),vt.rend());//这么就是从大到小
```

sort必须传入random，所以list\forward_list就不能传入sort()。list补不能跳着走.list 有自己的sort()方法。

# functor

STL规定每个Adaptable Function都应挑选一个适当者继承之。

有两个可选的(其实就是做了`typedef`)：

```cpp
template <class Arg,class Result>
sturct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};
template <class Arg1,clss Arg2,class Result>
sturct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
}
```

子类继承上面的，大小不会增加。只是继承了typedef。

# Adapter

-   容器适配器：stack\queue 里面都有个deque

-   函数适配器

-   binder2nd()

    绑定第二实参

-   

