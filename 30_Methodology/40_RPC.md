https://www.hackingarticles.in/active-directory-enumeration-rpcclient/

#### [RPC Endpoints](https://exploit-notes.hdks.org/exploit/windows/protocol/msrpc-pentesting/#rpc-endpoints)

To enumerate RPC endpoints, use `impacket-rpcdump`.

```sh
impacket-rpcdump -port 135 <target-ip> | grep -E 'MS-EFSRPC|MS-RPRN|MS-PAR'
```

- **MS-EFSRPC**: It might be vulnerable to **PetitPotam**.
- **MS-RPRN**, **MS-PAR**: It might be vulnerable to **PrintNightmare**.
#### Server Info

```
srvinfo
```

#### Domain Information Query

```
querydominfo
```

#### Enumerating Domain Users

```
enumdomusers
```

#### Enumerating Domain Groups

```
enumdomgroups
```

#### Group Queries

```
querygroup 0x200
```

#### User Queries

```
queryuser yashika
```

#### Enumerating Privileges

```
enumprivs
```

#### Get Domain Password Information

```
getdompwinfo
```

#### Get User Domain Password Information

```
getusrdompwinfo 0x1f4
```

#### Enumerating SID from LSA

```
lsaenumsid
```

#### Creating Domain User

```
createdomuser hacker
setuserinfo2 hacker 24 Password@1
enumdomusers
```

#### Lookup Names

```
lookupnames hacker
```

#### Enumerating Alias Groups

```
enumalsgroups builtin
```

#### Delete Domain User

```
deletedomuser hacker
```

#### Net Share Enumeration

```
netshareenum
netshareenumall
```

#### Net Share Get Information

```
netsharegetinfo Confidential
```

#### Enumerating Domains

```
enumdomains
```

#### Enumerating Domain Groups

```
enumdomgroups
enumdomusers
queryusersgroups 0x44f
querygroupmem 0x201
```

#### Display Query Information

```
querydispinfo
```

#### Change Password of User

```
chgpasswd raj Password@1 Password@987
```

#### Create Domain Group

```
createdomgroup newgroup
enumdomgroups
```

#### Delete Domain Group

```
deletedomgroup newgroup
enumdomgroups
```

#### Domain Lookup

```
lookupdomain ignite
```

#### SAM Lookup

```
samlookupnames domain raj
samlookuprids domain 0x44f
```

#### SID Lookup

```
lsaenumsid
```

#### LSA Query

```
lsaquery
dsroledominfo
```

#### LSA Create Account

An attacker can create an account object based on the SID of that user. For this particular demonstration, we will first need a SID. This can be extracted using the lookupnames command used earlier. Passing the SID as a parameter in the lsacreateaccount command will enable us as an attacker to create an account object as shown in the image below.

```
lookupnames raj
lsacreateaccount S-1-5-21-3232368669-2512470540-2741904768-1103
```

#### Enumerating LSA Group Privileges

```
lsaenumsid
lookupsids S-1-1-0
lsaenumacctrights S-1-1-0

lsaaddpriv S-1-1-0 SeCreateTokenPrivilege
lsaenumprivsaccount S-1-1-0
lsadelpriv S-1-1-0 SeCreateTokenPrivilege
lsaenumprivsaccount S-1-1-0
```

#### Enumerating LSA Account Privileges

```
lookupnames raj
lsaaddacctrights S-1-5-21-3232368669-2512470540-2741904768-1103 SeCreateTokenPrivilege
lsaenumprivsaccount S-1-5-21-3232368669-2512470540-2741904768-1103
lsaremoveacctrights S-1-5-21-3232368669-2512470540-2741904768-1103 SeCreateTokenPrivilege
lsaenumprivsaccount S-1-5-21-3232368669-2512470540-2741904768-1103

lsalookupprivvalue SeCreateTokenPrivielge
```

#### LSA Query Security Objects

```
lsaquerysecobj
```