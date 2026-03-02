- Name:
- Version
- Domain/workgroup name
- Domain-sid
- Allows unauthenticated login

### nmap

```bash

# Version detection + NSE scripts
nmap -Pn -sV -p 445 "--script=banner,(nbstat or smb* or ssl*) and not (brute or broadcast or dos or external or fuzzer)" --script-args=unsafe=1 -oN tcp_445_smb_nmap.txt $ip
```

### smbmap

```bash
# List share permissions
smbmap -H $ip -P 445 2>&1 | tee -a "smbmap-share-permissions.txt"; smbmap -u null -p "" -H $ip -P 445 2>&1 | tee -a "smbmap-share-permissions.txt"

# List share contents
smbmap -H $ip -P 445 -R 2>&1 | tee -a "smbmap-list-contents.txt"; smbmap -u null -p "" -H $ip -P 445 -R 2>&1 | tee -a "smbmap-list-contents.txt"
```

### enum4linux

```bash
enum4linux -a -M -l -d $ip 2>&1 | tee "enum4linux.txt"
```

### smbclient

```bash
smbclient -L <target>
smbclient //<target>/tmp
smbclient \\\\<target>\\ipc$ -U john
smbclient //<target>/ipc$ -U john
smbclient //<target>/admin$ -U john
```

**Enumerate Samba version (*nix)**

```bash
# NB: change interface tcpdump listening on
sudo ./smbver.sh $ip 139
```

**Null session**

```bash
smbmap -H $ip
smbclient -L //$ip/ -U '' -N
```

**Enumerate shares**

```bash
nmap --script smb-enum-shares -p 445 $ip
```

**Connect to wwwroot share (try blank password)**

```bash
smbclient \\\\$ip\\wwwroot
```

**Nmap scans for SMB vulnerabilities (NB: can cause DoS)**

```bash
# RRAS Service Overflow
# https://docs.microsoft.com/en-us/security-updates/securitybulletins/2006/ms06-025
nmap -Pn -sV -p 445 --script="smb-vuln-ms06-025" --script-args="unsafe=1" -oN "tcp_445_smb_ms06-025.txt" $ip

# DNS RPC Service Overflow
# https://docs.microsoft.com/en-us/security-updates/securitybulletins/2007/ms07-029
nmap -Pn -sV -p 445 --script="smb-vuln-ms07-029" --script-args="unsafe=1" -oN "tcp_445_smb_ms07-029.txt" $ip

# Server Service Vulnerability
# https://docs.microsoft.com/en-us/security-updates/securitybulletins/2008/ms08-067
nmap -Pn -sV -p 445 --script="smb-vuln-ms08-067" --script-args="unsafe=1" -oN "tcp_445_smb_ms08-067.txt" $ip

# Eternalblue
# https://docs.microsoft.com/en-us/security-updates/securitybulletins/2017/ms17-010    
nmap -p 445 --script smb-vuln-ms17-010 -oN "tcp_445_smb_ms08-067.txt" $ip
```
### UserEnum

```bash
# With netexec
nxc smb <target> -u 'guest' -p '' --rid-brute

# With Nulllinux
python nullinux.py -U 'cicada.htb\guest' -P '' -users -range '100-2000' cicada-dc.cicada.htb
```