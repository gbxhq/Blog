---
title: C++ STL容器相关
date: 2019-07-18 09:25:49
categories: cpp
tags: [cpp,Note]
---



<!---more--->

-   容器分类

    顺序容器：Array（两端封闭）、Vector（尾开放）、Deque（两端开放）、List（非连续空间）

    关联容器：Set/Multiset Map/Multimap：红黑树

    Unorded Map/Set

前面一直在铺垫。开始终于到正片了。

# 11分配器

`operator new`，先调`allocator<T>`,最终都是调用`malloc`，而malloc会根据操作系统去调用操作系统的接口。

delete调用的就是deallocate。

但其实`allocate`开销很大。因为我们自己的数据很小。但却要开辟很多“必要的”空间。

G2.9使用了一个更好的分配器 `alloc`,其源代码会在内存课里讲。

4.9中改名pool_alloc，且不再使用。不知道为啥。

# 顺序容器

## 12

一个list的大小。G2.9中是4，G4.9中是8.这个大小是容器控制本身用的。和容器里有100个元素没关系。

## 13~14 list

先讲讲最有代表性的链表。

iteraotr里重载了++, ++(int), `*()`, ->()这些东西。所以才让我们用起来，可以前后移动、可以 `*` 取数据。

```cpp
T& operator*() const {
    return (*node).data;
}
T* operator->() const {
    return &(operator*());
}
```

![](https://0pic.oss-cn-beijing.aliyuncs.com/20190722103610.png)

`list.end()`应该是最后一个元素的下一个。一个空白节点。

## 15 trait

为了解决“某个”算法，iterator必须提供的5种associated types

```cpp
template<typename _Tp>
struct _List_iterator
{
    typedef std::bidirectional_iterator_tag iterator_category;//区分双向
    typedef _Tp value_type;//存的类型
    typedef _Tp* pointer;//标准库从不用
    typedef _Tp& reference;//标准库从不用
    typedef ptrdiff_t difference_type;//距离
    //这个ptrdiff_t是标准库中定义的一个unsigned long（如果还是存不下头和尾的距离，那就失效咯。）
}
```

有了上面的typedef, 算法中会直接这么调用：

```cpp
temelate<typename I>
inline void algorithm(I a,I b){
...
    I::iterator_category
    I::value_type
...
}
```

但如果上面的算法传入的不是一个iterator而是一个普通指针，直接这么“回答”肯定出错了。

Iterator Trait的出现是用以分离class iterators 和 non-class iterators

```cpp
template <class I>
struct iterator_traits{
	typedef typename I::value_type value_type;  
};
template <class T>
struct iterator_traits<T*>{//如果传入的一个指针
	typedef T value_type;  
};
template <class T>
struct iterator_traits<const T*>{
	typedef T value_type;  
};
```

有了traits后，算法调用就可以这样：

```cpp
template <typename I,...>
void algorithm(...){
	typename iterator_traits<I>::value_type v1;
}
```

## 16 vector

扩充不能原地扩充。要找到足够的空间(2倍)后，把原来的vector搬过去。

## 17 Array

## 18 Deque

## 19 Deque如何模拟连续空间

迭代器会对减号做operator重载，所以可以用减号得到`.size()`

# 关联容器

## 20R-B tree

我们**不应**使用rb_tree的iterators改变元素值，会破坏排列。

rb_tree提供两种insertion操作：`insert_unique()`和`insert_equal()` , 分别用于key是否可相同的情况。

看源码（G2.9）:

```cpp
template <class Key,
          class Value,
          class KeyOfValue,
          class Compare,
          class Alloc = alloc>//传五个模板参数
class rb_tree{
protected:
    typedef __rb_tree_node<Value> rb_tree_node;
    ...
public:
    typedef rb_tree_node* link_type;
    ...
protected:
    //仅有三条数据
    size_type node_count; //节点数量
    link_type header; //头结点(可以方便很多计算)
    Compare key_compare; //key的大小比较规则；function object
};
```

关键数据。node_count占4个字节，header是个指针4个字节，key_compare是个仿函数，大小是0（其并没有数据），但大小为0的class编译器编译后大小为1 。所以总大小为9，9要对齐4，所以一个rb_tree大小为12。

下面我们建一个rb_tree对象试试:

```cpp
rb_tree<int,
        int,
        identity<int>,
        less<int>>
myTree;
```

其中identity是G2.9中的一个函数，并不在其他C库中:

```cpp
template <class T>
struct identity : public unary_funciton<T,T>{
    const T& operator()(const T& x)const {return x;}
};
```

传x进去就返回一个x, 就是说key就是value。其实G2.9中的set这个参数就是传入的identity。

## set

刚刚说了，set初始化要传的是: <int,compare, alloc> 第一个int传进去，调用rb_tree时其实是传了两个int。

而identity就是默认的也改不了。其他版的C++中没有这个函数，但也用了功能一样的函数来传入。

set中的iterator这么定义：

```cpp
typedef typename rep_type::const_iterator iterator; 
```

把一个const_iterator命名成了iterator，这就限定了这个iterator是不能乱改的。以保证其key不允许改变。避免使用者改了，破坏了rb_tree结构。

set中有个一rb_tree，所有的事都由它来完成。

## map

看map，我猜和set不一样的地方应该在于key和value不同，identity肯定不能用了，下面去看看是不是呢？

果然，identity的地方传入的是一个叫`select1st<value_type>`的东西。

-   但是前两个参数和我想的不一样。map中前两个传入的是key和value的类型，但这两个传入的类型，在构建rb_tree时并没有直接用。key直接传入了，但rb_tree的第二个参数传入了一个`pair<const Key, T>`。把key和value组合成pair传入rb_tree当value，而且pair中的Key是const类型来保证Key是不能被改变。

-   而rb_tree的第三个参数，`select1st<value_type>`，就是取出第二个参数（一对pair）的第一个做key。不多解释了！很通明了。当然这个`select1st<value_type>`是GC特有的一个函数，其他版本的库也有类似实现。

-   关于map的`[]`重载：

    如果找不到，会返回一个最适合插入的iterator。具体还有疑惑。

# 23HashTable

rehash: 如果元素个数比篮子总个数多。篮子个数增加大致2倍

（存在个数序列）{53,97,193,,389,769···}

完全是经验。没有科学依据。

看源码.

```cpp
template <class Value, class Key,
          class HashFcn,//计算位置
          class ExtractKey,//从元素中取Key
          class EuqalKey,//如何比较Key
          class Alloc=alloc>
```

基本上类似rb_tree. HashFcn是它独有的。 ExtractKey 相当于KeyOfValue, EuqalKey 相当于 Compare.

```cpp
class hashtable{
public:
    typedef HashFcn hasher;
    typedef EuqalKey key_equal;
    typedef size_t size_type;

private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef __hashtable_node<Value> node;
    
    vector<node*,Alloc> buckets;//最外层存篮子的是个vector，这也是hashtable对外的情况
    size_type num_elements;
public:
    size_type bucket_count() const { return buckets.size(); }
};
```

下面跟着的三个typedef不管了。

看private的数据：hash就是hashFunction, equals是比较Key的方法，get_key就是拿Key。对应我上面模板参数里注释的三条。

然后是一个vector定义的篮子和元素总个数。

下面计算一下hashtable大小:

三个仿函数，本来没数据，但说过多次了，没有0字节的，三个都是1字节。

然后是一个vector，vector里有三个指针（start,finish,storage)，大小12.  size_type大小4. 

12+4+3=19==》4的倍数20.

然后看一下篮子里的节点node源码:

```cpp
template<class Value>
struct __hashtable_node {
	__hashtable_node* next;
	Value val;
};
```

明显看出，就是个链表。里面一个Val一个next指针。

然后看一下它的迭代器:

```cpp
template <class Value, class Key,
          class HashFcn,//计算位置
          class ExtractKey,//从元素中取Key
          class EuqalKey,//如何比较Key
          class Alloc=alloc>
struct __hashtable_iterator {
...
    node* cur;
    hashtable* ht;
};
```

两个指针一个用于在node里移动，一个用于node移动到头后返回找下一个Node.

`hash`没有提供`std::string`

## unordered

C++11之后，hash_map/set更名为unordered map/set