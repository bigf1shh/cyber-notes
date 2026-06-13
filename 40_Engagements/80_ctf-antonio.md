

## notes
- php login /index.php /login.php
- directorios /backup y /reports que devuelven 401 Unauthorized
ctf ibm

## Vectores de ataque
```
Puerto 22/19722 (SSH):
    [x] Escaneo de versión: OpenSSH 6.6.1p1 (Vulnerable a enumeración de usuarios).
    [x] Enumeración de usuarios: Descubiertos root y user.
    [ ] Fuerza bruta: Pendiente lanzar diccionario mutado.
Puerto 80 (HTTP):
    [x] Fuzzing básico: Solo index.html (Fake rabbit hole de .NET) y error.html.
    [x] Virtual Hosting: Requiere Host Header ctf.somedomain.com
Puerto 19761 (HTTPS):
    [x] SSLScan: Usa TLSv1.0 y ciphers obsoletos (Resuelto con proxy socat en puerto 8080).
    [x] Fuzzing de directorios: Encontrado /reports/ (403) y /backup/ (401).
    [x] Fuzzing ampliado en /reports/: Encontrado user.txt (Contiene datos de gastos: 300USD).
```

Registro de comandos
```
# Comando: sslscan 192.168.1.136:19761
# Resultado: Reveló dominio ctf.somedomain.com y uso de TLSv1.0.

# Comando: hydra -l admin -P rockyou.txt 192.168.1.136 https-get ...
# Resultado: ERROR (Child terminating / unsupported protocol). TLS moderno de Kali bloquea la conexión.

# Comando: sudo socat TCP-LISTEN:8080,fork ...
# Resultado: EXITOSO. Puente HTTP plano -> HTTPS TLS1.0 activo en localhost:8080.
```

Privesc
```
2026/06/01 18:52:26 CMD: UID=0     PID=932    | acpid -c /etc/acpi/events -s /var/run/acpid.socket

cat /etc/monitoring-locations.conf
/etc
/bin
/usr

www-data@ctf:/etc/acpi$ ps aux | grep acpid
root       932  0.0  0.0   4372  1376 ?        Ss   May24   0:00 acpid -c /etc/acpi/events -s /var/run/acpid.socket

www-data@ctf:/etc/acpi$ ls -la
total 16
drwxr-xr-x  3 root root 4096 Sep 19  2016 .
drwxr-xr-x 95 root root 4096 May 24 22:06 ..
drwxr-xr-x  2 root root 4096 Sep 19  2016 events
-rwxr-xr-x  1 root root 2423 Apr  3  2014 powerbtn.sh

www-data@ctf:/etc/acpi$ ls -la events/
total 12
drwxr-xr-x 2 root root 4096 Sep 19  2016 .
drwxr-xr-x 3 root root 4096 Sep 19  2016 ..
-rw-r--r-- 1 root root  423 Apr  3  2014 powerbtn

www-data@ctf:/etc/acpi$ ls -la /var/run/acpid.socket
srw-rw-rw- 1 root root 0 May 24 22:06 /var/run/acpid.socket
```

## Credenciales y Datos Encontrados
```
Usuarios del Sistema: root, user, mysql
Dominios: ctf.somedomain.com
Pistas/Texto: Archivo user.txt reporta un total de 300USD. Posible patrón para contraseñas.
```


## Próximos Pasos
```
[x] Crear diccionario mutado combinando user, 2016 y 300USD.
[x] Lanzar Hydra contra SSH (19722) usando la lista de usuarios reales de la máquina.
[x] Lanzar Hydra contra basic auth (19761) /backup usando la lista de usuarios mutados
[x] Probar fuerza bruta al formulario web POST /login.php a través del puerto 8080 de socat.
[x] Probar fuerza bruta al formulario web POST /login.php con el email en vez de usernames a través del puerto 8080 de socat.
[] Fuerza bruta contra basic auth con user admin y rockyou-b64
[x] port knocking con los valores que hemos encontrado ¿?¿?
```

## Timeline

