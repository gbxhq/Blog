- json里的数字会被优先解析成 float

```golang
jsonData := `{
        "stringKey": "Hello, world",
        "intKey": 42,
        "floatKey": 3.14159
    }`

    var data map[string]interface{}
    if err := json.Unmarshal([]byte(jsonData), &data); err != nil {
        fmt.Println("JSON 解析错误:", err)
        return
    }

    fmt.Println("stringKey:", data["stringKey"].(string))
    fmt.Println("intKey:", data["intKey"].(int))
    fmt.Println("floatKey:", data["floatKey"].(float64))
```

42 不能被断言成 int，也会被断言成 float

- 实现接口到底加不加指针

```golang
type Person interface {
    Say()
}


type A struct{}
type B struct{}


func (x A) Say(){}
func (x *B) Say(){}


func Test(x Person) {}
```

在这里，A 和B 都实现了Person 接口，但是实际上你可以理解为。结构体方法也是有一个隐含参数的。其中 A 的 Say方法里就隐含了一个形参 A，B则是隐含了B的指针。

也就是说，其实 A 实现了 person 接口，但是对于 B 是 B 的指针实现了这个接口。

于是对于 Test 方法，可以传入 `A和*A`，但是对只能传入 `*B`，因为 B 是没有实现这个接口的。
