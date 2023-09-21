---
title: Useful Tips
date: 2018-07-25 21:04:09
categories: Log
tags: [tips,Shell,iTerm2,Markdown,Heroku]
mathjax: true
---

- 偏技术性的小姿势
- 使用一些软件中遇到的问题，记录以便下次查阅

Mac使用相关问题已单独开了[一篇文章](../MacTips)。

<!---more--->

# Shell相关

- `touch xxx.x` 新建文件

- `ls -a`查看隐藏文件包括“.”和“..” `-A`不包括“.”和“..”目录

  `-C` 按列列出文件

- 清屏: edit菜单里找。Terminal:`⌃+⌘+L` iTerm:`⌘+K`

- 删除文件：`rm -f` -f后不会给任何提示。 -i是交互式删除

  删除文件夹 -r

- 查找


## 自动运行命令脚本

shell命令写在记事本存成 1.sh

shell里运行`sh 1.sh`即可

关于需要输入密码时的交互：

```bash
ssh tester@192.168.139.218 << EOF #用 <<EOF 分割。这里就是输密码的地方
cd kurento/kurento-tutorial-java/kurento-group-call
mvn exec:java
```

## 终端走代理

参考：[让终端走代理的几种方法](https://blog.fazero.me/2015/09/15/%E8%AE%A9%E7%BB%88%E7%AB%AF%E8%B5%B0%E4%BB%A3%E7%90%86%E7%9A%84%E5%87%A0%E7%A7%8D%E6%96%B9%E6%B3%95/)

## Finder和终端快速转

- Finder到终端：拖窗口到终端界面
- 终端到Finder：`open .`

# iTerm2

## 免密码登录ssh

借助这个shell文件：

```shell
#!/usr/bin/expect

set timeout 30
spawn ssh -p [lindex $argv 0] [lindex $argv 1]@[lindex $argv 2]
expect {
        "(yes/no)?"
        {send "yes\n";exp_continue}
        "password:"
        {send "[lindex $argv 3]\n"}
}
# expect "~"
# send "clear\n"
interact
```

>   这里`[lindex $argv 0]， [lindex $argv 1]， [lindex $argv 2]， [lindex $argv 3] `分别代表着4个参数。分别是：端口号、用户名、服务器地址、密码。
>   注：`expect "~" send "clear\n"`此两行代码是登录完成后自动清除控制台信息。

文件保存到 `/usr/local/bin` 目录下， `sudo chmod 777 autoSSH.sh`给最高权限

然后添加一个iTerm2配置，开启时自动执行` autoSSH root 1.2.3.4 pwd` 就好了

## 美化&增强

- iTerm2 -> Make iTerm2 Default Term

- 配色改成这个：http://ethanschoonover.com/solarized

## 改用zsh

## zsh 安装最新版本

### 更新 zsh >= 5.4

从 https://sourceforge.net/projects/zsh/files/zsh/ 下载对应的 zsh 版本，使用如下代码编译安装：

```plain
tar -xvf zsh-5.8.tar.xz
cd zsh-5.8
./configure --prefix=/home/xxxxx/zsh-5.8 #设置安装路径
make && make install
```

`chsh -s /bin/zsh`  (默认使用bash) 

使用命令：在终端窗口中键入 `echo $0`，然后按回车键。这将显示当前正在运行的 Shell 的名称

## 添加alias

在 `.zshrc`这个文件里配置

注意例子：`alias blog="cd Documents/Hexo"`

其中`blog="xxx"`等号两边不允许有空格！不然alias会失效。


## 安装和配置**oh_my_zsh**

https://github.com/robbyrussell/oh-my-zsh

- via curl

```shell
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

- via wget

```shell
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
```

安装好了ohmyzsh之后：

### 配置主题：

修改`~/.zshrc`文件的 `ZSH_THEME=""` 属性为`"agnoster"`

0----- 建议直接搜 p10k 用这个主题

### 改字体

agnoster这个主题只认等宽字体

克隆这个仓库到本地：https://github.com/powerline/fonts.git

运行里面的 `install.sh` 就装好了字体。

然后在iTerm的设置里选一个还上就行了。

### 前缀

**路径前缀的user@MacBook太长不好看，缩短：**
**编辑`~/.oh-my-zsh/themes/agnoster.zsh-theme`主体文件，将里面的`build_prompt`下的`prompt_context`字段在前面加`#`注释掉即可**

  > 改这里学到一个小技巧：
  >
  > 由于`oh_my_zsh`时常会有版本更新，为了避免我们修改的跟更新的版本有冲突，建议不要修改`agnoster.zsh-theme`，而是将其拷贝出来，命名为自己的主题文件，比如叫做`myagnoster.zsh-theme`，然后只对`myagnoster.zsh-theme`进行修改。 
  > 2、修改后将`~/.zshrc`中的`ZSH_THEME="myagnoster"`

定制修改

```shell
prompt_segment black default "%(!.%{%F{yellow}%}.)%n@%m"
#很明显 %n是用户名 %m是机器名 
#你还可以在这里自由发挥输入你想填的内容
```

## 拓展

### 命令提示与补全

  1. `git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions`  

     > 克隆仓库到本地 ~/.oh-my-zsh/custom/plugins 路径下

  2. 编辑 `.zshrc` 文件，找到插件设置命令，默认是 `plugins=(git)` ，我们把它修改为`plugins=(zsh-autosuggestions git)`

  > PS：当你重新打开终端时可能看不到变化，可能你的字体颜色太淡了，我们把其改亮一些：

  编辑`~/.oh-my-zsh/custom/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh`文件。修改`ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE='fg=10'`

### 语法高亮效果

  1. 如果电脑上还没有安装homebrew，请先安装homebrew
     `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

     使用homebrew包管理工具安装 zsh-syntax-highlighting 插件
     `brew install zsh-syntax-highlighting`

     不是Mac就把这个地址https://github.com/zsh-users/zsh-syntax-highlighting.git clone到下面那个路径`/usr/local/share/`

  2. 配置`.zshrc`文件，插入一行
     `source /usr/local/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh`

  3. `source ~/.zshrc`(刷新加载.zshrc配置)

     或新打开一个iTerm2窗口即可以看到效果

### 其他插件

  `plugins=(z zsh-autosuggestions git d)`

  z那个是看以前cd过的目录

  


## 其他

1. iTerm2 zsh切换回原来的dash：`chsh -s /bin/bash`

2. 卸载`oh my zsh`，在命令行输入：`uninstall_oh_my_zsh`

3. 本节参考文章：https://www.cnblogs.com/kenz520/p/8259432.html

4. 出现`(base)`字样(遇到这个问题了自然懂)

   在`.zshrc`中加入：`conda deactivate`



# 卸载Adobe Creative Cloud:

官方卸载工具：

https://helpx.adobe.com/cn/creative-cloud/help/uninstall-creative-cloud-desktop-app.html


# Word

## 去掉编号前的·

修改【样式】-【段落】-这两个勾去掉就好了。![](https://0pic.oss-cn-beijing.aliyuncs.com/wordtips.png)

# PPT

- 原来PPT可以存成`.ppsx` 的格式，双击打开就直接播放（可与防止被改动



# Markdown相关

## Markdown折叠效果

<details>
  <summary>就类似这样：Click to expand</summary>
  这里不能插入Markdown了
</details>
其实就是用HTML的`<details>`标签：

```html
<details>
  <summary>Click to expand</summary>
  whatever
</details>
```

## Markdown 写上标下标

1. HTML

    ```
    <!--利用HTML-->
    <sub>上标</sub>
    <sup>下标</sup>
    ```
    例如
    `X<sub>1</sub>` ==> X<sub>1</sub>
    `Y<sup>2345</sup>` ==>Y<sup>2345</sup>

2. MathJax
MathJax不仅可以打上下标，还可以打双标。
> （1）两个符号$$中间是公式的内容
> （2）^ 符号后接的字符为上标 
> （3）_ 符号后接的字符为下标 
> （4）如果同时有两个下标，则需要使用{}来将符号括起来 

如：`$x^p_{ij}$` ==> $x^p_{ij}$



# Sublime相关

~~这几个问题怕是用过sublime的都解决过吧~记录一下防止下次碰到再百度了。~~

<details>
	<summary>我已转战 VS Code 🙂 本节内容全部折叠</summary>
  <h5>加入subl命令</h5>
<code>sudo ln -s &#39;/Applications/Sublime Text.app/Contents/SharedSupport/bin/subl&#39; /usr/local/bin/subl&#39;</code>
<h5>Sublime3屏蔽更新</h5>
<code>&quot;update_check&quot;: false,</code>
<li>Setting-User里添加<code>&quot;update_check&quot;: false,</code>
<strong>一定要带，</strong>
<strong>一定要带，</strong>
<strong>一定要带，</strong></li>
<li>再从网上找个能用的序列号：</li>
----- BEGIN LICENSE -----
sgbteam
Single User License
EA7E-1153259
8891CBB9 F1513E4F 1A3405C1 A865D53F
115F202E 7B91AB2D 0D2A40ED 352B269B
76E84F0B CD69BFC7 59F2DFEF E267328F
215652A3 E88F9D8F 4C38E3BA 5B2DAAE4
969624E7 DC9CD4D5 717FB40C 1B9738CF
20B3C4F1 E917B5B3 87C38D9C ACCE7DD8
5F7EF854 86B9743C FADC04AA FB0DA5C0
F913BE58 42FEA319 F954EFDD AE881E0B
------ END LICENSE ------
2017.7.1可用
<h5>中文乱码问题</h5>
安装<code>ConvertToUtf8</code>和<code>GBK</code>两个包
<h5>支持C++11</h5>
tools--&gt;new build sys
输入：
<pre><code>{
    &quot;cmd&quot;: [&quot;bash&quot;, &quot;-c&quot;, &quot;g++ &#39;${file}&#39; -std=c++11 -stdlib=libc++ -o &#39;${file_path}/${file_base_name}&#39;&quot;],
    &quot;file_regex&quot;: &quot;^(..{FNXX==XXFN}*):([0-9]+):?([0-9]+)?:? (.*)$&quot;,
    &quot;working_dir&quot;: &quot;${file_path}&quot;,
    &quot;selector&quot;: &quot;source.c, source.c++&quot;,
    &quot;variants&quot;:
    [
        {
        &quot;name&quot;: &quot;Run&quot;,
        &quot;cmd&quot;: [&quot;bash&quot;, &quot;-c&quot;, &quot;g++ &#39;${file}&#39; -std=c++11 -stdlib=libc++ -o &#39;${file_path}/${file_base_name}&#39; &amp;&amp; open -a Terminal.app &#39;${file_path}/${file_base_name}&#39;&quot;]
        }
    ]
}
</code></pre>
保存的时候注意后缀不要改，是<code>.sublime-build</code>
如果想调用iTerm2把里面的<code>Terminal.app</code>换成<code>iTerm.app</code>就行了。
换成iTerm之后程序执行完iTerm会自己关闭窗口，需要在设置里修改一下默认配置文件.

</details>


# Heroku

## 连接PGSQL

想给紫玉搭一个Typecho的博客，结果得用pgsql的数据库。

1. 添加环境扩展：https://elements.heroku.com/addons/heroku-postgresql
2. 添加好后点Setting可以看到数据库名啥的，正常配置即可

