
1. Objetivo: Conectar Arch a VPS para salir por su IP
2. Setup Servidor

3. Setup Cliente
4. Kil Switch

### Setup Servidor

- Instala WireGuard
`pacman -S wireguard´

- Genera las claves
```bash
wg genkey | tee private.key | wg pubkey > public.key
```

- Crea `etc/wireward/wg0.conf`

```toml
[Interface] 
Address = 10.0.0.1/24 
ListenPort = 51820 
PrivateKey = <Tu_Clave_Privada_VPS>
[Peer] 
PublicKey = <Tu_Clave_Publica_Local> 
AllowedIPs = 10.0.0.2/32
```

- Levanta la interfaz 
`wg-quick up wg0`

### Setup Client

- Instala WireGuard
- Crea `/etc/wireguard/wg0.conf`
```toml
[Interface]
Address = 10.0.0.2/24
PrivateKey = <tu_clave_privada_local>

[Peer]
PublicKey = <Tu_Clave_Publica_VPS>
Endpoint = <IP_PUBLICA_VPS>:51820
AllowedIPs = 10.0.0.0/24, <IP_PUBLICA_VPS>/32
PersistentKeepalive = 25
```
El `PersistentKeepalive` es vital para que no se caiga la conexión detrás del NAT de tu casa.

