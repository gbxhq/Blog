---
title: 剑指offer
date: 2018-10-19 15:12:07
categories: Algorithm
tags: [Note,Cpp]
---

《剑指Offer》读书笔记。感谢强哥给的书。希望明年的我也可以Offer满满~

代码基本都在这里了：https://github.com/ixsim/OJ

<!---more--->

# Problems

- [ ] P31单例模式
  
  ```cpp
  class A{
      static A getInstance();
      void func();
  private:
      A();
      A(A& rth);
      ~A();
  };
  A A::getInstance(){
      static A a;
      return a;
  }
  ```

- [ ] 这个代码啥问题
  
  ```cpp
  if(p->left||p->right){
      swap(p->left,p->right);
  }//这样就不行
  //这样就可以
  if(p->left||p->right){
      TreeNode *temp = p->left;
      p->left = p->right;
      p->right = temp;
  }
  ```
  
    看上去一样。但其实 swap两个指针。在里面操作半天。回来p的左右孩子还是没变化。

- [ ] 红黑树    据说和30题有关

- [ ] P75 斐波那契的公式法

- [ ] P82 位运算相关的题目和笔记是薄弱环

- [ ] 24 二刷还是没思路

- [ ] 27 重刷 递归方法

- [x] 30题 解法二回看

- [ ] 35相关题目回看

- [ ] 37 书上方法

- [ ] 39-1 书上方法

- [ ] 39-2 书上方法

- [ ] 40 重刷

- [ ] 41 其实没做出来

- [x] 45 约瑟夫写推导

- [ ] 53 正则匹配

# Notes

- 在C/C++中，数组作为函数的参数进行传递时，数组就自动退化为同类型的指针。
- 需要倒着再干啥的考虑【栈】
- 很多需要快速找到最大值或最小值的问题都可以用【堆】来解决
- 由于精度原因不能用等号判断两个小数是否相等。如果两个小数差的绝对值很小，就可以认为他们相等
- 我们有成熟的O(N)算法得到数组中任意第k大的数字
- 采用值传递，形参到实参会产生一次复制操作
- 题目描述一棵树--> 是不是二叉树 --> 是不是排序树

# 第二章 基础知识

## 3搜索二维数组

- 牛客的没AC。先LeetCode上找了74搜索二维矩阵，这个稍微简单点，用一个二分查找就可以。然后240题搜索二维矩阵II就是一样的了。

- 看书知道了要删减的思路后。就从右上角开始。先排除的列，又排除的行。然后继续用**最笨的方法去查找**（其实也是一步步排除行和列的过程）。没有考虑到：
  
  排除 列 和 行 的过程可以**同时进行**，直到循环结束啊。

- PS:我之前这种思路是错误的：
  
  类似二分查找，先找到要搜的列，再从这一列用二分查找。这样其实有的元素存在，但并不在你要找的这一列。

## 4替换空格

## 5尾到头打印链表

用栈比较easy了.但是**递归**的写法注意：

```c++
//我的写法：
while(node->next!=nullptr){function递归(a,b);}
//1.递归不能用while 要用if 啊
//2.不能只看是不是最后一个节点。还要看当前节点：
if(node!=null){
    if(node!=nullptr){
        func();
    }
}
```

## 6重建二叉树

确定递归思路后一口气撸下来，⌘ + R , 测试没问题 。提交OJ。PASS。这一周看书最爽的一次AC。

## 7用两个栈实现队列

虽然自己写AC了。但是方案不如书上。

我是借助stack2进行pop, 每次pop完再回传给stack1。

其实不需要的。好好考虑考虑吧！

## 8 旋转数组的min

看似水题。但遍历一次要O(N)

二分查找可以边O(logN)。然后还要考虑特殊情况。不可轻视

```cpp
int minNumberInRotateArray(vector<int> v) {
    int n = v.size();
    int l = 0, r = n-1;
    int m = l;
    while(v[l]>=v[r]){
        if(r-l==1){
            m = r;
            break;
         }
        int m = (l+r)>>1;
        if(v[m]>=v[l])
            l = m;
        if(v[m]<=v[r])
            r = m;
    }
    return v[m];
}
```

## 9 斐波那契

除了普通法和递归法，要注意还有O(logN)的解法。

## 10 二进制中1的个数

位运算。

- 1不停地执行左移。执行到首位（符号位）不就成了负的？然后再左移不就永远成了负的？
  
  ANS: 左移不会保留符号位。右移才保留

- 位运算效率远高于乘除。尽可能得用位运算代替乘除。

# 第三章 高质量代码

## 11 快速幂

马马虎虎地过了，看了书后发现，我并没有考虑底数是特殊值的情况。（只分了指数的情况）

Note：

- 用全局变量的方式抛出异常。

- [ ] 由于**底数是double型，不能直接用==判断是否是0**。要专门写一个函数来判断！！！

- [ ] 指数为负的情况！！！

## 12 打印1到n位最大数

不能用int型。要用string型。

- [ ] 递归的写法要注意！

## 13 O(1)时间内删除链表节点

题目思路简单。注意这种情况：

- **只有一个节点，要删除这个节点。**

## 14 调整数组顺序

判断奇数偶数这回我知道用位运算了。但是请注意这个Warn：

- ` & has lower precedence than ==;`  等号运算符的优先级高于&！所以要用位运算判断的与或非 **记得加括号**

## 15 链表中倒数第k个节点

- 我这个二傻子。把节点一个个存到栈里。然后出栈到第k个。AC了。
  
  为啥不存到vector里然后用下标就能返回倒数第k个呢。

- 书上的方法，用两个指针，两个相距k，当一个走到尾的时候，另个就是答案了。
  
  - [ ] 这个方法需要重刷。因为要考虑到鲁棒性问题。

## 16 反转链表

先用了栈做。龙哥刚好过来。让我自己想想别用栈。我一想。哈哈。挺简单。

## 17 合并有序链表

我用循环写的。比较简单。Note:

- [ ] 用递归做一遍

## 18 判断是不是树的子结构

我最后AC的版本存在本地了。有这么个错误代码需要注意：

```cpp
bool HasSubtree(TreeNode* p1, TreeNode* p2){
    if(p1==nullptr||p2==nullptr)
        return false;
    if(p1->val==p2->val)
    {   
        if(isSame(p1,p2))
            return true;
        else {
            if(p1->left)
                HasSubtree(p1->left,p2); 
            if(p1->right)
                HasSubtree(p1->right,p2);
        }
    }
    return false;
}
```

问题出现在第10行。我的想法是，如果有左子树就去走左子树。但是Debug的时候我发现，就算走到了第7行的return true, 程序也不会返回true的。因为我的第10行根本没有返回啊。只是去走一走。返回的一个true是从栈里返回到了第10行，并没有从第10行返回给main啊。

- [ ] 重刷标记

PS：这题牛客的测试用例绝对不全。

### &&的短路特性

```cpp
/*求1+2+…+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字以及条件判断语句.
解：利用&&的短路特性：如a&&b即如果a为假，b则被短路（不运算）
*/int add_fun(intn)                  
{   int num=0;
    (n>0)&&(num=n+add_fun(n-1));     
    return num;       
} 
int main( ) 
{ 
    intsum=0; 
    intn=100;  
    printf("%d\n",add_fun(n)); 
    return0; 
} 
```

# 第四章 解决思路

## 19 二叉树的镜像

easy 秒过

## 20 顺时针打印

思路清晰。一次撸过。下次看看自己怎么写的就好啦。

不要二刷。

## 21最小栈

easy不多说

## 22入栈出栈次序

知道了用辅助栈的思路。比较好写。

不过，我没仔细看书上的代码。有空还是好好看一看。

## 23二叉树层序遍历

层序遍历就用队列嘛。easy。

## 24判断是不是后序遍历序列

没思路。看书吧！

看书知道了思路。过了。其中输入数组为空的情况没考虑。细心点！

## 25路径选择

应该是深度优先搜索。但我最近脑子不转，写递归的思路老是抽。

老是想，这个节点遍历完往回退的时候，怎么减到当前的节点。

其实在循环的最后一步把栈给POP一下就行了

## 26复杂链表的复制

我的思路还是很清晰的。用一个map存。Key是原链表的地址，Value是新链表的地址。这样就有了一一对应关系。看代码：

```cpp
RandomListNode* Clone(RandomListNode* pHead)
{
    RandomListNode *ans = new RandomListNode(-1);
    RandomListNode *cur = ans;

    map<RandomListNode *,RandomListNode *> map;

    while(pHead!=nullptr){

        if(map.find(pHead)!=map.end()){//如果有就不new了
            cur->next = map[pHead];
            cur = cur->next;
        }else{//没有就new了 并存到map里
            RandomListNode *tmp = new RandomListNode(pHead->label);
            map[pHead] = tmp;
            cur->next = tmp;
            cur = cur->next;
        }

        if(pHead->random){
            //寻找 map 中有没有 pHead的random
            if(map.find(pHead->random)!=map.end()){//如果有就指向
                cur->random = map[pHead->random];
            }else{//没有就new了并存到map里
                RandomListNode *tmp = new RandomListNode(pHead->random->label);
                map[pHead->random] = tmp;
                cur->random = tmp;
            }
        }
        pHead = pHead->next;

    }

    return ans->next;
}
```

- 注意第20行的`if(pHead->random)` 之前一直过不了正是由于有的节点没有random指针，为空时自然取不到label值。以后写的时候要思考全面。

- [ ] 用书上的好方法刷一次

## 27 二叉树与双向链表

先中序遍历，存到栈里。

然后再设置左右子树就很简单了。

思路好想，关键是输入为null的特殊情况我一直没处理。导致过不了。

- [ ] 书上是递归方法。
  
  ```cpp
      TreeNode* Convert(TreeNode* pRootOfTree)
      {
          if(pRootOfTree == nullptr) return nullptr;
          TreeNode* pre = nullptr;
  
          convertHelper(pRootOfTree, pre);
  
          TreeNode* res = pRootOfTree;
          while(res ->left)
              res = res ->left;
          return res;
      }
  
      void convertHelper(TreeNode* cur, TreeNode*& pre)
      {
          if(cur == nullptr) return;
  
          convertHelper(cur ->left, pre);
  
          cur ->left = pre;
          if(pre) pre ->right = cur;
          pre = cur;
  
          convertHelper(cur ->right, pre);
  ```
  
        }
  
  ```
  
  ```

## 28 字符串的排列

全排列嘛。我知道要用递归写。可是就是钻进了牛角尖。一时间想不出来递归的参数怎么设置。

- multiset是允许key相同的set

- 输入的string 为`“”`时，要特判！

- [ ] **重要的问题**   写递归的时候函数体是func(string str), 然后在函数里面把传进来的str一个临时的string变量tmp，然后改变 tmp 的值，并把 tmp 传给要递归的函数。

# 第五章 时间空间效率

## 29 绝对众数

- 之前刷LeetCode知道有摩尔投票法了。做起来很轻松。
  
  当然这题不一样的就是，可能不存在。要输出0。所以我找到后，又遍历一次判断是不是真的大于 n/2 。效率还是O(N)的

- 看书的解法。快速排序。是时候去复习一下基本的排序了。撤。
  
  ---

- 我们有成熟的O(N)算法得到数组中任意第k大的数字--》partition()

- 刚刚用Partion解法做了一遍。
  
  感觉穿参数的时候有点绕啊，比如找第k大的，坐标是k-1。
  
  然后如果一趟快拍之后的坐标 i<k，说明第k大在i后面，
  
  要传的参数就是 k-i-1;
  
  **综上，我感觉不如在数组前加一个数，放到0位置。这样第k大的数坐标就是k。其他的逻辑也清晰很多。具体是否能行我们在下一题里用一下试试**

## 30 最小的前k个数

- 先用最low的冒泡AC过了。现在开始去查资料看高端解法~
  
  - 我错了。我用的方法是比冒泡还low的，纯一个一个比较。

- vector初始化要声明空间！
  
  ---

- 用partition的写法试试~

- **事实证明，在vector的0位置加一个垃圾数。然后整个代码写起来就特别清晰了，可以完全按照思路写出：**
  
  ```cpp
  if(i==k)
      return;
  if(i<k){
      partition(vt,i+1,jj,k-i);
  }else
      partition(vt,ii,i-1,k);
  ```
  
  > 如果不在0位置加垃圾数。i就要和k-1做比较，而且k-i那里要写k-i-1

---

- 输入的k比n还大的时候，要返回空😂

- [ ] 解法二没看哈~有空回来补

## 31 最小连续子串

- 先用了暴力（其实可以优化

- 看书，又用了DP。
  
  ---
  
  代码写起来都挺容易的。

## 32 整数中1出现次数

- 暴力过了。

- [x] 明天去看书上怎么解的。

- 书上解法看懵了，搜到这篇博客，不错https://blog.csdn.net/yi_afly/article/details/52012593

## 33 把数组排成最小的数

我自认为自己思路不错，把每个数字用`'9'+1`这个字符（就是`:`）补齐，这样每个数字就会变成这样的：

`3::`  `32: `  `321`

这时候再比较这3个string，自然是321最小了。因此先插入321。

---

- 输出ans的时候。要删掉ans里的：。下面看一下string的erase方法：

```cpp
int main()
{
    std::string s = "This is an example";
    std::cout << s << '\n';

    s.erase(0, 5); // Erase "This "
    std::cout << s << '\n';

    s.erase(std::find(s.begin(), s.end(), ' ')); // Erase ' '
    std::cout << s << '\n';

    s.erase(s.find(' ')); // Trim from ' ' to the end of the string
    std::cout << s << '\n';
}
```

> 我就不明白最后两种用法。都是传入的一个迭代器。为啥一个是删除迭代器所指的字符，一个是删除迭代器后的所有字符呢？
> 
> 经测试，直接传一个迭代器进去。也是删除这个字符。

答：string::find()函数返回的是postion。是一个Int坐标。

​    而std::find()返回的是迭代器。

---

提交到OJ发现。我的思路有问题啊。如果是用更大的字符来补齐。

遇到这种情况： `3`和`34` 本来应该先插入3再插入34。

但是我把3补齐成了`3：`  导致先插入的是34~

行不通。

---

写了个比较两个字符串大小的方法。AC了。方法就是，两个不一样长的字符串，把短的用其最后一位数补齐。

比如 3和 342. 就把3 补齐成333.  333<342 。插入333.

可我这个方法，需要比较N<sup>2</sup>次。走起，看书。

---

书上，比较两个字符串大小。原来只要两个字符串拼接一下（长度就一定一样了）。返回小的就可以了。

- 书上方法固然更好，写起来也更轻松。然而我竟然发现我刚刚的用最后一位补齐的方法，时间和空间效率都比后来改的方法好啊~哈哈哈

## 34 丑数

```cpp
int a[n];
a[0 ] = 1;
int i = 1, t2 = 0, t3 = 0, t5 = 0;
while (i<n){
    int newValue = min(min(a[t2]*2,a[t3]*3),a[t5]*5);
    a[i++] = newValue;
    while (a[t2]*2<=newValue)
        t2++;
    while (a[t3]*3<=newValue)
        t3++;
    while (a[t5]*5<=newValue)
        t5++;
}
```

## 35 第一个只出现一次的字符

- map里存的顺序并不是按你存入的顺序。而是字典序。比如`g`先进入map，e后进入map。但是`e`会放在`g`前面。

- 用map做挺容易。并没有从这题学到啥呢。

- [ ] 相关题目记得回看

## 36 数组中的逆序对

**本书中遇到的第一道难题。MARK**

- 拿到题先思考：逆序对我记着是组成原理的时候学的来~干啥用来着？

- [ ] 为什么要模1000000007？

---

- 简单搜一下。https://www.e-learn.cn/content/qita/999143
  
  知识点：**归并排序、线段树、树状数组**
  
  先看这文章吧：https://mudrobot.blog.luogu.org/zong-ni-xu-dui-kai-shi-post
  
  知识点：**线段树、离散化、动态开点**

- 学了下线段树，真的强大。需要去新开一篇博客写啦~

- 归并法做，过50%. 看来过不了10^5

## 37 链表的公共节点

- [x] 这是为什么？
  
  ```cpp
  ListNode* p1=pHead1,p2=pHead2;//这样就会报错no viable conversion from 'ListNode *' to 'ListNode'
  ```
  
  因为p2前要加`*` （不然的话其实Clion会有💡自动提示让你分开定义）

- 没判断可能不存在公共节点的问题。shit。题目这样说根本就是一定存在啊。坑爹~

- 又没判断传进两个空指针的情况

- 我虽然AC了。但是我是用【环】的特性做的，就是两个链表有公共节点，那么两个指针一直往下遍历，一定能相遇。我自以为我的方法很好，其实，效率弱爆了。LeetCode试了下排倒数。380ms多。而在牛客4ms。说明啥？说明牛客不准？不，再一次说明牛客的测试用例，考虑到的情况少，用例个数少，虽然算法辣鸡但是一样很快就跑完了。以后不要信牛客。

- [ ] 重刷标记。（这题还是按书上的，统计出两个链表的长度，再根据小的开始同时遍历效率高。）

# 第六章 各项能力

## 38 排序数组中出现的次数

二分查找 easy

## 39 二叉树深度

递归写 easy 但写法其实很有技巧。对比一下便知：

我的Answer

```cpp
void TreeDepth(TreeNode* rt,int depth,int &max){
    if(rt)
        depth++;
    else//防止rt为空还继续往下走。走到rt->left肯定出事
        return;
    if(depth>max)
        max = depth;
    if(rt->left)
        TreeDepth(rt->left,depth,max);
    if(rt->right)
        TreeDepth(rt->right,depth,max);
}
int TreeDepth(TreeNode* pRoot)
{
    int ans =0;
    TreeDepth(pRoot,0,ans);
    return ans;
}
```

我用了一个辅助函数来写入max的值。但其实，看我之前在LeetCode的提交答案：

```cpp
int maxDepth(TreeNode* root){
    if(!root)
        return 0;
    else{
        int leftDepth = maxDepth(root->left)+1;
        int rightDepth = maxDepth(root->right)+1;
        return std::max(leftDepth,rightDepth);
    }
}
```

不光没借助辅助函数来写入。还清晰明了，层层递归完成。虽然两种写法，思路一样，就是递归来统计完成（提交后效率也完全一样）**但是**， 其实是 思想出了问题。下面的写法能看出”分治“的思想。就是，**分别查找左右子树的最大深度**，并返回。而上面的写法，只是单纯的递归遍历思路。

## 39-2判断平衡二叉树

- 判断左右深度。延续上题。
  
  看书：我直接延续上题的方法，有缺陷。

- 改进：就是在遍历的同时随时进行判断当前的节点平衡不。如果不平衡就提前返回False。
  
  > 就是说，直接判断左右深度的方法，辣鸡就辣鸡在，他是从上往下的遍历。不能在第一时间发现不平衡的情况，需要**遍历到最下面那层不平衡的层**才知道返回false。而改进就是改成了后序遍历~ Over
  
  写了一下发现，逻辑上还有细节主要注意。
  
  - [ ] 重刷标记

## 40只出现一次的数字

位运算啊~相当弱的环节。要好好总结。

> 做了这题，位运算有了点理解

### **需要特别注意的！**

**在写 & | ^这种位运算的运算式的时候，一定要加括号！因为它们的优先级很低。不加括号运算顺序会完全和你想的不一样🙃**

本题的主要过程都记录在了代码注释里：

```cpp
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    int all=0;
    for(int x:data)
        all ^= x;//all是全部异或的结果

    //找到x第一个是1的位（这个位就是 num1和num2 在此位不同所致
    int i=0;
    while (!(all&1)){// &1 就是只保留这个数的最后一位
        all = all>>1;
        i++;
    }
    for(int x:data){
        if((x>>i)&1)
            *num1 ^= x;
        else
            *num2 ^= x;
    }
}
```

## 41-1和为S的连续序列

- Clion真强啊。我的代码本来这样：
  
  ```cpp
  if((x&1)==0)
      return true;
  return false;
  ```
  
  提示，1，可以简化。2，`x==0`最好写 `0 == x`  3，if(a==b)return true; 建议改成 if(!=)return false; 为啥？
  
  最后改成了`return (x & 1) == 0;`

- ~~开始没考虑输入1的情况。但是我自己分奇数偶数做的，牛客AC了。~~
  
  我自己用的辣鸡方法不要再看！
  
  书上介绍的是尺取法。
  
  尺取法过不了LeetCode 829.因为LeetCode输入数据规模大。必须寻找一个Log_n算法

- [ ] LeetCode标记，参考文章。https://blog.csdn.net/curry3030/article/details/80701612

## 41-2和为S的两个数

水题。

- 我真的太天真了。觉得让我返回两个数，就一定存在。。。可是，你用例中不存在的情况不是在欺骗我吗？？？😤
- 所以说嘛，不论什么时候，边界、特例都要考虑！这才是好的习惯。

## 42循环左移

Easy。

## 42-2翻转单词顺序

- 题倒是简单。光在这处理特殊情况了。
  
  输入都是什么玩意啊，`""` `" "` 这样有意思吗？

- 恶心这道题

## 43n个骰子的点数

牛客没这题？

- [ ] 这题没刷，看书后不想看也。标记。

## 44扑克牌顺子

- 我是不是傻子。竟然想直接遍历一次然后判断是不是顺子。
- 轻松AC

## 45约瑟夫环

- 自己模拟遍历过的。效率差

- [ ] 记得刷书
  
  公式法的推导，已写[独立文章](https://o--o.win/Algorithm/josephus/)

## 46特殊法求1-n的和

自己是绞尽脑汁也没想出来，看书了。

- 用方法1、2刷了一遍

- [ ] 下次再刷，完全不看书，方法1、2自己还能想出来吗？

- [ ] 记得回头还要用方法3、4刷一遍

## 47不用+-*/做加法

```cpp
int Add(int num1, int num2)
{
    int a = num1^num2; //第一步异或
    int b = num1&num2;
    b = b << 1;  //第二步进位
    if(b==0)
        return a^b;
    else
        return Add(a,b);
}
```

## 48不能被继承的类

- 牛客没有此题

- 常规解法：把构造函数设为私有。
  
  书中说，这样的类，只能得到位于堆上的实例，而得不到位于栈上的实例。
  
  堆，和栈。到底是什么关系呢？
  
  > 大体搜了下。三言两语说不清了。开一片文章记录下吧。
  > 
  > [关于堆和栈](../DeferencesbetweenStackandHeap)

- 关于这道题，解法二。我还是懵懵的

# 第七章 案例

## 49字符串转数字

没啥意思。

- 不过在考虑周全这方面。我也是有欠缺的。比如，输入“” “+” “-” 等无效输入时。我都没做处理的。

## 50树中两节点的最低公共祖先

- 牛客无

# 第八章

## 51数组中的重复数字

过的有点简单啊~有空看书上咋说的吧。继续下一题了。

- 书上果然提供了 O(1) 的算法
- 

## 52构建乘积数组

用线段树做，还挺容易的。不过看这题通过率这么高，应该不用这么复杂。所以记得去看书上怎么做。

- [ ] 刷书
  
  哪里用得上线段树这么复杂的结构啊。一个矩阵就搞定的事 。

## 53正则匹配

难。不会。

## 54字符串是不是个数字

疯狂嵌套if。AC。没技术含量？？？

## 55字符流中第一个不重复的字符

map做有点过于Easy了。

## 56链表环入口

看了书才做出来的。

## 57删除链表重复节点

对应LeetCode82.

~~虽然主要逻辑没问题。~~

但是真的，AC得太艰难了。指针动不动就越界了。哎！

- 再看看LeetCode上人家的思路。啥也别说了：

- [ ] 重刷标记

## 58二叉树的中序下一个节点

想清楚就去写了。轻松AC。不错哦。考虑得挺全。

## 59判断二叉树对称

递归Easy过

- [x] 书上方法不错。记得刷
  
  然后发现。书上代码和我自己写的一模一样啊

## 60-61层序遍历

Easy

关于层序遍历，我自认为我的写法逻辑更清晰（引入一个int变量表示第几层）。但是有机会的话还是再实现一下书上的写法吧。

## 62序列化

先吐槽一下牛客的题目描述吧。

太辣鸡了。

如果不是看了书，谁会知道你的序列化是让我用「前序遍历」来做？而且我在刷题的时候，肯定不可能先去看答案啊。

马上刷完牛客的剑指Offer了。体验感真的差。刷完赶紧回LeetCode。

## 63二叉搜索树的kTh

翻书不小心看到“中序遍历”几个字。这题就。。。水过去了~

> 后悔看到 555

## 64数据流的中位数

就用了最普通的二分查找做的。（而且我二分查找写得好不好还不确定）

**Note：**

```cpp
double func(int a, int b){ //输入，5，6
    return (a+b)/2;  //这么写返回的还是Int，输出5
    return (double)(a+b)/2;  //这么写才行。输出5.5 
}
```

- [ ] 看书咋说的

## 65滑动窗口

题目类型写着：栈、队列。。。

我还能说什么呢？？？都提示成这样了。我真的不该多看一眼啊！

## 66矩阵中的路径

没看书就自己做出来了。😝。

注意几个地方：

```cpp
if(i<0||j<0||i>=(int)vt.size()||j>=(int)vt[0].size())
//这里如果不加(int) clion不报错。 
//牛客报：warning: comparison of integers of different signs: 'int' and 'size_type' 因为.size()不是int型值
```

```cpp
bool hasPath(vector<vector<char > > vt,char* str,int i,int j){
    if(*str=='\0')
        return true;
    if(i<0||j<0||i>=(int)vt.size()||j>=(int)vt[0].size())
        return false;
    if(vt[i][j]!=*str)
        return false;
    if(vt[i][j]==*str){
        vt[i][j]='\0'; //让这一格子失效
        //往4个方向遍历
        return hasPath(vt,str+1,i,j+1)||hasPath(vt,str+1,i,j-1)||hasPath(vt,str+1,i+1,j)||hasPath(vt,str+1,i-1,j);
    }
    return false;
}
//看13行。本来我没写 return false. clion不报错
//牛客报，没有返回值。确实，如果不写上那么一句，就有”危险“
```

```cpp
if(*str==*matrix){
    vector<int > tmp2;
    tmp2.push_back(i);//横坐标存入
    tmp2.push_back(j);//纵坐标存入
    xy.push_back(tmp2);//(x,y)存入
}
//这里。我本来把tmp2声明到了外层。
//导致如果这一层里能找到两个匹配坐标。4个数字就会都存到 tmp2 里。
```

- [ ] 我并没有用回溯。就是四个方向全递归的。记得看书上做法~
