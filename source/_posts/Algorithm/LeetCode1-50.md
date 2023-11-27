---
title: LeetCode 1-50题
date: 2018-09-01 14:33:54
categories: Algorithm
tags: [Cpp,LeetCode,Algorithm]
---

知识点：`Hash、双指针`[1]     `int的范围`[7]     `stack、ascii`[20] 
`str.substr(pos,n)注意n是子串长` [14]     

代码基本都在这里了：https://github.com/ixsim/OJ

<!---more--->

# 1.两数之和

- 朴素法

我的第一道LeetCode。上来就暴力解。我还纳闷呢，怎么输出结果和答案都一样。就是过不了。

原来是，时间复杂度为O(N)。过不了的。

- Hash O(nlogn)

哈希表Hash[x]  下标x表示x在nums中的下标。

**注意“** map底层使用平衡树一类的数据结构进行实现，插入和查询是O(logn)级别的。

代码

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> Hash;
        for (int i = 0; i < nums.size(); ++i)//建Hash
        {
            Hash[nums[i]]= i;
        }
        std::vector<int> ans(2);
        for (int i = 0; i < nums.size(); ++i)
        {
            if (Hash.find(target - nums[i])!=Hash.end()&&Hash[target-nums[i]]!=i)
            {
                ans[0] = i;
                ans[1] = Hash[target-nums[i]];
                break;
            }
        }
        return ans;
    }
};
```

上面这个版本更好理解。

然后看到这个版本更简洁。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int N = nums.size();
        vector<int> res;
        map<int ,int> subMap;
        for(int i = 0;i<N;i++)
        {
            int temp = target - nums[i];
            auto it = subMap.find(temp);
            if(it != subMap.end())
            {
                res.push_back(it->second);
                 res.push_back(i);
            }
            subMap[nums[i]] = i;//i=0时肯定不会输出结果，这样建Hash和判断合二为一。
        }        
        return res;       
    }
};
```

- 知识点：

为啥要和 `map.end()` 比较呢？

> **修改和查找数据**
> 
>  （1）修改Map["sunquan"]=11111;
> 
>  （2）查找数据 用Map.find(key); 可以通过键来查。
> 
> **切记不要用int value=Map[key];**
> 
> **这样会在Map中增加这个key**，**而value就是缺省值（int 为0，string为空字符串）**。
> 
> 通过方法（2），会返回迭代器的地址， **key不存在的话迭代器的值为**`Map.end()`

初学map哈哈。

https://www.cnblogs.com/panweiwei/p/6657583.html

# 2 两数之和

easy

# 3 无重复字符的最长子串

- 不能判断到有重复字符就从0开始算啊。字符串的头尾不固定的。
  
  比如 `avadc` 虽然a在第三个位置出现了。但是不能重新计数。前面的v也可以算的。
  
  - 很快就解决了这个问题。就是 计数的变量count 找到重复字符后，不置为0，而是置为 两个相同字符的坐标差。这样就包含了后面的字符。
  - 新问题就是，从新计数的单词，之前的字母还在map中没清空。怎么办？
    - 我设了一个开始坐标start，只有在map中且坐标大于这个start才算重复出现。

看下第一的答案：

```cpp
int lengthOfLongestSubstring(string s) {

    int subStringStart = 0,subStringEnd = 0, maxLength = 0;
    string subString;
    size_t occPos;        for(subStringEnd;subStringEnd<s.length();subStringEnd++){
        //查找subStringStart位置之后是否有要插入的字符
        occPos = subString.find(s[subStringEnd],subStringStart);
        //如果subString中已有带插入字符，将子串中已有字符的位置(occPos)的下一位置(occPos + 1)设置为无重复子串的开始位置,即向右移动滑窗
        //不断调整无重复子字符串的开始位置
        if(occPos != string::npos){
            subStringStart = occPos + 1; 
        }
        //依次将s中的元素插入subString中，同时不断计算最长子字符串长度并更新
        subString.push_back(s[subStringEnd]);
        maxLength = max(maxLength, subStringEnd-subStringStart+1);
    }
    return maxLength;
}
```

# 04二叉树的最大深度

必备

# 5最长回文子串

没想到我的方法效率还不错。

# 6.Z字形变换

水题。用一个flag记录存入的方向即可。详情看代码。

# 7.反转整数

- 正解

```cpp
int reverse(int x) {
    if(x==-2147483648)
            return 0;
    int sign ;
    x>0? sign=1: (sign=-1,x=-x);
    long ans=0;
    while(x){
        int tmp = x;
        x = x/10;
        ans = ans*10 + (tmp-x*10);    
    }
    if (ans > INT_MAX)
        return 0;
    return ans*sign;
}
```

- Problems
1. 第一次问题出在ans的类型上。没有存成`long`。
   
   输入是1534236469时，输出错误。
   
   Int 的范围是 -2^31 ~ 2^31-1，即-2147483648~2147483647
   
   输入1534236469输出应该是9646435461都就90多亿了。int最大存21亿。
   
   所以应该输出零。而且这个数在ans存的时候要用`long`型，再和`INT_MAX`判断一次再return。

2. 改了long之后。1032个用例就差一个过不了了。就是-2147483648。
   
   -2147483648会被转成正2147483648。而正int里最大是2147483647。存不下2147483648 。所以特判了。

# 8.atoi

- 在C++里，长度不一样的String比较会是什么规则？
  
  - 直接输入： `cout << "abc"<"bbbb";`
    
    这种情况注意了：比较的是两个const char*！实则比较的是他们的地址而已。真的相比较要用：`strcmp("abc","bbbb")`
  
  - 比较的时候：
    
    1. 先不管两个串的长度，一位一位的比下去。如果有一个串的相同位更大，立马返回结果。
    2. 当一个串比完，还都一样的时候，长的更大。

- 这题意思不大，就是把所有的情况都考虑到。反正我是没用到啥编程技巧。

# 9.回文数

- 解法

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
    int tmp = x;
    if(x<0)
        return false;
    if(x==0)
        return true;
    if (x%10 == 0)
        return false;

    int y=0;
    while(x){
        y = y*10 + (x%10);
        x = x/10;
    }
    if(y==tmp)
        return true;
    else
        return false;
    }
};
```

- Problems
1. 开始忘了把x先存到tmp中。最后就直接判断` y==x` 结果每次都是返回false。
   
   很尴尬。x在while中肯定会被改成0啊。

2. 最后一个if只判断了true的情况，忘了写else😂😂😂

低级错误。见笑。

- 知识点  取消cin同步。取消cin与cout绑定。

在这题和翻转数字那题的优化解里都看到这么一断：

```cpp
//lambda 表达式，可以立即执行，在main函数之前执行，取消输入输出同步，较快输入输出速度
static const auto ban_io_sync = []()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();
//以后直接当模板用
```

 **`std::ios::sync_with_stdio(false)`**

这句语句是用来**取消cin的同步**，什么叫同步呢？就是iostream的缓冲跟stdio的同步。如果你已经在头文件上用了using namespace std;那么就可以去掉前面的std::了。

取消后就cin就不能和scanf，sscanf, getchar, fgets之类同时用了，否则就可能会导致输出和预期的不一样。 

取消同步的目的，是为了让cin不超时，另外**cout的时候尽量少用endl，换用”\n”，也是防止超时的方法**。 
当然，**尽量用scanf，printf就不用考虑这种因为缓冲的超时**了。

 **`cin.tie(NULL)`**

取消cin与cout的绑定

------

```
把上一段代码加到我的解法前面，运行时间直接从120ms到了64ms。
```

------

- 再看这个解法
  
  ```cpp
  static auto x = []() {
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      return 0;
  }();
  
  class Solution {
  public:
      bool isPalindrome(int x) {
          stringstream ss;
          ss << x;
          string str;
          ss >> str;
          string strTmp = str;
          reverse(str.begin(), str.end());
          if (strTmp == str)
              return true;
          return false;
      }
  };
  ```
  
  存成字符串。然后用了个reverse翻转。STL里面啥都有啊。

# 10.正则表达式匹配

# 11盛最多水的容器

# 12整数转罗马数字

# 13.罗马数字转整数

- 无聊的一题

# 14.最长公共前缀

- 解

```cpp
string Prefix2(string a,string b){
        string ans = "";
        int p = 0;
        while(p <= (a.size()-1) && p <= (b.size()-1) ){
                if(a[p] == b [p]){
                        ans += a[p];
                        p++;
                }
                else
                        break;
        }
        return ans;
}
string longestCommonPrefix(vector<string>& strs) {
    string ans = "";
    if(strs.size()==0)
        return ans;
    if(strs.size()==1)
        return strs[0];
    auto iter1 = strs.begin();
    while(iter1 != (strs.end()-1)){
        auto iter2 = iter1 +1;
        ans = Prefix2(*iter1,*iter2);
        if(ans == "")
            break;
        iter1++;
        *iter1 = ans;
    }
    return ans;
}
```

我的解真是弱爆了。

**Problems**

- 第一次报错
  
  > "Runtime Error Message:reference binding to null pointer of type 'struct value_type'
  > 
  >  Last executed input: []
  
  百度了一下。https://blog.csdn.net/zy2317878/article/details/78820900  特判：如果size()是0则返回""
  
  边界值特殊值要考虑好啊。

- 第二次是输入只有1个单词的时候。因为我是自己写了个比较两个单词最长前缀的函数。所以输入只有一个的时候，直接返回了""。正确答案应该是返回这个单词。我又强行加了这么一种情况。

- 我的解法效率极低。下面去看看大神们怎么解吧。

优化解

```cpp
string longestCommonPrefix(vector<string>& strs) {
        int vec_len=strs.size();
        if(vec_len==0)
            return "";
        int str_len=strs[0].size();
        for(int i=0;i<str_len;i++)
          for(int j=1;j<vec_len;j++)
            if(strs[j][i]!=strs[0][i])
                return strs[0].substr(0,i);
        return strs[0];
}
```

知识点：

- `str.substr(x,y)`就是取子串。
- `str.substr(0,0)`应该就是`""`

这个解的逻辑确实很清晰！

- 相同的逻辑，解答里还有一个0ms的写法就是
  
  `while((strs[0])[i])`

# 14最长公共前缀

# 15三数之和

# 16最接近的三数之和

# 17电话号码的字母组合

# 18四数之和

# 19删除链表的倒数第N个节点

# 20.有效的括号

**Problems**

- `char`类型就用**单引号**啊！！！
  
  之前写 `s[i] == "("`一直报错。我就是整不明白为啥报错。
  
  **单引号啊！！！**

- `vector.end()`是地址，而且还是最后一个元素后面的地址。所以最后一个元素应该是
  
  `*(vector.end()-1)` 
  
  遍历的话可以用`for(auto s:vector)`

- 拿过题就用vector声明了一个栈做。不知道有`stack`都。NAIVE~

- 判断")}]"这三种情况的时候应该先看栈里是不是空。再看栈顶的元素。不然如果栈为空，取栈top()会跑不出来。

- 每次`return flase`之后都要记得**break**跳出循环啊

- **vector中v[i]与v.at(i)的区别**
  
  ```cpp
  v[0];    // A
  v.at[0];  // B
  ```
  
  如果v非空，A行和B行没有任何区别。
  
  如果**v为空或者下标越界**，B行会抛出std::out_of_range异常，A行的行为未定义。
  
  c++标准不要求vector::operator[]进行下标越界检查，原因是为了效率，总是强制下标越界检查会增加程序的性能开销。设计vector是用来代替内置数组的，所以效率问题也应该考虑。不过使用operator[]就要自己承担越界风险了。
  
  如果需要下标越界检查，请使用at。

我的解效率特别差。看一下人家的

**优化解**

```cpp
class Solution {
public:
    bool isValid(string s) {
       stack<char> sta;
    int length = s.length();
    if (length % 2 == 1) return false;
    if (s.empty()) return true;
    for (int i = 0; i < length; i++)
    {
        if (sta.empty())
        {
            sta.push(s.at(i)); 
        }
        else if(sta.top() == s.at(i) - 2 || sta.top() == s.at(i) - 1)
        {
            sta.pop();
        }
        else
        {
            sta.push(s.at(i));
        }
    }
    return sta.empty() ? true : false;
    }
};
```

哎！简洁又效率。

- 先判断了长度是奇数返回false.为空返回false.

- 没有瞎判断字符是不是`'{([])}'`
  
  而是利用了ascii码。那为啥有 -1 有 -2 呢？
  
  看了ascii码表你就知道了。

| ASCII值 | 控制字符 | ASCII值 | 控制字符    | ASCII值 | 控制字符  | ASCII值  | 控制字符  |
| ------ | ---- | ------ | ------- | ------ | ----- | ------- | ----- |
| 0      | NUT  | 32     | (space) | 64     | @     | 96      | 、     |
| 1      | SOH  | 33     | !       | 65     | A     | 97      | a     |
| 2      | STX  | 34     | "       | 66     | B     | 98      | b     |
| 3      | ETX  | 35     | #       | 67     | C     | 99      | c     |
| 4      | EOT  | 36     | $       | 68     | D     | 100     | d     |
| 5      | ENQ  | 37     | %       | 69     | E     | 101     | e     |
| 6      | ACK  | 38     | &       | 70     | F     | 102     | f     |
| 7      | BEL  | 39     | ,       | 71     | G     | 103     | g     |
| 8      | BS   | **40** | **(**   | 72     | H     | 104     | h     |
| 9      | HT   | **41** | **)**   | 73     | I     | 105     | i     |
| 10     | LF   | 42     | *       | 74     | J     | 106     | j     |
| 11     | VT   | 43     | +       | 75     | K     | 107     | k     |
| 12     | FF   | 44     | ,       | 76     | L     | 108     | l     |
| 13     | CR   | 45     | -       | 77     | M     | 109     | m     |
| 14     | SO   | 46     | .       | 78     | N     | 110     | n     |
| 15     | SI   | 47     | /       | 79     | O     | 111     | o     |
| 16     | DLE  | 48     | 0       | 80     | P     | 112     | p     |
| 17     | DCI  | 49     | 1       | 81     | Q     | 113     | q     |
| 18     | DC2  | 50     | 2       | 82     | R     | 114     | r     |
| 19     | DC3  | 51     | 3       | 83     | S     | 115     | s     |
| 20     | DC4  | 52     | 4       | 84     | T     | 116     | t     |
| 21     | NAK  | 53     | 5       | 85     | U     | 117     | u     |
| 22     | SYN  | 54     | 6       | 86     | V     | 118     | v     |
| 23     | TB   | 55     | 7       | 87     | W     | 119     | w     |
| 24     | CAN  | 56     | 8       | 88     | X     | 120     | x     |
| 25     | EM   | 57     | 9       | 89     | Y     | 121     | y     |
| 26     | SUB  | 58     | :       | 90     | Z     | 122     | z     |
| 27     | ESC  | 59     | ;       | **91** | **[** | **123** | **{** |
| 28     | FS   | 60     | <       | 92     | /     | 124     |       |
| 29     | GS   | 61     | =       | **93** | **]** | **125** | **}** |
| 30     | RS   | 62     | >       | 94     | ^     | 126     | `     |
| 31     | US   | 63     | ?       | 95     | _     | 127     | DEL   |

# 21 合并有序链表

## 解

不贴我的了。写的太烂了。新建了一个链表一个数一个数插进去的。

贴一个同效率的。简洁好多。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* l0;

        ListNode* head=new ListNode(-1);
        l0=head;
        while(l1!=NULL&&l2!=NULL)
        {
            if(l1->val<=l2->val) 
            {
                l0->next=new ListNode(l1->val);
                l1=l1->next;
            }
            else 
            {
                l0->next=new ListNode(l2->val);
                l2=l2->next;
            }
            l0=l0->next;
        }
        l0->next = l1 ? l1 : l2;
        return head->next;
    }
};
```

~ 知识点

- 一个是建ListNode。声明节点的细节。`new struct`

- 一个就是重要的技巧。别声明一个新指针为NULL。除非你开车很稳。
  
  - 关于`NULL`和`nullptr`:
    
    `NULL`其实是**int型的0**，为了**真正的空指针**，c++11推出`nullptr`

- 可以先声明一个随意值的节点(比如-9999)，然后在这个节点后面处理就好了。最后return时返回这个节点的next就好了。

## Problems

- 输入是`[]和[0]`的时候不行。没考虑第一个链表就是空的情况。所以开头定义tmp就直接指向L1；

- **重要！！！**
  
  新声明一个**节点**`new struct`。和新声明一个**指针**`*p`不一样。
  
  这个问题要想清楚！！！

- 记得要先把头存起啦啊。不然你移来移去拿什么返回链表头。

- 循环遍历所有节点最好用`while(list->next)`。这样指针刚好停在最后一个节点。

## 递归的解法

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==NULL || l2==NULL) return (l1==NULL ? l2: l1);
        if(l1->val<l2->val) 
        {
            l1->next=mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next=mergeTwoLists(l1,l2->next);
            return l2;
        }

    }//end function
};
```

**合并**两个链表。就是判断完**头**元素后。**合并** <u>剩下的部分</u> 连接到 小的头里。

结束条件：

如果一个为Null（总是合并剩下的部分一定会遇到null）则返回另一个。

# 22括号生成

# 23合并K个排序链表

# 24两两交换链表中的节点

# 25k个一组翻转链表

# 26. 删除排序数组中的重复项

- 循环左移之后。记得这一轮就不要让标记位置走到下一个了。
- 传入空字符串的时候。我的程序会完全没有符合的条件。而导致没有返回值超时。以后要注意写条件的时候就想清楚会不会有特殊情况。
- sb了。没看题是排好序的。而且遍历的时候是遍历你返回值n的前n个。

# 27. 移除元素

吸收了上一题的答案。直接超越100%：

```cpp
int n = 0;
for (int i = 0; i<nums.size();i++){
    if(nums[i]!=val)//只要不是val就存进来
        nums[n++]=nums[i];
}
return n;
```

# 28实现strStr()

# 29两数相除

# 30与所有单词相关联的字串

# 31下一个排列

# 32最长有效括号

# 33搜索旋转排序数组

# 34在排序数组中查找元素的第一个和最后一个位置

# 35. 搜索插入位置

PASS

# 36有效的数独

# 37解数独

# 38. 报数

水题不解释

# 39组合总和

# 40组合总和 II

# 41缺失的第一个正数

# 42接雨水

# 43字符串相乘

# 44通配符匹配

# 45跳跃游戏 II

# 46全排列

# 47全排列 II

# 48旋转图像

# 49字母异位词分组

# 50Pow(x, n)