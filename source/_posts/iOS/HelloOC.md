---
title: HelloOC
date: 2018-09-05 11:17:28
categories: iOS
tags: Obj-C
---

Hello?

🙂🙂🙂

😌😌😌

🙁🙁🙁

<!---more--->

# Notes

- `#import <...>`表示包含系统自带的文件，`#import "..."`表示包含开发人员自己创建的文件

# Basics

## Functions

```objective-c
- (return_type) method_name:( argumentType1 )argumentName1 
joiningArgument2:( argumentType2 )argumentName2 ... 
joiningArgumentn:( argumentTypen )argumentNamen {
   body of the function
}
```

## Interface and Implementation

A interface file `MyClass.h`

```objc
@interface MyClass:NSObject { 
   // class variable declared here
}
// class properties declared here
// class methods and instance methods declared here
@end
```

A implementation file `MyClass.m`

```objc
@implementation MyClass
   // class methods defined here
@end
```

## Object Creation

```objc
MyClass  *objectName = [[MyClass alloc]init] ;
```

## Methods

Method is declared in Objective C as follows −

```objc
-(returnType)methodName:(typeName) variable1 :(typeName)variable2;
```

An example is shown below.

```objc
-(void)calculateAreaForRectangleWithLength:(CGfloat)length 
andBreadth:(CGfloat)breadth;
```

其中 **andBreadth** 就是为了方便对函数进行阅读的可选字段

```objc
[self calculateAreaForRectangleWithLength:30 andBreadth:20];
```

### Class Methods

类方法不需要创建类对象可被直接访问。

没有任何变量和关联对象。ex:

```objc
+(void)simpleClassMethod;
```

假设属于MyClass类。可以直接这么访问：

```objc
[MyClass simpleClassMethod];
```

### Instance Methods

Instance methods can be accessed only after creating an object for the class. Memory is allocated to the instance variables. An example instance method is shown below.

```
-(void)simpleInstanceMethod; 
```

It can be accessed after creating an object for the class as follows −

```objc
MyClass  *objectName = [[MyClass alloc]init] ;
[objectName simpleInstanceMethod];
```

## Important Data Types in Objective C

| Sr.No. | Data Type                                                    |
| ------ | ------------------------------------------------------------ |
| 1      | **NSString**It is used for representing a string.            |
| 2      | **CGfloat**It is used for representing a floating point value (normal float is also allowed but it's better to use CGfloat). |
| 3      | **NSInteger**It is used for representing integer.            |
| 4      | **BOOL**It is used for representing Boolean (YES or NO are BOOL types allowed).j |

## Printing Logs

NSLog - used for printing a statement. It will be printed in the device logs and debug console in release and debug modes respectively. For example,

```
NSlog(@"");
```

## Control Structures

Most of the control structures are same as in C and C++, except for a few additions like for in statement.

## Properties

For an external class to access the class, variable properties are used. For example,

```
@property(nonatomic , strong) NSString *myString;
```

### Accessing Properties

You can use dot operator to access properties. To access the above property, we will do the following.

```
self.myString = @"Test";
```

You can also use the set method as follows −

```
[self setMyString:@"Test"];
```

## Categories

Categories are used to add methods to the existing classes. By this way, we can add method to classes for which we don't have even implementation files where the actual class is defined. A sample category for our class is as follows −

```objc
@interface MyClass(customAdditions)
- (void)sampleCategoryMethod;
@end

@implementation MyClass(categoryAdditions)

-(void)sampleCategoryMethod {
   NSLog(@"Just a test category");
}
```

## Arrays

NSMutableArray and NSArray are the array classes used in objective C. As the name suggests, the former is mutable and the latter is immutable. An example is shown below.

```objc
NSMutableArray *aMutableArray = [[NSMutableArray alloc]init];
[anArray addObject:@"firstobject"];
NSArray *aImmutableArray = [[NSArray alloc]
initWithObjects:@"firstObject",nil];
```

## Dictionary

NSMutableDictionary and NSDictionary are the dictionary classes used in objective C. As the name suggests, the former is mutable and the latter is immutable. An example is shown below.

```objc
NSMutableDictionary *aMutableDictionary = [[NSMutableArray alloc]init];
[aMutableDictionary setObject:@"firstobject" forKey:@"aKey"];
NSDictionary*aImmutableDictionary= [[NSDictionary alloc]initWithObjects:[NSArray arrayWithObjects:
@"firstObject",nil] forKeys:[ NSArray arrayWithObjects:@"aKey"]];
```

这文章不错

https://www.cnblogs.com/lucan727/p/3883666.html

# Delegates

## EX.

假设对象A唤起对象B完成一个动作。一旦完成A会知道并作出相应动作。这就是代理完成的。其中：

- A是B的代理对象
- B将有A的参考
- A会执行B的代理方法
- B会用代理方法给A通知

# 成员变量的封装

二、OC中成员变量的命名规范以及注意事项

1、命名规范--.成员变量都以下划线“_”开头

　　1）为了跟get方法的名称区分开

　　2）一看到下划线开头的变量，肯定是成员变量

2、注意事项--以后的成员变量最好不要写@public，因为@public修饰的成员变量可以被别人乱改

```objective-c
/*
成员变量的命名规范
*/

#import <Foundation/Foundation.h>

// 声明
@interface Person : NSObject
{
    // 成员变量都以下划线 _ 开头
    // 1.可以跟get方法的名称区分开
    // 2.一看到下划线开头的变量，肯定是成员变量
    int _age;
}

- (void) setAge:(int)newAge;

- (int) age;

@end

// 实现
@implementation Person

- (void) setAge:(int)newAge
{
    _age = newAge;
}

- (int) age
{
    return _age;
}

@end

int main()
{
    Person *p = [Person new];
    [p setAge:20];
    
    int age2 = [p age];
    
    NSLog(@"年龄是%i", age2);
    
    return 0;
}
```

# 类方法和对象方法

先说一下，类里的才叫方法。外面的那叫函数。

一、OC中的对象方法

　　1.**以减号“-”开头**

　　2.只能让对象调用，没有对象，这个方法根本不可能被执行

　　3.对象方法能访问实例变量（也就是成员变量）

二、OC中的类方法

　　1.**以加号“+”开头**

　　2.只能用类名调用，对象不能调用

　　3.类方法中不能访问实例变量（也就是成员变量）

　　4.适用场合：当不需要访问成员变量的时候，尽量用类方法

**值得注意的是类方法和对象方法可以同名，但是慎用啊！**

# 类的description方法

```objective-c
#import <Foundation/Foundation.h>

// Person的声明
@interface Person : NSObject
{
    int _age;
}

- (void) setAge:(int)age;
- (int) age;

@end

// Person的实现
@implementation Person

- (void) setAge:(int)age
{
    _age = age;
}

- (int) age
{
    return _age;
}

//重写父类-description方法，利用NSString类的类方法stringWithFormat方法拼接字符串
//使得重写的-description方法返回自己想要的内容
- (NSString *) description
{
    return [NSString stringWithFormat:@"age=%d", _age];
}

@end


int main()
{
    Person *p = [Person new];
    [p setAge:29];
    
    // 输出所有的OC对象都用%@
    // 默认情况下对象的输出信息：<Person: 0x7fedc9c09720>
    // 类名 + 对象的内存地址
    
    // 给指针变量p所指向的对象发送一条-description消息
    // 会调用对象的-description方法，并且把-description方法返回的OC字符串输出到屏幕上
    NSLog(@"Person对象：%@", p);
    /*
    // 指针变量p的地址
    NSLog(@"指针变量p的地址：%p", &p);
    // 对象的地址
    NSLog(@"这个Person对象的地址：%p", p);
     */
    return 0;
}
```



##  @property

还记得我们之前定义属性的时候，在{...}中进行定义，而且定义完之后还有可能需要实现get/set方法，这里我们直接使用@property关键字进行定义：

@property NSString *userName;
这样定义完之后，我们就可以使用这个属性了：
这样定义的方式之后，这个属性就会自动有set/get方法了


第一步生成_userName属性

第二步为_userName属性自动生成set/get方法

这样定义是不是比以前方便多了

下面再来看一下他还有三个值可以设置：

```objc
@property(atomic,retain,readwrite) Dog *dog;
```


1、第一个位置的值：

`atomic`:线程保护的，默认

`nonatomic`:线程不保护的

2、第二个位置的值：

`assign`:直接赋值，默认

`retain`:保留对象,内部会自动调用retain方法，引用计数+1

`copy`:拷贝对象

3、第三个位置的值：

`readwrite`:生成get/set方法，默认

`readonly`:只生成get方法

因为我们使用@property定义属性之后，如果我们想修改这个属性的名称(不想让它是_开头的)，就可以使用@synthesize关键字来对属性名称进行修改

```objc
@synthesize userName = $userName;
```

# [Objective-C中NSString与int和float的相互转换](https://www.cnblogs.com/davidgu/p/5304981.html)

```objective-c
NSString *tempA = @"123";

NSString *tempB = @"456";

 

1，字符串拼接

 NSString *newString = [NSString stringWithFormat:@"%@%@",tempA,tempB];

 

2，字符转int

int intString = [newString intValue];

 

3，int转字符

NSString *stringInt = [NSString stringWithFormat:@"%d",intString];

 

4，字符转float

 float floatString = [newString floatValue];

 

5，float转字符

NSString *stringFloat = [NSString stringWithFormat:@"%f",intString];

 

四舍五入问题

 

-(NSString *)notRounding:(float)price afterPoint:(int)position{

    NSDecimalNumberHandler* roundingBehavior = [NSDecimalNumberHandler decimalNumberHandlerWithRoundingMode:NSRoundDown scale:position raiseOnExactness:NO raiseOnOverflow:NO raiseOnUnderflow:NO raiseOnDivideByZero:NO];

    NSDecimalNumber *ouncesDecimal;

    NSDecimalNumber *roundedOunces;

    

    ouncesDecimal = [[NSDecimalNumber alloc] initWithFloat:price];

    roundedOunces = [ouncesDecimal decimalNumberByRoundingAccordingToBehavior:roundingBehavior];

    [ouncesDecimal release];

    return [NSString stringWithFormat:@"%@",roundedOunces];

}

介绍一下参数：

price:需要处理的数字，

position：保留小数点第几位，

然后调用

 

    float s =0.126;

    NSString *sb = [self notRounding:s afterPoint:2];

    NSLog(@"sb = %@",sb);

输出结果为：sb = 0.12

 

接下来介绍NSDecimalNumberHandler初始化时的关键参数：decimalNumberHandlerWithRoundingMode：NSRoundDown，

NSRoundDown代表的就是 只舍不入。

scale的参数position代表保留小数点后几位。
```

