---
title: 关于ssh-key
date: 2020-03-07 20:25:47
categories:
tags:
---

<!---more--->

创建密钥对：

```bash
ssh-keygen -t rsa -C  'your email@domain.com'

-t 指定密钥类型，默认即 rsa ，可以省略
-C 设置注释文字，比如你的邮箱，可以省略
```

生成过程中会提示输入密码两次，如果不想在使用公钥的时候输入密码，可以回车跳过；
密钥默认保存位置在 `~/.ssh` 目录下

> 如果不加`-t -C`参数，一直按回车。会生成
>
> -   私钥文件 `id_rsa` 
> -   公钥文件 `id_rsa.pub`

# 公钥放到服务器

## 填公钥

把公钥`.pub`那个文件内容,如

```
ssh-rsa ABCDABCD ixsim@MacBook-XS.lan
```

填到服务器的`~/.ssh/authorized_keys`文件里

## 登录

`ssh -i ~/.ssh/私钥名 root@1.1.1.1`

如果私钥当时都没改名字(就叫`id_rsa`)，则可直接

`ssh root@1.1.1.1`



