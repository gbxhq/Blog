---
title: 洛谷5-高精
date: 2019-07-03 23:06:15
categories: Algorithm
tags: [luoguOJ,Cpp,Algorithm]
mathjax: true
---



<!---more--->

**Note**

-   用int数组时，我习惯于先把数字相乘存起来，再统一计算进位。

    但是用char数组存数时，问题来了，当遇到大数，99*99时，不进位则会在一位存入81+81=162。要知道char只能表示128的数啊。最终结果错误。

# 洛谷高精题

## **P1601** A+B Problem

注意：0+0的情况！

最后倒序输出的时候。如果maxLen一直减到了-1.再让maxLen归零。

- 输入str转int存入时记得`-'0'`

关键代码：

```cpp
void sum(int bit){
    //传入a和b的最大位数
    int temp=0,i=0;
    for (; i < bit; ++i) {
        ans[i]=a[i]+b[i]+temp;
        temp=ans[i]/10;
        ans[i]%=10;
    }
    ans[i]=temp;//别忘了最后可能还有个进位      
}
```



## P2142 高精度减法

注意，目前我做的高精度加减法，都不涉及负数的输入。这一点也是以后需要加强的。

关键代码：注意传入时a已经是确保大于b的了（利用string比较）

```cpp
void sub(int *a,int *b,int maxL){
    int temp=0;
    for (int i = 0; i < maxL; ++i) {
        c[i]=a[i]-b[i]-temp;
        if(c[i]>=0)
            temp=0;
        if(c[i]<0)
        {
            c[i]+=10;
            temp=1;
        }
    }
}
```

## P1303 A*B Problem

关键代码：(注意两个是`+=`的地方即可)

```cpp
void multiply(int n,int m){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i+j] += a[i]*b[j];
        }
    }
    for (int k = 0; k < m+n; ++k) {
            ans[k+1] += ans[k]/10;
            ans[k] %= 10;
    }
}
```

## [**P1255** 数楼梯](https://www.luogu.org/problemnew/show/P1255)

- 数据证明，输入5000时（第5000个斐波那契数）为1400多位。故开数组大小为1500即够用。
- 不要忘记输入0的情况特判。

## [**P1604** B进制星球](https://www.luogu.org/problemnew/show/P1604)

- 管它多少进制，先用int数组存啊。用char数组做运算太费事。大于10进制的每一位存它的值就行啊。输出的时候再转成ABC
- 开始没过，原因原来是` cout<<(char)('A'+ans[i]-10);`这种输出如果不强制转char会输出int！

# 高精度模板

```cpp
#define MAX_L 205 //最大长度，可以修改
class bign
{
public:
    int len, s[MAX_L];//数的长度，记录数组
//构造函数
    bign();
    bign(const char*);
    bign(int);
    bool sign;//符号 1正数 0负数
    string toStr() const;//转化为字符串，主要是便于输出
    friend istream& operator>>(istream &,bign &);//重载输入流
    friend ostream& operator<<(ostream &,bign &);//重载输出流
//重载复制
    bign operator=(const char*);
    bign operator=(int);
    bign operator=(const string);
//重载各种比较
    bool operator>(const bign &) const;
    bool operator>=(const bign &) const;
    bool operator<(const bign &) const;
    bool operator<=(const bign &) const;
    bool operator==(const bign &) const;
    bool operator!=(const bign &) const;
//重载四则运算
    bign operator+(const bign &) const;
    bign operator++();
    bign operator++(int);
    bign operator+=(const bign&);
    bign operator-(const bign &) const;
    bign operator--();
    bign operator--(int);
    bign operator-=(const bign&);
    bign operator*(const bign &)const;
    bign operator*(const int num)const;
    bign operator*=(const bign&);
    bign operator/(const bign&)const;
    bign operator/=(const bign&);
//四则运算的衍生运算
    bign operator%(const bign&)const;//取模（余数）
    bign factorial()const;//阶乘
    bign Sqrt()const;//整数开根（向下取整）
    bign pow(const bign&)const;//次方
//一些乱乱的函数
    void clean();
    ~bign();
};
#define max(a,b) a>b ? a : b
#define min(a,b) a<b ? a : b

bign::bign()
{
    memset(s, 0, sizeof(s));
    len = 1;
    sign = 1;
}

bign::bign(const char *num)
{
    *this = num;
}

bign::bign(int num)
{
    *this = num;
}

string bign::toStr() const
{
    string res;
    res = "";
    for (int i = 0; i < len; i++)
        res = (char)(s[i] + '0') + res;
    if (res == "")
        res = "0";
    if (!sign&&res != "0")
        res = "-" + res;
    return res;
}

istream &operator>>(istream &in, bign &num)
{
    string str;
    in>>str;
    num=str;
    return in;
}

ostream &operator<<(ostream &out, bign &num)
{
    out<<num.toStr();
    return out;
}

bign bign::operator=(const char *num)
{

    memset(s, 0, sizeof(s));
    char a[MAX_L] = "";
    if (num[0] != '-')
        strcpy(a, num);
    else
        for (int i = 1; i < strlen(num); i++)
            a[i - 1] = num[i];
    sign = !(num[0] == '-');
    len = strlen(a);
    for (int i = 0; i < strlen(a); i++)
        s[i] = a[len - i - 1] - 48;
    return *this;
}

bign bign::operator=(int num)
{
    char temp[MAX_L];
    sprintf(temp, "%d", num);
    *this = temp;
    return *this;
}

bign bign::operator=(const string num)
{
    const char *tmp;
    tmp = num.c_str();
    *this = tmp;
    return *this;
}

bool bign::operator<(const bign &num) const
{
    if (sign^num.sign)
        return num.sign;
    if (len != num.len)
        return len < num.len;
    for (int i = len - 1; i >= 0; i--)
        if (s[i] != num.s[i])
            return sign ? (s[i] < num.s[i]) : (!(s[i] < num.s[i]));
    return !sign;
}

bool bign::operator>(const bign&num)const
{
    return num < *this;
}

bool bign::operator<=(const bign&num)const
{
    return !(*this>num);
}

bool bign::operator>=(const bign&num)const
{
    return !(*this<num);
}

bool bign::operator!=(const bign&num)const
{
    return *this > num || *this < num;
}

bool bign::operator==(const bign&num)const
{
    return !(num != *this);
}

bign bign::operator+(const bign &num) const
{
    if (sign^num.sign)
    {
        bign tmp = sign ? num : *this;
        tmp.sign = 1;
        return sign ? *this - tmp : num - tmp;
    }
    bign result;
    result.len = 0;
    int temp = 0;
    for (int i = 0; temp || i < (max(len, num.len)); i++)
    {
        int t = s[i] + num.s[i] + temp;
        result.s[result.len++] = t % 10;
        temp = t / 10;
    }
    result.sign = sign;
    return result;
}

bign bign::operator++()
{
    *this = *this + 1;
    return *this;
}

bign bign::operator++(int)
{
    bign old = *this;
    ++(*this);
    return old;
}

bign bign::operator+=(const bign &num)
{
    *this = *this + num;
    return *this;
}

bign bign::operator-(const bign &num) const
{
    bign b=num,a=*this;
    if (!num.sign && !sign)
    {
        b.sign=1;
        a.sign=1;
        return b-a;
    }
    if (!b.sign)
    {
        b.sign=1;
        return a+b;
    }
    if (!a.sign)
    {
        a.sign=1;
        b=bign(0)-(a+b);
        return b;
    }
    if (a<b)
    {
        bign c=(b-a);
        c.sign=false;
        return c;
    }
    bign result;
    result.len = 0;
    for (int i = 0, g = 0; i < a.len; i++)
    {
        int x = a.s[i] - g;
        if (i < b.len) x -= b.s[i];
        if (x >= 0) g = 0;
        else
        {
            g = 1;
            x += 10;
        }
        result.s[result.len++] = x;
    }
    result.clean();
    return result;
}

bign bign::operator * (const bign &num)const
{
    bign result;
    result.len = len + num.len;

    for (int i = 0; i < len; i++)
        for (int j = 0; j < num.len; j++)
            result.s[i + j] += s[i] * num.s[j];

    for (int i = 0; i < result.len; i++)
    {
        result.s[i + 1] += result.s[i] / 10;
        result.s[i] %= 10;
    }
    result.clean();
    result.sign = !(sign^num.sign);
    return result;
}

bign bign::operator*(const int num)const
{
    bign x = num;
    bign z = *this;
    return x*z;
}
bign bign::operator*=(const bign&num)
{
    *this = *this * num;
    return *this;
}

bign bign::operator /(const bign&num)const
{
    bign ans;
    ans.len = len - num.len + 1;
    if (ans.len < 0)
    {
        ans.len = 1;
        return ans;
    }

    bign divisor = *this, divid = num;
    divisor.sign = divid.sign = 1;
    int k = ans.len - 1;
    int j = len - 1;
    while (k >= 0)
    {
        while (divisor.s[j] == 0) j--;
        if (k > j) k = j;
        char z[MAX_L];
        memset(z, 0, sizeof(z));
        for (int i = j; i >= k; i--)
            z[j - i] = divisor.s[i] + '0';
        bign dividend = z;
        if (dividend < divid) { k--; continue; }
        int key = 0;
        while (divid*key <= dividend) key++;
        key--;
        ans.s[k] = key;
        bign temp = divid*key;
        for (int i = 0; i < k; i++)
            temp = temp * 10;
        divisor = divisor - temp;
        k--;
    }
    ans.clean();
    ans.sign = !(sign^num.sign);
    return ans;
}

bign bign::operator/=(const bign&num)
{
    *this = *this / num;
    return *this;
}

bign bign::operator%(const bign& num)const
{
    bign a = *this, b = num;
    a.sign = b.sign = 1;
    bign result, temp = a / b*b;
    result = a - temp;
    result.sign = sign;
    return result;
}

bign bign::pow(const bign& num)const
{
    bign result = 1;
    for (bign i = 0; i < num; i++)
        result = result*(*this);
    return result;
}

bign bign::factorial()const
{
    bign result = 1;
    for (bign i = 1; i <= *this; i++)
        result *= i;
    return result;
}

void bign::clean()
{
    if (len == 0) len++;
    while (len > 1 && s[len - 1] == '\0')
        len--;
}

bign bign::Sqrt()const
{
    if(*this<0)return -1;
    if(*this<=1)return *this;
    bign l=0,r=*this,mid;
    while(r-l>1)
    {
        mid=(l+r)/2;
        if(mid*mid>*this)
            r=mid;
        else
            l=mid;
    }
    return l;
}

bign::~bign()
{
}

```

