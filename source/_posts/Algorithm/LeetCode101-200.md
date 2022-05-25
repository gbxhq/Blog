---
title: LeetCode 101-200
date: 2018-09-06 14:30:53
categories: [Algorithm]
tags: [Cpp,LeetCode,Algorithm]
---

知识点：  `摩尔投票算法`[169]   `reverse()的理解`[189]     `位运算`[136](#136只出现一次的数字)   `string.erase()`[171]     

<!---more--->

# 101.对称二叉树

- 开始写成了判断节点的两个孩子是否相同。完全整错了题。

- 用两个前序遍历把结果存到vector里。一个先遍历左孩子，一个先遍历右孩子。然后比较两个vt相同。

  - Problem，空节点的时候，不会存入vector，导致一些情况判错。解决方法：空节点存入-9999

- 正经的解法：

  ```cpp
   bool symmetric(TreeNode* left, TreeNode* right)
  {
      if (!left && !right)
      {
          return true;
      }
      if (!left || !right)
      {
          return false;
      }
      return left->val == right->val && symmetric(left->left, right->right) && symmetric(left->right, right->left);
  }
  bool isSymmetric(TreeNode* root) 
  {
      if (!root)
      {
          return true;
      }
      return symmetric(root->left, root->right);
  }
  ```

# 107二叉树的层次遍历 II

# 121/122 买股票1 买股票2

- 121：比较简单。但我第一次用的O(n2)。显得很没水平。只要记录最小值和最大值就可以了。不需要两层循环遍历的。
- 122：有了上一题的启发。很快解决。（本来想半天）

# 141环形链表

> 知识点：如果有环，快慢指针一定会相遇。可用递归法证明。

# 136只出现一次的数字

高端操作：位运算

- 延伸阅读：https://blog.csdn.net/bitboss/article/details/51594037
  - [ ] 进阶1： **一个数组中，只有一个数字出现了一次，其他数字都出现了三次，找出这个出现了一次的数字；**
  - [x] 进阶2：**<百度面试题>：在一个数组中，其他元素都是成对出现，只有两个数字只出现了一次，找出这两个数；** 剑指offer#40。已刷

# 151最小栈

- 可以用`*(vt.end()-1)`的方式取到vector的最后一个元素啊。

# 两个数组的交集 II

关于map的遍历：

- 如果输入的map下标不存在则会创建这个下标。
- map.find()是查的关键字

# 160 相交链表

我用了一个set保存A的每个地址。

然后对着B进行set.find()。过。关闭输入输出同步之后效率从29升到87~哈哈。

# 168 EXCELL表列名

就是输入1输出A 输入28输出AB

- 注意输入26时，余数为0。这种情况需要特判。

  输入26时。n的循环也会多走一圈。需要特判。不然输入26会输出ZA。

- 每轮循环结束是 `n = n/26` 还是` n = n-26` ?    请思考清楚

# 171和168相对

`string.erase(pos,len)`,从pos位置开始删除len个字符。len缺省则删除到末尾。返回string的一个引用。

比如`str.erase(str.size()-5,5);` 删除了后5个字符。注意是.size()-5 。就是用下标来控制的。

我个人更喜欢用` str = str.substr(pos1,pos2)`这种方式删除

# 169绝对众数

- 用map做感觉是水题。

但是在别人的解法里学到了摩尔投票算法：

> 首先请考虑最基本的摩尔投票问题，找出一组数字序列中出现次数大于总数1/2的数字（并且假设这个数字一定存在）。显然这个数字只可能有一个。**摩尔投票算法是基于这个事实：每次从序列里选择两个不相同的数字删除掉（或称为“抵消”），最后剩下一个数字或几个相同的数字，就是出现次数大于总数一半的那个**。

- 继续延伸：1/k众数

Ex:k=3。求1/3众数。注：这样的数可能不存在

```cpp
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <iterator>
    using namespace std;

    void FindMode(const int *a, int size, vector<int>& mode){
    int m,n;//候选值
    int cm = 0, cn = 0;//候选值m、n的个数
    int i;
    for(i=0; i<size; i++){
        if(cm == 0){
            m = a[i];
            cm = 1;
        }else if(cn == 0){
            n = a[i];
            cn = 1;
        }else if(m == a[i]){
            cm++;
        }else if(n == a[i]){
            cn++;
        }else{
            cm--;
            cn--;
        }
    }
    //↑ 运行到此处时的m、n一定是众数，同时也是可能存在的1/3众数。
    
    cm = cn = 0;//为确保一定存在（因为1/3众数可能不存在），一定要重新遍历统计出现次数
    for(i=0; i<size; i++){
        if(m == a[i]){
            cm++;
        }else if(n == a[i]){
            cn++;
        }
    }
    if(cm > size/3){
        mode.push_back(m);
//        cout<< m<<" ";
    }
    if(cn > size/3){
        mode.push_back(n);
//        cout<< n<<" ";
    }
    
}

void Print(vector<int> vector){
    for(int i=0; i<vector.size(); i++){
        cout<< vector[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int a[] = {8,1,1,8,1,1,6,1,5,8,8};
    vector<int> mode;
    FindMode(a, sizeof(a)/sizeof(int),mode);
    Print(mode);
    return 0;
}
```

# 172阶乘后的零

- 13的阶乘就已经超INT范围了。用了`long long`型之后，它给我输入了个30🙂🙂🙂

  思路有问题🙃

- 找到了规律。其实有几个零就是和因子里有几个5有关系。所以遇到 5、25、125、675~这种要处理，可是刁钻的问题出现了。测试用例给了一个1808548329。5的13次方是1220703125。我的算法可以给出答案。但是超时了。后面还有个过不了的用例2147483647。就是INT_MAX呗。超时了。我直接特判了这两个过的。

- 结果发现0ms的答案只有这么几行：

  ```cpp
  int trailingZeroes(int n) {
      long long sum=0;
      for(long long i=5;i<=n;i=i*5)
          sum=sum+n/i;
      return sum;
  }
  ```

这时候再回头看一下我自己写的【超时版】答案。其实不就是一个意思吗：

```cpp
int ans = n/5; //先除以5
for(int i=2;pow(5,i)<=n;i++){ /*小于25的时候。
里面每有一个25就++(这不就是m/pow(5,2)吗？
我傻不拉几的在那用循环判断每次ans++)*/
    int tmp = n;
    while(tmp>=pow(5,i)){
        ans ++;
        tmp -= pow(5,i);
    }
    cout<<i<<endl;
}
return ans;
```

# 189旋转数组

- 开始想用一个临时数组存原来的数。然后根据需要copy。

  结果发现人家让空间复杂度O(1)原地完成。

- 想到了多次Reverse的方法。这个思路还是很清晰的。以下两点需要注意：

  - 如vt的内容是 1 2 3 4 5 6 7

    `reverse(vt.begin(),vt.begin()+3)`执行后，反转的就是前三个数。变成：

    `321  4567`

    虽然`vt.begin()+3`已经指向了`4`这个元素。

    这也可以解释为什么` reverse(vt.begin(),vt.end())`在end()指向空的时候，为什么可以翻转整个vector。

    -->四个字：**左闭右开！**

  - 输入的位移量大于数组长度的情况要考虑到，取余即可。（怕的是想不到）

# 283移动零

输入 0 1 0 3 2

输出 1 3 2 0 0 

- 注意，用迭代器it控制，vt.erase(it) 时，删除了it指向的元素，且it会指向下一个it。
- 出现的问题：
  - 开始我只用迭代器来控制遍历，当迭代器为end时终止遍历，没考虑到，我会不停地在vector尾部push_back(0)，这样遍历永远都不会结束。

# 206 反转链表

我用递归做的。

思路是，把第一个节点取出来。然后从第二个开始反转，反转的结果再接上第一个节点。

## Problems

开始我取第一个节点是直接一个指针指向head。这样虽然取到了。但是这个节点的next不是NULL啊。而是2号到最后。

后来用的方法是new一个新的空间。（相当于是取出来了第一个节点的**值**吧）

然后再把后面的反转之后，接上这个new的节点。

## 解

```
ListNode* reverseList(ListNode* head) {
	if(head == NULL)//输入竟然有空的情况。不得不加这么一个判断。
		retrun head;
    if(head->next == NULL){
        //这里也要声明新的节点。不然又是原来的头地址，串起来了。
        ListNode *p = new ListNode(head->val);
        return p;
    }
    else
    {
        ListNode* p = new ListNode(head->val);
        ListNode* tmp = reverseList(head->next);
        //要把 头部 预存一下。不然下面的while就让tmp走到尾部了。
        ListNode* ans = tmp;
        while(tmp->next){
            tmp = tmp->next;
        }
        tmp->next = p;
        return ans;
    }       
}
```

要点就是我备注的两个地方了。

但是我这个写法。光顾着递归了。效率是排行倒数。人家第一的递归写法：

```cpp
if(head==NULL||head->next==NULL)
    return head;
ListNode *res=reverseList(head->next);
head->next->next=head;
head->next=NULL;
return res;
```

这就是另一个境界的思想问题了。

他的解法也是把第一个取出来。把后面的反转了接上第一个。

**但是**，人家是在地址上操作的。我是新开辟空间的。

直接把两个一组。`head->next->next=head;`这句是精华。

然**2号**的下一个变成**1号**，再让**1号**的下一个变成null。成功调换1-2的位置为2-1-null、

而**2号**其实在上一次的递归中，已经被它的上一个3号所指向。即3->next就是2号、

> 启发。递归的时候可以倒着思考问题。
>
> 思路是把第一个拿出来。再把剩下的做reverse()处理后返回。
>
> 返回的时候返回的就是**已经反转完成的链表的头**。别想别的。
>
> 思考最后递归的倒数第二层是什么情况（比如这题就是还剩俩节点）。


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

# 707设计链表

不想做😛😛😛

【链表+简单】刷完~

# 876 链表的中间节点

简单。计数器判断。

