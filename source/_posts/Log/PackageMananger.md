---
title: PackageMananger相关
date: 2018-10-15 11:20:20
categories: Log
tags: [Note,Homebrew,Ruby,CocoaPods,npm]
---

Homebrew,Ruby,CocoaPods,npm使用时遇到的的命令、更换源、出现的问题，简单记录

<!---more--->
# Homebrew

## 概念

- Mac的软件包管理工具，类似于linux的`apt-get`，能在mac中方便地安装软件或者卸载软件。

## 安装Homebrew

### 安装

- Homebrew依赖xcode和其Command Line Tools。

  1. 在App Store中安装最新版本的xcode；
  2. 执行`xcode-select --install`安装Command Line Tools。

- 把Homebrew安装到`/usr/local`。

  ```
  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  ```

### 卸载

```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/uninstall)"
```

### 重装

1. 备份`/usr/local/Cellar`。

2. 删除Homebrew相关文件。

   ```
   cd /usr/local
   sudo rm -rf Library .git .gitignore bin/brew README.md share/man/man1/brew
   sudo rm -rf Homebrew
   sudo rm -rf ~/Library/Caches/Homebrew
   ```

3. 卸载Homebrew。

   ```
   ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/uninstall)"
   ```

4. 安装Homebrew。

   ```
   /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
   ```

5. 将第1步中的备份拷贝回`/usr/local/Cellar`。

6. 更新Homebrew及其管理的各软件。

   ```
   brew update
   brew upgrade
   brew cleanup
   ```

7. `brew doctor`检测Homebrew潜在问题，并自行排错。如使用`brew link 软件名`将备份的软件重新symlink到Homebrew上。

## 使用

### 安装软件

`brew install 软件名`，如`brew install git`。

### 卸载软件

`brew uninstall 软件名`，如`brew uninstall git`。

### 查找软件

```
brew search 查询内容
```

1. 普通查询，`brew search git`
2. 正则查询，`brew search /gi*/`

### 升级软件

- `brew upgrade 软件名`：更新指定软件，如`brew update git`。
- `brew upgrade`：更新所有软件。

### 清理软件

- `brew cleanup -n`：查看哪些软件包要被清除。
- `brew cleanup 软件名`：清除指定软件包的所有老版本。
- `brew cleanup`：清除所有软件包的所有老版本。

### 关联软件

- `brew prune`：清理无用的symlink，且清理与之相关的位于`/Applications`和`~/Applications`中的无用App链接。

- `brew link 软件名`：将指定软件的安装文件symlink到Homebrew上。

  > `brew install`安装的软件会自动执行link操作；
  > DIY安装的需要手动执行link操作；
  > 加上`--overwrite`选项，会先删除旧的symlink，再进行新的link操作。

### 信息查询

- `brew -v`：查看Homebrew版本号。
- `brew list`：列出已安装的软件。
- `brew home`：用浏览器打开homebrew官网。
- `brew info`：显示软件信息。

### 其他操作

- `brew update`：升级Homebrew自身。
- `brew doctor`：检测系统中与Homebrew有关的潜在问题。

## 疑难杂症

### 清除 HOMEBREW 缓存

`brew cleanup` 命令会删除旧版 `cellar`，以及所有 `brew` 缓存。

(`man brew`可以查看手册)

### 文件权限问题

- `/usr/local`权限问题：

  1. 打开Finder；
  2. 前往文件夹`/usr`；
  3. 右键文件夹local，点击显示简介；
  4. 给当前用户添加对`/usr/local`的读写权限

- `/usr/local/share`权限问题：

  ```
  sudo chown -R $(whoami) /usr/local/share/
  ```

# Ruby

## ruby gem源更换国内源

`gem sources -l`

`gem sources --add https://gems.ruby-china.org/ --remove https://rubygems.org/`

更新缓存
`gem sources -u `

# npm

Linux下安装nodejs：

官网找已经编译好的文件，选择好对应的linux版本下载即可，简单说就是解压后，在bin文件夹中已经存在node以及npm，如果你进入到对应文件的中执行命令行一点问题都没有，不过不是全局的，所以通过建立软链接的方式将这个设置为全局就好了。

```shell
wget http://nodejs.org/dist/latest/node-v10.11.0-linux-x64.tar.gz 

tar  xf node-v5.10.1-linux-x64.tar.gz -C /usr/local/

cd /usr/local/

mv node-v5.10.1-linux-x64/ nodejs

ln -s /usr/local/nodejs/bin/node /usr/local/bin

ln -s /usr/local/nodejs/bin/npm /usr/local/bin
```

npm 每次都要 sudo：

```shell
sudo chown -R $(whoami) ~/.npm
```

## 基本操作

全局安装的方式：`npm install -g 模块名称`

## **利用npm删除包**

删除模块其实很简单：

### **删除全局模块**

`npm uninstall -g <package>` 利用npm

### **删除本地模块**

`npm uninstall 模块`

删除本地模块时你应该思考的问题：**是否将在package.json上的相应依赖信息也消除？**

**npm uninstall 模块**：删除模块，但不删除模块留在package.json中的对应信息

**npm uninstall 模块 --save** 删除模块，同时删除模块留在package.json中dependencies下的对应信息

**npm uninstall 模块 --save-dev** 删除模块，同时删除模块留在package.json中devDependencies下的对应信息

## npm install提示没有package.json

## 解决方法：

首先，初始化项目，一路回车就行

```bash
npm init -f
```

`-f`表示force的意思，不加这个，npm会让你输入一堆信息，比如name、version之类，如果只是做做实验小demo，直接`-f`，npm帮你初始化package.json，并填充各种默认值，省事。

接着安装依赖

```bash
npm install formidable --save
```

`--save`表示将安装的包加入依赖列表的意思，可以看下package.json 里的`dependencies`字段。后面再运行 `npm install`，就会把所有依赖安装下来。如果不加`--save`，什么都不会安装。

## 淘宝 npm 镜像

`npm config set registry https://registry.npm.taobao.org`

不想用他们的，再设置回原来的就可以了：
`npm config set registry https://registry.npmjs.org`

# /usr/bin/env: node: No such file or directory

解压完成node.js 之后，通过npm命令安装grunt-cli会出现没有对应文件夹的错误

```
/usr/bin/env: node: No such file or directory
1
```

解决办法：
创建一个软连接将自己的node的执行文件指到/usr/bin/node上：

```
ln -s %node的解压目录%/bin/node /usr/bin/node
1
```

原理（若有错误请指正）：
env是一个脚本解释器，bin目录下无该文件，将查找环境变量的配置，也没有。将node指向bin文件夹后，env将会可以执行node脚本文件。