1. Limpieza interna (Desde Arch Linux)

```bash
# 1. Limpiar el caché de paquetes de pacman
sudo pacman -Scc

# 2. (Opcional pero recomendado) Llenar el espacio libre con ceros 
# Esto ayuda al compactador a identificar el espacio vacío.
dd if=/dev/zero of=zero.small.file bs=1024 count=1024
rm zero.small.file
```

2. Apagar WSL Completamente
```powershell
wsl --shutdown
```

3. Compactar el disco con diskpart
```cmd
diskpart
select vdisk file="C:\Users\Eugenio\AppData\Local\wsl\{eba7a9e3-e767-4e64-a6bc-24f4329fa822}\ext4.vhdx"
attach vdisk readonly
compact vdisk
detach vdisk
exit
```
