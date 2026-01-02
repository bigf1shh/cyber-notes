# Change DNS Nameserver temporarly
Objetivo: Modificar temporalmente los dns de arch

```
sudo resolvectl dns ens18 184.72.209.137
sudo resolvectl domain ens18 "~."
sudo resolvectl flush-caches
```

Modify `/etc/nsswitch.conf`
```
# Name Service Switch configuration file.
# See nsswitch.conf(5) for details.

passwd: files systemd
group: files [SUCCESS=merge] systemd
shadow: files systemd
gshadow: files systemd

publickey: files

hosts: files dns myhostname
# hosts: mymachines resolve [!UNAVAIL=return] files myhostname dns
networks: files

protocols: files
services: files
ethers: files
rpc: files

netgroup: files
```

Modify `/etc/resolv.conf`
```
nameserver 34.234.94.55
```

Probar resultados con:
```
resolvectl status
getent hosts www.offseclab.io
```