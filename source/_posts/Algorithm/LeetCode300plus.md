---
title: LeetCode 300题以后
date: 2018-09-10 19:07:02
categories: [Algorithm]
tags: [Cpp,LeetCode]
---

知识点：`npos`[345] 、`memset`[387] 、  `reverse()`[557]、   `istringstream`[557]、`树`[606]、`to_string()`[788]、`transform()`[819]、`strA.find(strB) != string:npos`[686]

<!---more--->

# 基础部分

- string对象的操作

  ```cpp
  istringstram os
  os<<s   //s写入到输出流os中。返回os
  is>>s	//从输入流is读取字符串赋给s，返回is。
  s.empty()
  s.size()
  s[n] //n从0计
  ```

# 709. 转换成小写字母

`A~Z`的ascii码为`65~90`   小写字母对应+32

# 657. 机器人能否返回原点

```cpp
bool judgeCircle(string moves) {
    char tb[256]{0};
    for(auto ch : moves)
        ++tb[ch];
    return tb['R'] == tb['L'] && tb['U'] == tb['D'];
}
```

# 344. 反转字符串

EASY

# 557. 反转字符串中的单词III

从句子里取单词的方法：

```cpp
string reverseWords(string s) {
    istringstream is(s);
    string t = "";
    string res = "";
    while (is >> t)
    {
        reverse(t.begin(), t.end());
        res += t + " ";
    }
    res.pop_back();
    return res;
}
```

# 521. 最长特殊序列I

抠定义的题。直接返回最长的子串长度即可。

# 520. 检测大写字母

各种if分情况🙂

# 788. 旋转数字

- int转string： `str = tostring(i);`

- 最好不要一次写两次循环。能拆出函数来就写一个函数。

# 824. 山羊拉丁文

- 用istringstream挨个读单词并处理。处理后加一个空格。

  注意，这样句子最后就会多一个空格。需要输出`ans.substr(0,ans.size()-1)`

- 把单词的第一个字母放到最后的方法：

  ```cpp
  stringstream oss;
  oss<<word.substr(1)<<word[0];
  ```


# 606. 根据二叉树创建字符串

```cpp
//唯一要注意的地方就是函数定义参数时ans前面加引用&
void visit(TreeNode* t,string &ans){
    if (t == NULL)
        return;
    ans += to_string(t->val);
    if(t->left)
        ans += "(";
    if(!t->left&&t->right)//如果没有←但是有→儿子
        ans += "()";
    visit(t->left,ans);
    if(t->left)
        ans += ")";
    if(t->right)
        ans += "(";
    visit(t->right,ans);
    if(t->right)
        ans += ")";
}
string tree2str(TreeNode* t) {
    string ans = "";
    visit(t,ans);
    return ans;
}
```



# 696. 计数二进制子串

- 挨个取子串的解法过了85/90用例。败在一个超级长的的字符串上。也是，人家长度范围就是50000呢。咋整捏。

- 找到了规律。奇低的效率过了。

- 看个好答案吧：

  ```cpp
  int countBinarySubstrings(string s) {
      int n=s.size(),pre=0,cur=1,res=0;
      for(int i=1;i<n;++i)
      {
          if(s[i]==s[i-1])
          {
              ++cur;
          }
          else
          {
              pre=cur;
              cur=1;
          }
          if(pre>=cur)
              ++res;
      }
      return res;
  }
  ```

# 893. 特殊等价字符串组

不会🙂

# 551. 学生出勤记录

水题

# 67. 二进制求和

- 二进制转了int。发现人家给的二进制数太大了int存不下--》换long，存不下。--》long long，存不下—》unsigned long long，存下了，加和以后存不下。😂。—》此方法卒。
- 纯字符判断的方法过了~没啥意思。

# 345. 反转字符串中的元音字母

水题 

- 学到知识点 : npos

  std::string::npos 常数值，等于size_t的最大值。通常用来做string**不存在的位置**的标记。

# 541. 反转字符串 II

`#557`知道了有reverse()后。分分钟。

- 进阶：`reverse(s.begin(),s.begin()+i)` 可以用**s.begin()+i**这种方式定位

# 383.赎金信

水。存数组OK

# 819. 最常见的单词

- vector中没有find方法。要利用algorithm这个头文件。

  ```cpp
  vector<string>::iterator it = find(vt.begin(),vt.end(),s);
  if(it != vt.end())
  ```

- 字符串转小写：`transform(s.begin(),s.end(),s.begin(),::towlower);`

# 28. 实现strStr()

- 小写字母ascii码是大写的  **+**   32

# 125. 验证回文串

水。

# 459. 重复的子字符串

- 之前我取 tmp = s.substr(0,step) 取出来之后 每次让tmp加上自己来增加。没考虑到这样tmp这样是2的指数级增加。
- 有continue的情况却忘了i— 进入了死循环

# 387. 字符串中的第一个唯一字符

- 初始化数组全为0：

  ```cpp
  int nums[26];
  memset(nums,0,len * sizeof(int));
  ```

# 443. 压缩字符串

**不会！**

# 434.字符串中的单词数

和上题一样水。

# 68.验证回文字符串 Ⅱ  

排除一个字符只让一个标记移动的时候。要判断清除。(不好形容)

比如字符串cuucu。s[0]≠s[4]...

但是s[1]=s[4]..这时候如果让第一个标记右移，新字符串是uucu就错了。

因为其实s[0]=s[3]..应该让第二个标记左移。得到新串cuuc。

# 686. 重复叠加字符串匹配

折腾半天。过了。这题要二刷。样例太狗了哈哈。

# 859. 亲密字符串

- 突然有个感悟就是。不要老是在判断过程中就 `return true ,false` 的。导致常常有的情况都没有return 的。最好是这样  `ans = 1; break;`、然后最后`return ans;`    稳

# 866.回文素数

打表 很无聊



