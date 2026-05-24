```bash
25 SMTP: Servidor de salida, encargado de enviar los correos, distribuirlos, y entregarlos a su destino.
If we find port 25 smtp open we can find emails.
110 POP3, 143 IMAP: Servidores de entrada, se encargan de almacenar y organizar los correos, una vez recibidos.
```

## SMTP - 25: Simple Mail Transfer Protocol

### We can send emails this way

```bash
telnet host port
helo bigfish.com
250 OK
MAIL FROM:<root@bigfish.com>
250 OK
RCPT TO:<valid.email@contoso.com>
250 OK
DATA
250 OK
Subject: Here goes the subject

Here goes the body: http://localhost:80/body
.
250 Queued
```

### We can find valid email accounts this way

```bash
smtp-user-enum -u possible-email@contoso.com host port
smtp-user-anum -U possible-email.lst host port
```

### vrfy python script

```python
#!/usr/bin/python

import socket
import sys

if len(sys.argv) != 3:
        print("Usage: vrfy.py <username> <target_ip>")
        sys.exit(0)

# Create a Socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the Server
ip = sys.argv[2]
connect = s.connect((ip,25))

# Receive the banner
banner = s.recv(1024)

print(banner)

# VRFY a user
user = (sys.argv[1]).encode()
s.send(b'VRFY ' + user + b'\r\n')
result = s.recv(1024)

print(result)

# Close the socket
s.close()
```

## POP3 IMAP

### POP3 We can list and retrieve emails from valid user

Si tu cuenta se configura como POP, los correos serán descargados directamente desde el servidor a tu equipo, por lo que no ocuparán espacio en tu hosting.

```bash
telnet host 110
USER <username>
PASS <password>
+OK POP3
LIST (Retrieve list of emails)
RETR X (X is the number of email we want to retrieve)
DELE X
QUIT
```

### IMAP

Si configuras tu cuenta como IMAP, tus emails serán visualizados desde tu gestor de correo, pero físicamente estarán almacenados en el servidor.

```bash
# For IMAP we can use evolution and configure account
```