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

## Create Firewall Rule

```powershell
New-NetFirewallRule -DisplayName "8080-In" -Direction Inbound -Protocol TCP -Action Allow -LocalPort 8080
```

Disallow

```powershell
Remove-NetFirewallRule -DisplayName "8080-In"
```