华为云配置docker UI & Nginx

```shell
chsh -s /bin/zsh
vim .zshrc
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
source .zshrc
vim ~/.oh-my-zsh/themes/agnoster.zsh-theme
source .zshrc
cd .oh-my-zsh/custom/plugins
ls
cd
vim .zshrc
source .zshrc
sudo apt-get update
sudo dpkg --configure -a
sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install docker-ce
docker ps
docker volume create portainer_data
docker run -d -p 8000:8000 -p 9000:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
apt install nginx
cd /etc/nginx/sites-enabled
ls
vim go.conf
service nginx restart
ls
vim go.conf
service nginx restart
nginx -t
vim go.conf
docker ps
sudo service nginx restart
cd /etc/nginx/sites-available
ls
vim go.conf
service nginx restart
cd /etc/nginx/sites-available
ls
rm go.conf
ls
cd  ..
ls
cd sites-enabled
ls
vim go.conf
sudo service nginx restart
vsftpd -v
apt-get install vsftpd
vsftpd -v
which nginx
nginx -V
cd /etc/nginx/sites-enabled
ls
vim go.conf
service nginx restart
vim go.conf
lsof -i:443
cd /etc/nginx/sites-enabled
rm go.conf.1
mv go.conf go.conf.1
vim go.conf
cat go.conf
service nginx restart
nginx -t # 检测nginx配置文件
vim go.conf
service nginx restart # 应用nginx配置
```

