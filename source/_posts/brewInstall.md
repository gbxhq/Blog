---
title: Homebrew安装
date: 2020-11-23 22:16:21
categories:
tags:
---



<!---more--->

`Homebrew`是一款包管理工具，目前支持`macOS`和`linux`系统。主要有四个部分组成: `brew`、`homebrew-core` 、`homebrew-cask`、`homebrew-bottles`。

![img](https://pic3.zhimg.com/80/v2-e7af6f2ca9ed932aaa42c45c973299da_1440w.jpg)

本文主要介绍`Homebrew`安装方式以及如何加速访问，顺便普及一些必要的知识。

## 1. 脚本说明

`Homebrew`默认安装脚本：

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

如果你等待一段时间之后遇到下面提示，就说明无法访问官方脚本地址：

```bash
curl: (7) Failed to connect to raw.githubusercontent.com port 443: Operation timed out
```

请使用下面的脚本:

```bash
/usr/bin/ruby -e "$(curl -fsSL https://cdn.jsdelivr.net/gh/ineo6/homebrew-install/install)"
```

上面脚本中使用了中科大镜像来加速访问。

安装使用到的脚本源码在此 [homebrew-install](https://link.zhihu.com/?target=https%3A//github.com/ineo6/homebrew-install) ，仅修改了仓库地址部分，不会产生安全隐患，另外求 star 。

------

> 官方脚本无法使用的原因是[http://raw.githubusercontent.com](https://link.zhihu.com/?target=http%3A//raw.githubusercontent.com)访问很不稳定，我上面提供的方案里是采用了jsdelivr CDN加速访问。
> 另外也可以采用写入hosts的方式，可以一定程度解决GitHub资源无法访问的问题，我也写了一篇操作文章，有需要可以阅读下。

[ineo6：解决GitHub网页githubusercontent地址无法访问问题zhuanlan.zhihu.com![图标](https://pic1.zhimg.com/v2-ad9ed1bedf8fe606480686e08dac4aa4_180x120.jpg)](https://zhuanlan.zhihu.com/p/107691233)

## 2. 安装说明

```bash
/usr/bin/ruby -e "$(curl -fsSL https://cdn.jsdelivr.net/gh/ineo6/homebrew-install/install)"
```

如果命令执行中卡在下面信息：

```bash
==> Tapping homebrew/core
Cloning into '/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core'...
```

请`Control + C`中断脚本执行如下命令：

```bash
cd "$(brew --repo)/Library/Taps/"
mkdir homebrew && cd homebrew
git clone git://mirrors.ustc.edu.cn/homebrew-core.git
```

**`cask` 同样也有安装失败或者卡住的问题，解决方法也是一样：**

```bash
cd "$(brew --repo)/Library/Taps/"
cd homebrew
git clone https://mirrors.ustc.edu.cn/homebrew-cask.git
```

成功执行之后继续执行前文的安装命令:

```bash
/usr/bin/ruby -e "$(curl -fsSL https://cdn.jsdelivr.net/gh/ineo6/homebrew-install/install)"
```

最后看到`==> Installation successful!`就说明安装成功了。

最最后执行：

```bash
brew update
```

## 3. 如何卸载Homebrew

使用官方脚本同样会遇到`uninstall`地址无法访问问题，可以替换为下面脚本：

```bash
/usr/bin/ruby -e "$(curl -fsSL https://cdn.jsdelivr.net/gh/ineo6/homebrew-install/uninstall)"
```

## 4. 设置镜像方法

`brew`、`homebrew/core`是必备项目，`homebrew/cask`、`homebrew/bottles`按需设置。

通过 `brew config` 命令查看配置信息。

### 4.1 中科大源

```bash
git -C "$(brew --repo)" remote set-url origin https://mirrors.ustc.edu.cn/brew.git

git -C "$(brew --repo homebrew/core)" remote set-url origin https://mirrors.ustc.edu.cn/homebrew-core.git

git -C "$(brew --repo homebrew/cask)" remote set-url origin https://mirrors.ustc.edu.cn/homebrew-cask.git

brew update

# 长期替换homebrew-bottles
echo 'export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles' >> ~/.bash_profile
source ~/.bash_profile
```

注意`bottles`可以临时设置，在终端执行下面命令：

```bash
export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles
```

### 4.2 清华大学源

```bash
git -C "$(brew --repo)" remote set-url origin https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/brew.git

git -C "$(brew --repo homebrew/core)" remote set-url origin https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/homebrew-core.git

git -C "$(brew --repo homebrew/cask)" remote set-url origin https://mirrors.tuna.tsinghua.edu.cn/git/homebrew/homebrew-cask.git

brew update

# 长期替换homebrew-bottles
echo 'export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.tuna.tsinghua.edu.cn/homebrew-bottles' >> ~/.bash_profile
source ~/.bash_profile
```

### 4.3 恢复默认源

```bash
git -C "$(brew --repo)" remote set-url origin https://github.com/Homebrew/brew.git

git -C "$(brew --repo homebrew/core)" remote set-url origin https://github.com/Homebrew/homebrew-core.git

git -C "$(brew --repo homebrew/cask)" remote set-url origin https://github.com/Homebrew/homebrew-cask.git

brew update
```

`homebrew-bottles`配置只能手动删除，将 `~/.bash_profile` 文件中的 `HOMEBREW_BOTTLE_DOMAIN=https://mirrors.xxx.com`内容删除，并执行 `source ~/.bash_profile`。

## 5. 其他

### 5.1 cask

目前`cask`是从`GitHub`上读取软件源，而`GitHub Api`对匿名访问有限制，如果使用比较频繁的话，可以申请`Api Token`，然后在环境变量中配置到`HOMEBREW_GITHUB_API_TOKEN`。

在`.bash_profile`中追加:

```bash
export HOMEBREW_GITHUB_API_TOKEN=yourtoken
```

注意：因为`cask`是基于`GitHub`下载软件，所以目前是无法加速的。

## 6. 总结

在前面的过程中我们把`brew`和`homebrew-core`的地址都指向到中科大镜像。

原理是通过修改`install`脚本，在里面预设镜像地址来做到的。

```bash
#!/usr/bin/ruby
# This script installs to /usr/local only. To install elsewhere (which is
# unsupported) you can untar https://github.com/Homebrew/brew/tarball/master
# anywhere you like.
HOMEBREW_PREFIX = "/usr/local".freeze
HOMEBREW_REPOSITORY = "/usr/local/Homebrew".freeze
HOMEBREW_CACHE = "#{ENV["HOME"]}/Library/Caches/Homebrew".freeze
# 这里替换了BREW_REPO
BREW_REPO = "https://mirrors.ustc.edu.cn/brew.git".freeze
```

最后不完美的地方是我们只能预设`brew`镜像，没找到比较好的办法预设`homebrew-core`、`homebrew-cask`的`git`地址。

## 参考文章

- [清华大学开源软件镜像站](https://link.zhihu.com/?target=https%3A//mirror.tuna.tsinghua.edu.cn/help/homebrew/)
- [科大源](https://link.zhihu.com/?target=http%3A//mirrors.ustc.edu.cn/help/brew.git.html%23)

## 如果对您有帮助

请给我一个赞⭐️，让更多人能发现文章，这也是对我的认可和鼓励。

------

## 广告插播

`GitMaster`可以树形展示`git`项目代码。

- 代码树支持`GitHub`、`GitLab`、`Gitee`
- ️ 支持私有部署页面，一键标记
- ️ 文件提交历史可视化 `git history`
- `GitHub`通知提醒功能
- ⬇️ 支持`GitHub`文件、目录下载

![img](https://pic4.zhimg.com/80/v2-59d3a51e7c84e2a19f87ed0a8246c293_1440w.jpg)

- [Chrome Web Sore](https://link.zhihu.com/?target=https%3A//chrome.google.com/webstore/detail/git-master/klmeolbcejnhefkapdchfhlhhjgobhmo)
- [Edge Web Store](https://link.zhihu.com/?target=https%3A//microsoftedge.microsoft.com/addons/detail/pcpkfgepcjdmdfelbabogmgoadgmiocg)

------

> 本文首发博客: [mac下镜像飞速安装Homebrew教程](https://link.zhihu.com/?target=http%3A//idayer.com/mac-install-homebrew-by-cdn/)

[http://weixin.qq.com/r/1XVlfVnEGQRmrR0e9yDH](https://link.zhihu.com/?target=http%3A//weixin.qq.com/r/1XVlfVnEGQRmrR0e9yDH) (二维码自动识别)