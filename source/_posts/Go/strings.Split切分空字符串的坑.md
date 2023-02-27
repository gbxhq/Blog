---
title: strings.Split切分空字符串的坑
date: 2020-01-19
categories: Go
tags: [Go,Note]
---

空字符串，使用`strings.Split`，切出来的数组长度为1，但是数组里没东西

```go
func main(){
  s:=""
  sArray := strings.Split(s, ",")
  fmt.Printf("%v\n",sArray) //[]
  fmt.Printf("===%v---",sArray[0]) //===---
  fmt.Printf("%v\n",len(sArray)) //1
  sArray = []string{}
  fmt.Printf("%v\n",len(sArray)) //0
  fmt.Printf("===%v---",sArray[0]) //panic
}
```

