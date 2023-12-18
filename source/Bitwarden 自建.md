# Bitwarden 自建

不得不说，移动的网络真不太行，同步 bitwarden 经常因为网络问题同步失败。

那就自建一下吧。反正小鸡性能也是过剩。

## 方案调研

目前有两种方案

- 一个是 bitwarden 官网的自部署：

    [Self-host an Organization | Bitwarden Help Center](https://bitwarden.com/help/self-host-an-organization/)

- 一个是同源项目 [Vaultwarden](https://github.com/dani-garcia/vaultwarden) 进行自搭建
  
  Vault­war­den 原名 Bit­war­den_RS，是用 Rust 语言实现的 bit­war­den api，实现了 bit­war­den api 的完整功能，同时支持使用 [Docker](https://hub.docker.com/r/vaultwarden/server) 方便地进行部署。

### 方案一踩坑

这里我开始不知道有下面这种，直接照着官网的方法部署的。倒是很简单。脚本都是交互式的，一键就能全部搞定。

但这个方法有个缺点。就是真的有点吃配置。

完全部署好后，要起10来个 docker 容器，这倒无所谓。关键跑起来之后，我的性能被稳定吃了20%(4c4g)以上。这里面有很多不必要的步骤，比如 mysql，其实我宿主机本身就安装了，没必要再起一个 docker 部署mysql。于是，我把这套删掉，改用了更轻量的方案二。

### 方案二

贴一个教程，我感觉这里写的已经非常详细：[自搭建全平台私有密码库 bitwarden & Vaultwarden - OttoLi 的胡言乱语](https://www.ottoli.cn/howto/bitwarden-vaultwarden)

部署也很简单，docker 一键，这里我贴一下我配好的 compose：

```
version: '3'

services:
  vaultwarden:
    container_name: vaultwarden
    image: vaultwarden/server:latest
    environment:
      - ADMIN_TOKEN=123456
      - RUST_BACKTRACE=1
      - DATABASE_URL=mysql:// root: passwd@172.17.0.1:3306/bitwarden?charset=utf8mb4&parseTime=True&loc=Local
    volumes:
      - /www/wwwroot/bit.abc.com/:/data/
    ports:
      - 5555:80
```

解读：

- ADMIN_TOKEN 后台的密码, /admin 可以进入管理页面

- DATABASE_URL 链接MySQL的配置，这里注意，172.17.0.1是宿主机在 docker 的 ip，这个 docker 第一次启动，应该是没有权限访问数据库的（除非你数据库放行所有 IP 那当我没说），这时候你看 docker 日志也会告诉你连不上数据库。
  
  需要授权一下容器的 IP：
  
  ![](https://pic.oo1.win/i/0/2023/12/18/y0x29x-0.png)

- volumes 一定记得，要把磁盘外挂出来，方便做备份。

其他的内容。我直接把楼上那个大哥写的抄过来了：

### **Vaultwarden 管理后台**

访问 `your.domain/admin`，登录 Vault­war­den 管理后台，登陆密码为刚刚设置的 `ADMIN_TOKEN`

![](https://www.ottoli.cn/wp-content/uploads/m2x136-0.webp)

在这里可以根据情况对 Vault­war­den 进行一些可选设置，所有的设置项都可以通过鼠标悬停查看相应的说明，不了解的项目建议保持默认

这里介绍几个我认为值得关注的设置项：

- Gen­eral Set­tings
  - Domain URL：设置你的网站域名，记得带上 https，如 `https://your.domain`
  - Allow new signups：是否允许用户注册，如果密码库仅仅用于自用，建议在自己注册后关闭此选项
  - Admin page token：在这里更改 Vaultwarden 管理后台的密码
  - Invitation organization name：设置你的网站名字，将出现在自动发送的电子邮件中
- SMTP Email Set­tings
  - 设置 SMTP 服务，用来发送系统邮件（建议开启）
  - 根据你的 SMTP 服务提供方填写相关信息即可
    - 设置保存后，运行一次 Test SMTP 确保邮件可以正常发送
- Read-Only Con­fig
  - 这里可以查看所有只读选项，可以停止 docker 容器后通过编辑 `'docker映射本机目录地址':/data/` 目录中的 `config.json` 修改
- Backup Data­base
  - 这里提供了一个简易的数据库备份功能，不过我们稍后会介绍全面的备份流程

### **开始使用**

必要的设置完成后，访问 `your.domain` 创建你的密码管理账户

![](https://www.ottoli.cn/wp-content/uploads/md287y-0.webp)

在这里设置 `主密码`，同时可以选择设置一条主密码提示，当你忘记主密码时，可通过邮件获取主密码提示

注意：千万不要设置与主密码关联性太强的主密码提示，因为当你的邮箱账户被盗用时，所有人都可以获得你的主密码提示！

## 备份/恢复/升级

> Vault­war­den 官方文档：[Backing up your vault · dani-garcia/vaultwarden Wiki · GitHub](https://github.com/dani-garcia/vaultwarden/wiki/Backing-up-your-vault)

使用 docker-ault­war­den 部署的 bit­war­den 备份非常简单，只需要备份映射的 `'docker映射本机目录地址':/data/` 目录中的全部文件即可

详细来说，它的目录结构是这样的

data

├── attachments # 用户上传的每个附件都存储为此目录下的单独文件.

│ └── <uuid> # (如果没有创建附件，附件目录将不存在.)

│ └── <random_id>

├── config.json # 存储 Vaultwarden 管理后台配置.

├── db.sqlite3 # 主 SQLite 数据库文件.

├── db.sqlite3-shm # SQLite 共享内存文件（可能存在）.

├── db.sqlite3-wal # SQLite 预写日志文件（可能存在）.

├── icon_cache # 站点图标（favicons）缓存在此目录下.

│ ├── <domain>.png

│ ├── example.com.png

│ ├── example.net.png

│ └── example.org.png

├── rsa_key.der # `rsa_key.*` 文件用于签署认证令牌.

├── rsa_key.pem

├── rsa_key.pub.der

└── sends # 用户上传的每个 Send 附件都存储为此目录下的单独文件.

└── <uuid> # (如果未创建 Send 附件，则发送目录将不存在.)

└── <random_id>

其中

### **SQLite 数据库文件**

**非常重要，需要备份**

除了上传的附件单独存储在 at­tach­ments 目录下外，SQLite 数据库文件存储了几乎所有重要的用户密码信息，是最重要的数据文件。

### **attachments 目录**

**重要，需要备份**

`attachments` 目录存放密码条目中上传的附件文件

### **sends 目录**

可选备份

`sends` 目录存放 Send 附件，考虑到 Send 附件往往只用作暂时分享，如果你没有长期存储的 Send 文件，可排除备份此文件夹以减小备份体积

### **config.json 文件**

**建议备份**

`config.json` 文件**明文**存储 Vault­war­den 管理后台配置，如果没有备份此文件，恢复备份后可能需要重新设置相关配置

> 需要注意的是，`config.json` 文件**明文**存储信息，这意味着将包括你的 **Vaultwarden 管理后台密码**和**邮箱 SMTP 设置**，虽然说这并不会对你的主密码和密码库安全有任何影响，但如果你担心会泄露这两者，可在备份此文件时采用一定的加密措施
> 
> 我的建议是，保证 Vault­war­den 管理后台密码不和主密码以及任何常用密码相同，然后采用专用的业务邮箱来配置 SMTP 信息，这样即使发生泄露，一般也不会产生实质的危害

### **rsa_key* 文件**

**建议备份**

该文件存储当前登录用户的身份令牌，删除此文件后，所有登陆的用户将被注销，迫使他们重新登录

### **icon_cache 目录**

可选备份

存放密码网站图标，这些图标会在缺少是自动生成，如非必要可以不备份

---

### **备份操作**

实际备份操作可根据以上说明进行

对我而言，我的网站只供我和朋友使用，平时也不常用附件和 Send 功能，数据量很小，所以直接对整个目录进行备份

我的备份策略是每天凌晨 1:30 将目录打包备份至服务器，并上传一份到 OneDrive，始终保存最新的 10 个版本（基于宝塔

![](https://www.ottoli.cn/wp-content/uploads/nxu55i-0.webp)

---

### **恢复操作**

1. **回滚恢复**

先暂停 docker 容器

docker stop <name>

将备份的文件替换当前 data 目录，然后重新启动 docker 容器

docker start <name>

> 如果发生错误，可尝试删除容器重新部署 docker（参考 2. 全新回复

1. **全新恢复**

删除现有 docker 容器（如有）

docker stop <name>

docker rm <name>

将备份的文件替换当前 data 目录，然后重新部署 docker 容器

docker run -d \

--name=vaultwarden \

-e WEBSOCKET_ENABLED=true \

-e LOG_FILE=/log/bitwarden.log \

-e ADMIN_TOKEN='主管理密码' \

-p 'docker映射本机端口':80 -p 'docker映射本机端口':3012 \

-v 'docker映射本机目录地址':/data/ \

--restart=always \

vaultwarden/server:latest

---

### **升级操作**

当 im­age 镜像更新，可根据需要对镜像进行升级

> 在升级前务必阅读官方更新日志，关注升级过程中有没有兼容性问题，以及如何迁移数据（如果需要

正常的版本更新，可通过以下步骤进行

> 在更新开始前，建议先备份一下

首先暂停并删除当前容器

docker stop <name>

docker rm <name>

然后拉取最新镜像

docker pull vaultwarden/server:latest

从新镜像部署容器（注意映射关系要保持一致

docker run -d \

--name=vaultwarden \

-e WEBSOCKET_ENABLED=true \

-e LOG_FILE=/log/bitwarden.log \

-e ADMIN_TOKEN='主管理密码' \

-p 'docker映射本机端口':80 -p 'docker映射本机端口':3012 \

-v 'docker映射本机目录地址':/data/ \

--restart=always \

vaultwarden/server:latest

> 建议部署容器成功后，进行测试，确定没有问题后再删除镜像
> 
> 如果发生了错误，可用未删除的老版本镜像重新部署，然后等待社区更新

确认无误后，删除原镜像，先查看镜像列表

docker images

# REPOSITORY TAG IMAGE ID CREATED SIZE

# vaultwarden/server latest 28e916391e7a 2 months ago 193MB

# vaultwarden/server <none> 8af25c1e7832 2 months ago 193MB

比如上面例子中，`TAG` 为 `<none>` 的便是老版本镜像，删除它

docker rmi 8af25c1e7832
