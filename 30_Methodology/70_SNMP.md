## snmpwalk


```bash
snmpwalk -v2c -c <public> <ip>
```

### Extra info

```bash
snmpwalk -v2c -c <community string> <ip> NET-SNMP-EXTEND-MIB::nsExtendObjects
```

We can RCE if we have write permission -> https://book.hacktricks.xyz/network-services-pentesting/pentesting-snmp/snmp-rce

# onesixtyone

We can use this for bruteforce community strings
