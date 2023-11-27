---
title: Go 里的 byte 和 rune 对比
date: 2021-01-18
categories: Note
tags: [Go,Note]
---

为什么说**字符只是整数的特殊用例**呢？因为在 Go 中，用于表示字符的 `byte` 和 `rune` 类型都是**整型的别名**。在 Go 的源码中我们可以看到：

```
// byte is an alias for uint8 and is equivalent to uint8 in all ways. It is
// used, by convention, to distinguish byte values from 8-bit unsigned
// integer values.
type byte = uint8

// rune is an alias for int32 and is equivalent to int32 in all ways. It is
// used, by convention, to distinguish character values from integer values.
type rune = int32
```

- `byte` 是 `uint8` 的别名，长度为 1 个字节，用于表示 ASCII 字符
- `rune` 是 `int32` 的别名，长度为 4 个字节，用于表示以 UTF-8 编码的 Unicode 码点

> Tips：Unicode 从 0 开始，为每个符号指定一个编号，这叫做「码点」（code point）。

## 字符的表示

那么，如何在 Go 语言中表示字符呢？

在 Go 语言中使用**单引号包围**来表示字符，例如 `'j'`。

### byte

如果要表示 `byte` 类型的字符，可以使用 `byte` 关键字来指明字符变量的类型：

```
var byteC byte = 'j'
```

又因为 `byte` 实质上是整型 `uint8`，所以可以直接转成整型值。在格式化说明符中我们使用 `%c` 表示字符，`%d` 表示整型：

```
// 声明 byte 类型字符
var byteC byte = 'j'
fmt.Printf("字符 %c 对应的整型为 %d\n", byteC, byteC)
// Output: 字符 j 对应的整型为 106
```

### rune

与 `byte` 相同，想要声明 `rune` 类型的字符可以使用 `rune` 关键字指明：

```
var runeC rune = 'J'
```

**但如果在声明一个字符变量时没有指明类型，Go 会默认它是 `rune` 类型**：

```
runeC := 'J'
fmt.Printf("字符 %c 的类型为 %T\n", runeC, runeC)
// Output: 字符 J 的类型为 int32
```

## 为什么需要两种类型？

看到这里你可能会问了，既然都用于表示字符，为什么还需要两种类型呢？

我们知道，`byte` 占用一个字节，因此它可以用于表示 ASCII 字符。**而 UTF-8 是一种变长的编码方法，字符长度从 1 个字节到 4 个字节不等**。`byte` 显然不擅长这样的表示，就算你想要使用多个 `byte` 进行表示，你也无从知晓你要处理的 UTF-8 字符究竟占了几个字节。

因此，如果你在中文字符串上狂妄地进行截取，一定会输出乱码：

```
testString := "你好，世界"
fmt.Println(testString[:2]) // 输出乱码，因为截取了前两个字节
fmt.Println(testString[:3]) // 输出「你」，一个中文字符由三个字节表示
```

此时就需要 `rune` 的帮助了。利用 `[]rune()` 将字符串转为 Unicode 码点再进行截取，这样就无需考虑字符串中含有 UTF-8 字符的情况了：

```
testString := "你好，世界"
fmt.Println(string([]rune(testString)[:2])) // 输出：「你好」
```

> Tips：Unicode 和 ASCII 一样，是一种字符集，UTF-8 则是一种编码方式。

## 遍历字符串

字符串遍历有两种方式，一种是下标遍历，一种是使用 `range`。

### 下标遍历

由于在 Go 语言中，字符串以 UTF-8 编码方式存储，使用 `len()` 函数获取字符串长度时，获取到的是该 UTF-8 编码字符串的字节长度，**通过下标索引字符串将会产生一个字节**。因此，如果字符串中含有 UTF-8 编码字符，就会出现乱码：

```
testString := "Hello，世界"

for i := 0; i < len(testString); i++ {
    c := testString[i]
    fmt.Printf("%c 的类型是 %s\n", c, reflect.TypeOf(c))
}

/* Output:
H 的类型是 uint8（ASCII 字符返回正常）
e 的类型是 uint8
l 的类型是 uint8
l 的类型是 uint8
o 的类型是 uint8
ï 的类型是 uint8（从这里开始出现了奇怪的乱码）
¼ 的类型是 uint8
 的类型是 uint8
ä 的类型是 uint8
¸ 的类型是 uint8
 的类型是 uint8
ç 的类型是 uint8
 的类型是 uint8
 的类型是 uint8
*/
```

### range

`range` 遍历则会得到 `rune` 类型的字符：

```
testString := "Hello，世界"

for _, c := range testString {
    fmt.Printf("%c 的类型是 %s\n", c, reflect.TypeOf(c))
}

/* Output:
H 的类型是 int32
e 的类型是 int32
l 的类型是 int32
l 的类型是 int32
o 的类型是 int32
， 的类型是 int32
世 的类型是 int32
界 的类型是 int32
*/
```

## 总结

- Go 语言中没有字符的概念，**一个字符就是一堆字节**，它可能是单个字节（ASCII 字符集），也有可能是多个字节（Unicode 字符集）
- `byte` 是 `uint8` 的别名，长度为 1 个字节，用于表示 ASCII 字符
- `rune` 则是 `int32` 的别名，长度为 4 个字节，用于表示以 UTF-8 编码的 Unicode 码点
- 字符串的截取是以字节为单位的
- 使用下标索引字符串会产生字节
- 想要遍历 `rune` 类型的字符则使用 `range` 方法进行遍历