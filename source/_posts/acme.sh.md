泛域名证书

```
cd .acme.sh
  796  ls
  797  bash
  798  acme.sh   --issue   --dns dns_dp   -d '*.xydh.fun' --debug
  799  acme.sh --install-cert -d '*.xydh.fun' \\n--key-file       /etc/ssl/private/fan.key.pem  \\n--fullchain-file /etc/ssl/private/fan.cert.pem \\n--reloadcmd     "service nginx force-reload"
  800  vim /etc/nginx/sites-enabled/go.conf
  801  service nginx restart

```