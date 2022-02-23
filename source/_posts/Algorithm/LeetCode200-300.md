---
title: LeetCode 200-300
date: 2019-3-10 19:07:02
categories: [Algorithm]
tags: [Cpp,LeetCode]
---

知识点：`npos`[345] 、`memset`[387] 、  `reverse()`[557](#557反转字符串中的单词III)、   `istringstream`[557](#557反转字符串中的单词III)、`树`[606]、`to_string()`[788]、`transform()`[819]、`strA.find(strB) != string:npos`[#686]

<!---more--->

# Problems

- [ ] 超级丑数的两个答案看懂
- [ ] 

# 203 删除链表中的节点

和237题不同的是这个题是给了值。237题给的是节点。

感悟和上一个#83题查不多。就是想删除某个节点。只把 cur指针赋NULL是不行的。因为**上一个节点的next 还指着 之前 cur的地址**啊。cur是为空了，上一个节点的next不是空啊。

因为觉得删最后一个节点的情况不好写。转递归法一气呵成哈哈。

```cpp
ListNode* removeElements(ListNode* head, int val) {
    if(head==NULL)
        return head;
    if(head->next == NULL){
        if(head->val == val)
            return NULL;
        else
            return head;
    }
    if(head->val == val)
        if(head->next)
            return removeElements(head->next,val);
        else
            return NULL;
    else
    {
        head->next = removeElements(head->next,val);
        return head;
    }
}
```

当然效率一般。超越了96%。我再参考下别的。

- 处理最后一个节点的方法。可以再声明一个指针p。一个指针往下移。p不移动。这样就可以定位倒数第二的节点。

- 下面这个解法很清晰了。

  ```cpp
  if (head == NULL)
  	return head;
  ListNode phead(0);
  ListNode *ptemp = head;
  ListNode *p = &phead; //phead是一个结构体。所以要指向它的地址。
  //也可以在之前就声明ListNode* phead = new ListNode(9999);就不用取地址了。
  phead.next = ptemp;
  while (1)
  {
      if (ptemp->val == val)
      {
          p->next = ptemp->next;
          ptemp = p->next;
      }
      else
      {
          p = ptemp;
          ptemp = ptemp->next;
      }
      if (ptemp==NULL)
          break;
  }
  return phead.next;
  ```

# [205. 同构字符串](https://leetcode-cn.com/problems/isomorphic-strings/)

准备都存到map里，然后遍历对比。

没想到遍历map时，是按下标的字母顺序。比如map['b']先存入，map['a']又存入，map从begin开始遍历，还是先访问a。

因此需要一个map来存，读取的顺序。

循环读完两个字符串后，比较两组map。

- 一组是看这个字母是不是都是第i次出现的字母
- 一组看这个字母是不是到现在出现了同样的次数

# 233 数字1的次数

剑指offer里刷到了。这题也是Hard？

# 234 回文链表

- 注意。长度为1的链表也是回文的。
- 我的方法比较笨。先跑一遍记录有多少个数。再遍历前半部分，把数存到栈里。再遍历后半部分。挨个出栈。
- 下面看一个知识点，

## 快慢指针

> 知识点：快指针走两步。慢指针走一步。快指针到链尾。慢指针到中间。

```cpp
bool isPalindrome(ListNode* head) {
    ListNode *pre = nullptr, *cur = head, *quick = head;
    //下面这一段很巧妙。不仅找到了中间节点。还把链表的前半部分都倒置了存在pre里。
    //倒置的方法：
    //1.预存当前节点cur到tmp，
    //2.cur后移，保证下一步进行。但我们有tmp预存了cur。
	//3.tmp的next置为pre(初始的pre刚好是NULL)。
    //4.pre=tmp。这时候pre已经是倒置链表的头。
    while (quick && quick->next) {
        quick = quick->next->next;
        auto tmp = cur;
        cur = cur->next;
        tmp->next = pre;
        pre = tmp;
    }
    if (quick != nullptr)
        cur = cur->next;
    while (cur) {
        if (cur->val != pre->val)
            return false;
        else {
            cur = cur->next;
            pre = pre->next;
        }
    }
    return true;
}
```

- 最后说一下排行第一的方法。人家没存到栈里。存到了向量里。然后直接用坐标定位来判断首尾是否一样。我真的是太定向思维了。看到是从中间往两侧判断就知道用栈。辣鸡~

# 237 删除某个节点

这个比较简单。操作指针就好了。

注意此题简单的一个重要条件就是：

**给点节点为非末尾节点**

这样就不会有删除最后一个节点的情况。

# 240 搜索二维矩阵ii

剑指Offer第三题 

注意：修剪的时候可以行列同时进行。我的100%代码：

```c++
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if(m==0)
        return false;
    int n = matrix[0].size();
    if(n==0)
        return false;
    n--;
    while(matrix[0][n]>=target&&n>=0){
        if(matrix[0][n]==target)
            return true;
        n--;
    }
    if(n<0)
        return false;
    int i = 0;
    while(i<m&&matrix[i][n]<=target)
    {
        if(i<m&&matrix[i][n]==target)
            return true;
        i++;
    }
    if(i==m)
        return false;
    //修剪完毕
    while(i!=m&&n!=-1){
        if(matrix[i][n]==target)
            return true;
        if(matrix[i][n]>target)
            n--;
        else
            i++;
    }
    return false;
}
```



# 263丑数

- 没考虑输入0的情况
- 加了 禁止 i/o 同步的代码后，时间从 8ms--> 0ms

# 264丑数2

剑指Offer刷过了

# 313超级丑数

按照丑数2的思维原封不动地写，AC了。虽然AC了。但是也太辣鸡了，执行了12s。第一名12ms。一百倍的效率差距，完美的解释了我能打100个。赶紧去看看人家怎么写的。

```cpp
int nthSuperUglyNumber(int n, vector<int>& primes) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > min_heap;
    vector<int> uglies(n); //丑数集
    uglies[0] = 1; //存入1
    vector<int> last_factor(n);
    int k = primes.size(); //因子个数
    vector<int> idx(k);    //该因子要组成的数的坐标
    for (int i =0; i < k; ++i) {
        min_heap.emplace(primes[i], i);
    }
    for (int i = 1; i < n; ++i) {
        tie(uglies[i], last_factor[i]) = min_heap.top();
        min_heap.pop();
        int j = last_factor[i];
        ++idx[j];
        while (last_factor[idx[j]] > j) ++idx[j];
        min_heap.emplace(primes[j] * uglies[idx[j]], j);
    }
    return uglies[n - 1];
}
```

好吧。暂时。。。。。。。。。。看不懂。我们先看第二名的答案吧。这个貌似没用啥我不知道的语法：

```cpp
int nthSuperUglyNumber(int n, vector<int>& primes) {
    if (n == 1)
        return 1;
    int m = primes.size(); //因子个数
    vector<int> ugly(n,INT_MAX); //丑数集合 用超大数来初始化的 不明觉厉
    vector<int> tmp(m,1);
    vector<int> count(m,0);
    int next = 1;
    for (int i = 0; i < n; i++) {
        ugly[i] = next;
        next = INT_MAX;
        for (int j = 0; j < m; j++) {
            //cout << "j "  << j << " tmp " << tmp[j] << " ugly " << ugly[i] << " count " << count[j] << " next " << next << endl;
            if (tmp[j] == ugly[i]) {
                tmp[j] = ugly[count[j]]*primes[j];
                count[j]++;
            }
            next = min(next,tmp[j]);
        }

    }
    return ugly[n-1];
}
```

# 709转换成小写字母

`A~Z`的ascii码为`65~90`   小写字母对应+32

# 657机器人能否返回原点

```cpp
bool judgeCircle(string moves) {
    char tb[256]{0};
    for(auto ch : moves)
        ++tb[ch];
    return tb['R'] == tb['L'] && tb['U'] == tb['D'];
}
```

# 344反转字符串

EASY

# 557反转字符串中的单词III

从句子里取单词的方法：

```cpp
#include <sstream>
string reverseWords(string s) {
    istringstream is(s);//把String s变成一个输入流is
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

# 521最长特殊序列I

抠定义的题。直接返回最长的子串长度即可。

# 520检测大写字母

各种if分情况🙂

# 788旋转数字

- int转string： `str = tostring(i);`

- 最好不要一次写两次循环。能拆出函数来就写一个函数。

# 824. 山羊拉丁文

- 用istringsteam挨个读单词并处理。处理后加一个空格。

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



---

字符串的Easy完结啦。下面按Easy题号刷满100再做计划！

