

## notes
- php login /index.php /login.php
- directorios /backup y /reports que devuelven 401 Unauthorized

## nmap
```nmap
# Nmap 7.98 scan initiated Mon Nov 24 19:37:03 2025 as: nmap -p80,19722,19761 -sC -sV -oN targeted -vv 192.168.1.163
Nmap scan report for 192.168.1.163 (192.168.1.163)
Host is up, received syn-ack (0.00034s latency).
Scanned at 2025-11-24 19:37:03 CET for 12s

PORT      STATE SERVICE REASON  VERSION
80/tcp    open  http    syn-ack Apache httpd 2.4.7
| http-methods: 
|_  Supported Methods: OPTIONS GET HEAD POST
|_http-server-header: Apache/2.4.7
|_http-title: Welcome: It works
19722/tcp open  ssh     syn-ack OpenSSH 6.6.1p1 Ubuntu 2ubuntu2 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   1024 fa:59:e1:29:92:c9:9e:f4:79:da:9c:3f:21:c9:0f:72 (DSA)
| ssh-dss AAAAB3NzaC1kc3MAAACBALR+CrRi3Lr+cNgQXR+g+Dn7ANi6fb+ExK+m49GbvER5+6Faiu9Ifw+AEKpZOtd5PcdByFDCQXib0Aqg5hRxRJFtJbOYb+cBSw1yk4yGKNoaC2XMgulAZYjFljjU1sI+brfFIWUZSGKuV/c6SF6XvxGD8ithnYwOsSVjqyAcZbYnAAAAFQCJCSEFhV2V8y8aSylBcBbM2J9uvQAAAIBTyegF7UgkyTj1DdgSqmpe8Zj4GxH/c8hkHfmD9lI7prqNTEZSEgBAOmoMcHJLJ2UMqUlKY1mTbg0t+ahX+Yvt9RZeg41khMkHfYFYE5p9etnQKxzsOftzaF4LztBNyJ8jodajwjXxMP+X3wjanjI8iAmINXQ5CseKH6Gf3Q5EsAAAAIEAjMBwPMFhJLWeAUPHzj8u/yVuKCyexZXIFHXGbEPJa9es6dIIfaPssr9HZ80Q8KUN0Me78TpjlrRPqWqGg7UP2MkQQIgnN/EkQ46+Ey6Oibz+h5qEQ7XIv2eqyxGrlizTVyThgKSIzS0H9JIiZtj7HUaOjUhHIntnV1Wx9G0hHiU=
|   2048 56:bf:e8:f2:9f:6c:4e:82:1a:7c:89:49:e5:de:64:a3 (RSA)
| ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDXy3cJFkFbZRz7iXSlcA4S9h68EbbfP3CDvmE8EQ6boXQ3UsZbyFn/zG+3FuJkxj3GBL9sRKkAFv0e1HBvc14OjklG3OJAsiaYGQ9NcYPkCJQZxuKyaYDg6i/JU8jRwI1TDtANGPKAhI8gSC3yDY9Yk48sAResUw6vJ2zWxrOcktk6RQ9caR7Vf/5iyWDO2IvVpJAyQsEal6Ab/EzDJqJWA1sddnxM7DhvT9mQvaXpK4eiPbKdIx0/HEU3AuNroVq1HMUijhjjY+2w22cEKd+ovO5LcvktFjAUQVSeibK/FI2FizzOIImzkeAgX/dGNl2CTlM3pHgcnzKjyaTHWX1P
|   256 c9:f2:dd:4e:fc:8d:08:18:3a:be:a8:3a:ac:0b:d2:e4 (ECDSA)
| ecdsa-sha2-nistp256 AAAAE2VjZHNhLXNoYTItbmlzdHAyNTYAAAAIbmlzdHAyNTYAAABBBHpB/FWXfP4R3Bcb+CJESd93Qi3m4hOiSRsbv/5832YYn+v0bOafCnfDcCmBIKYCmyBQVDE4UpIETJGvpX4KJ3g=
|   256 43:6e:e1:0d:f9:72:26:c5:89:ca:a7:ad:f7:18:1d:63 (ED25519)
|_ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIEqV3rMIAHDjtbqE0Jj7A0/vd3BqtLYnGszYrQLZKJ3Y
19761/tcp open  http    syn-ack Apache httpd 2.4.7
| http-methods: 
|_  Supported Methods: GET HEAD POST
|_http-server-header: Apache/2.4.7
|_http-title: 400 Bad Request
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Read data files from: /usr/bin/../share/nmap
Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Mon Nov 24 19:37:15 2025 -- 1 IP address (1 host up) scanned in 11.95 seconds

```