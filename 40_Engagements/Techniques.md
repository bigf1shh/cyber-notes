
---
tags: [ #tool/network, #technique/pivoting, #os/linux ]
aliases: [ ssh-tunnel, socks-proxy ]
creation_date: 2025-12-07

---
# SSH Dynamic Port Forwarding (SOCKS)

## Quick Command
El comando que uso el 90% de las veces.

```bash
ssh -N -D 1080 -f usuario@vps-ip
```

## Syntax

Desglose si necesito modificar algo.

- `-N`: No ejecutar comando remoto (solo forward).
    
- `-D <port>`: Puerto SOCKS local.
    
- `-f`: Background.
    

## Configuration (Proxychains)

Añadir al final de `/etc/proxychains4.conf`:

