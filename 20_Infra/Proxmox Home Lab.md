
Tags: #homelab #proxmox #archlinux #optimización

- [[#1. Hardware y Estrategia Base|1. Hardware y Estrategia Base]]
- [[#2. Gestión de Memoria (RAM 16GB Total)|2. Gestión de Memoria (RAM 16GB Total)]]
- [[#3. Configuración Óptima de la VM (Proxmox GUI)|3. Configuración Óptima de la VM (Proxmox GUI)]]
	- [[#3. Configuración Óptima de la VM (Proxmox GUI)#Arch|Arch]]
	- [[#3. Configuración Óptima de la VM (Proxmox GUI)#Windows|Windows]]
- [[#4. Configuración dentro de Arch Linux (Guest)|4. Configuración dentro de Arch Linux (Guest)]]
	- [[#4. Configuración dentro de Arch Linux (Guest)#A. Instalación del Agente|A. Instalación del Agente]]
	- [[#4. Configuración dentro de Arch Linux (Guest)#B. Habilitar TRIM (Recuperación de espacio)|B. Habilitar TRIM (Recuperación de espacio)]]
	- [[#4. Configuración dentro de Arch Linux (Guest)#C. Comprobación Final|C. Comprobación Final]]
- [[#5. Configuración dentro de Windows (Guest)|5. Configuración dentro de Windows (Guest)]]
	- [[#5. Configuración dentro de Windows (Guest)#A. Instalación de los Drivers VirtIO|A. Instalación de los Drivers VirtIO]]
	- [[#5. Configuración dentro de Windows (Guest)#B. Post-Instalación|B. Post-Instalación]]
	- [[#5. Configuración dentro de Windows (Guest)#C. Ajustes Específicos para Windows (Importante)|C. Ajustes Específicos para Windows (Importante)]]
	- [[#5. Configuración dentro de Windows (Guest)#Resumen Rápido|Resumen Rápido]]


## 1. Hardware y Estrategia Base
     
- **Sistema de Archivos del Host:** **LVM-Thin / EXT4** (Verificado).
    
    - _Nota:_ Al no usar ZFS, no es necesario limitar la caché ARC. El host consume poca RAM (~1.5GB).
        

## 2. Gestión de Memoria (RAM 16GB Total)

Estrategia de **Overprovisioning** y **Ballooning** para maximizar recursos.
- **Reserva para Proxmox (Host):** ~2 GB intocables.
- **Disponible para VMs:** ~14 GB.
- **Configuración por VM (Ejemplo):**
    - `Memory (RAM)`: Límite máximo 8Gb
    - `Minimum Memory`: Lo mínimo garantizado 4GB
    - _Importante:_ Para que esto funcione bien, el **QEMU Guest Agent** es obligatorio.
- Windows **Ballooning:** **SÍ, pero con cuidado.** A Windows le gusta comer RAM.
    - _Recomendación:_ Si le das 8GB de máximo, ponle un **Mínimo de 4GB**. Si bajas de 4GB, la interfaz de Windows se arrastrará y la experiencia será muy lenta.
    
## 3. Configuración Óptima de la VM (Proxmox GUI)

### Arch
Ajustes a realizar en la configuración de la máquina virtual (Arch) **antes** de encenderla o aplicando cambios apagándola completamente.

- [ ] **System > QEMU Guest Agent:** `Enabled` (Crucial para ver RAM real y apagado limpio).
    
- [ ] **Processor > Type:** Cambiar de `kvm64` a `Host` (Permite usar instrucciones reales de la CPU como AES-NI para cifrado rápido). 1 Socket. 4 Cores
    
- [ ] **Hard Disk:**
    
    - [ ] `Discard`: Marcado (Permite liberar espacio en el host al borrar archivos en la VM - TRIM).
        
    - [ ] `SSD Emulation`: Marcado (Si el disco físico es SSD).
        
    - [ ] `Bus/Device`: Usar **VirtIO Block**.
        
- [ ] **Network Device:** Model `VirtIO (paravirtualized)`.

### Windows
1. **Disco Duro:**
    
    - **Bus/Device:** `SCSI` (Mejor que VirtIO Block en Windows).
        
    - **Controller:** `VirtIO SCSI`.
        
    - **Cache:** `Write back` (Mejora mucho la velocidad en Windows, pero ojo si se va la luz).
        
    - **Discard:** ✅ Activado (SSD Emulation también).
        
2. **Red:** Modelo `VirtIO (paravirtualized)`. (Windows no detectará la red al instalar hasta que cargues el driver, tenlo en cuenta).
    
3. **CPU:** Type `Host`.
    
4. **CD/DVD Drive 2:** Añade una segunda unidad de CD y monta la ISO de `virtio-win`.

## 4. Configuración dentro de Arch Linux (Guest)

### A. Instalación del Agente

Necesario para que Proxmox vea la IP y el consumo real de RAM (soluciona el falso 100% de uso).

```bash
sudo pacman -S qemu-guest-agent
```

Si al intentar habilitar el servicio aparece el error _"The unit files have no installation config"_:

1. **Causa:** El paquete en Arch usa reglas `udev` para auto-iniciarse solo si detecta el hardware virtual.
    
2. **Solución:**
    
    - Asegurar que la opción "QEMU Guest Agent" está activa en Proxmox.
        
    - Realizar un **Ciclo de Energía Completo**: Apagar la VM (`Stop` / `Shutdown`) y volver a iniciarla (`Start`). **No vale reiniciar (`Reboot`)**.
        
3. **Verificación:**

```bash
systemctl status qemu-guest-agent
```
	(Debería salir `active (running)` automáticamente tras el encendido).
### B. Habilitar TRIM (Recuperación de espacio)

Para que la opción `Discard` funcione y recupere espacio en disco:

```bash
sudo systemctl enable --now fstrim.timer
```
### C. Comprobación Final

En la interfaz web de Proxmox (Summary de la VM):

1. **IP:** Debe aparecer la dirección IP de la VM.
2. **RAM Usage:** Debe mostrar el consumo real (aprox 10-40%) y no el 80-90% fijo.
3. **Ballooning:** Si la RAM host se llena, Proxmox podrá reclamar memoria a esta VM.

## 5. Configuración dentro de Windows (Guest)

### A. Instalación de los Drivers VirtIO

A diferencia de Arch, donde `pacman` lo hace todo, en Windows **tienes que instalar manualmente los drivers**. Sin ellos, la red irá lenta, el disco será ineficiente y no tendrás Guest Agent.

**Lo que necesitas:** La ISO de `virtio-win`. (Suele estar en los repositorios de Proxmox o descargable desde su web).

### B. Post-Instalación

Una vez instalado Windows, verás que faltan drivers en el "Administrador de dispositivos".

1. Abre el CD de **virtio-win** que montaste.
    
2. Ejecuta el instalador **`virtio-win-gt-x64.exe`** (o similar).
    
3. Asegúrate de marcar todo, especialmente:
    
    - **VirtIO Ethernet Adapter** (Red).
        
    - **VirtIO SCSI Controller** (Disco).
        
    - **VirtIO Balloon Driver** (Memoria dinámica).
        
    - **QEMU Guest Agent** (El servicio clave).
        
    - _QEMU PVPanic Device_ (Opcional, para reportar pantallazos azules a Proxmox).
        

### C. Ajustes Específicos para Windows (Importante)

- **Desactiva el "Inicio Rápido" (Fast Startup):**
    
    - _Por qué:_ Windows por defecto no se apaga, hiberna. Esto puede corromper el sistema de archivos si Proxmox hace un backup o instantánea mientras Windows cree que está hibernando.
        
    - _Cómo:_ Panel de Control -> Energía -> Elegir comportamiento de botones -> Desmarcar "Activar inicio rápido".
        
- **Desfragmentar vs TRIM:**
    
    - Como activamos "Discard", ve a "Desfragmentar y optimizar unidades". Windows debería detectar el disco como "Medio de estado sólido" (gracias a la opción SSD Emulation) y ejecutar **Recorte (TRIM)** en lugar de desfragmentar.
### Resumen Rápido

- **Drivers:** Requiere montar ISO `virtio-win` e instalar `virtio-win-gt-x64`. 
- **Disco:** Usar controlador `VirtIO SCSI` + Cache `Write Back`.    
- **Red:** `VirtIO`.    
- **Guest Agent:** Se instala vía el ejecutable de la ISO, no por CMD.    
- **RAM:** Ballooning activo, pero **Min Memory >= 4GB** para evitar lag en GUI.    
- **Seguridad:** Desactivar **Windows Fast Startup** para evitar corrupción de datos en backups.