---
title: Git笔记
date: 2018-1-1
categories: Log
tags: [Git,Note]
---

Git肯定不是看一本书去一次学会的，而是先掌握了最基础的命令后，在一次次地遇到各种要应对的情况时去查文档解决。解决了问题当然要记一下咯，于是就有了这篇文章。

<!---more--->

# 基本操作

- 回滚版本

  ```git
  git reset --hard HEAD^
  git reset --hard HEAD^^
  git reset --hard HEAD~10
  git reset --hard SHA1串(而且不需要写全就能匹配，8位就够)
  #忘记了SHA1号怎么办？
  git log #查看提交历史，以便确定要回退到哪个版本
  git reflog #查看命令历史，以便确定要回到未来的哪个版本。
  ```

- 回滚文件

  ```git
  git checkout --a.txt 
  #这样就撤销了对这个文件的修改。（注意一定要带--  不然就成了加分支）
  #如果修改后又git add .了呢？（文件已经在暂存区）
  git reset HEAD a.txt
  #git reset 命令既可以回退版本，也可以把暂存区的修改回退到工作区。当我们用 HEAD 时，表示最新的版本。 运行了上一层命令，git status看一下状态，会发现，暂存区里已经回滚。 再执行 checkout --a.txt 就把文件回滚了
  ```

- 分支

```git
git checkout -b newBranch
#-b表示创建并切换，相当于以下两条命令
git branch newBranch
git checkout newBranch
git branch #查看分支
#合并到master
git checkout master
git merge newBranch
git branch -d newBranch #删除分支
```

> 普通的`git merge`合并使用fast forward的合并模式，就是把HEAD指针指到分支commit的最新指针上了。 使用命令`git merge --no-ff -m "合并内容" newBranchName`禁用了ff，合并的时候会创建一个commit。

# .gitignore

- 所有空行或#开头的行都会被忽略；
- 可以使用标准的 glob 模式匹配；
- 文件或目录前加 `/` 表示仓库根目录的对应文件；
- 匹配模式最后跟反斜杠 `/` 说明要忽略的是目录；
- 要特殊不忽略某个文件或目录，可以在模式前加上取反 `!` 。

其中 glob 模式是指 shell 所使用的简化了的正则表达式。

- 星号 `*` 匹配零个或多个任意字符；
-  `[abc]`匹配任何一个列在方括号中的字符（这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）；- - 问号 `?` 只匹配一个任意字符；
- 如果在方括号中使用短划线分隔两个字符，表示所有在这两个字符范围内的都可以匹配（比如 `[0-9]` 表示匹配所有 0 到 9 的数字）。

下面是一个 `.gitignore` 文件例子，注释上附录有说明：

```git
*.a                    # 所有以 '.a' 为后缀的文件都屏蔽掉
# Office 缓存文件
~'$'*.docx
~'$'*.ppt
~'$'*.pptx 
~'$'*.xls

tags                   # 仓库中所有名为 tags 的文件都屏蔽
core.*                 # 仓库中所有以 'core.' 开头的文件都屏蔽

tools/                # 屏蔽目录 tools
log/*                  # 屏蔽目录 log 下的所有文件，但不屏蔽 log 目录本身

/log.log               # 只屏蔽仓库根目录下的 log.log 文件，其他目录中的不屏蔽
readme.md       # 屏蔽仓库中所有名为 readme.md 的文件
!/readme.md     # 在上一条屏蔽规则的条件下，不屏蔽仓库根目录下的 readme.md 文件
 例子中的最后两条的顺序很重要，必须要先屏蔽所有的，然后才建立特殊不屏蔽的规则
```

# Git Pull冲突问题

- 方法1 **git stash**

  ```git
  git stash 暂存本地修改
  git pull 从远程版本库拉取新的修改
  git stash pop 将暂存起来的修改合并到本地工作库，如果有冲突会有相应的提示，解决冲突并提交即可
  ```

  **Note：**
  `git stash`一般用于你在某一分支工作做了一半(还不值得做一次提交或者压根还不想提交)时，你突然想切换到其他分支做一点儿别的事。这时，用`git stash`就再合适不过了。
  stash的恢复方法：
  
  ```git
  git stash list #查看stash
  # 恢复方法一
  git stash apply #恢复，stash内容并不删除，需要用
  git stash drop #来删除。
  # 上面两句相当于下面的方法二：
  git stash pop #恢复的同时把stash的内容也删了。
  ```
  
- 方法2  Pull is not possible because you have unmerged files.
本地的push和merge会形成MERGE-HEAD(FETCH-HEAD), HEAD（PUSH-HEAD）这样的引用。HEAD代表本地最近成功push后形成的引用。MERGE-HEAD表示成功pull后形成的引用。可以通过MERGE-HEAD或者HEAD来实现类型与svn revet的效果。
解决：
1.将本地的冲突文件冲掉，不仅需要reset到MERGE-HEAD或者HEAD,还需要--hard。没有后面的hard，不会冲掉本地工作区。只会冲掉stage区。
`git reset --hard FETCH_HEAD`

2.`git pull`就会成功。


# 多个Git账号问题

- 配置账号时

  ```git
  git config --global user.name "Your Name"
  ```

  其中 --global 参数就是表示这台机器所有Git仓库都使用这个配置。

https://www.jianshu.com/p/fbbf6efb50ba

# 悟

> 一次我Clone 一个仓库后，往里加了一个abc文件，然后 `add .`  `commit`  。这时候我发现这个abc文件我搞错了。趁着还没`push` 我就删除了，然后放上正确的CBA文件又执行 `add .` `commit -m`。然后我`push`。
>
> 竟然发现，git 还是会传刚刚删除的abc文件。（传上去再删掉，执行我刚刚的两次commit）
>
> 我一看这样太慢了（那个文件很大）。
>
> 就`reset`到了第一次clone的版本。这时候我本地查看文件，发现仓库里并不是最初clone下来的样子，还是最终的带有CBA文件的样子，只不过这时候我`add .`  `commit`  `push` 就一次性完成了。

- `push`这个过程会按照你的`commit`顺序一步步来。并不是按最后一次`commit`

- github单文件最大只允许100Mb

- `reset`只清除了暂存区，如何真正恢复到想去的那个版本呢？

  ANSWER: 回滚了暂存区再用`checkout --文件名`回滚文件啊！

  ```git
  git checkout . #本地所有修改的。没有的提交的，都返回到原来的状态
  ```

---

