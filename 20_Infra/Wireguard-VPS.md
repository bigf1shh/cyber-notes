
1. Objetivo: Conectar Arch a VPS para salir por su IP

### Setup Servidor

- Instala WireGuard
```bash
apt install wireguard
```

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
PostUp = iptables -A FORWARD -i wg0 -j ACCEPT; iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE
PostDown = iptables -D FORWARD -i wg0 -j ACCEPT; iptables -t nat -D POSTROUTING -o ens3 -j MASQUERADE

[Peer]
PublicKey = <Tu_Clave_Publica_Local> 
AllowedIPs = 10.0.0.2/32
```

- Levanta la interfaz 
```bash
sudo wg-quick up wg0
```

##### Proxy inverso - Redirección de puertos

Objetivo: Que el tráfico que llega al VPS puerto 80 o 443, salte al túnel 10.0.0.2

En el VPS -> Habilitamos forwarding y creamos reglas de NAT

```bash
# Habilitar IP Forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward
# Variables 
PUERTO_C2=443 
IP_LOCAL_TEAMSERVER=10.0.0.2 

# 1. Regla de Redirección (Entrada) 
# "Todo lo que llegue al puerto 443, envíalo a la 10.0.0.2" 
sudo iptables -t nat -A PREROUTING -p tcp --dport $PUERTO_C2 -j DNAT --to-destination $IP_CLIENTE_VPN:$PUERTO_C2 

# 2. Regla de Permiso (Paso a través) 
# A veces el firewall bloquea el paso de una interfaz a otra. Aseguramos que pase. 
sudo iptables -A FORWARD -p tcp -d $IP_CLIENTE_VPN --dport $PUERTO_C2 -j ACCEPT
```
Guardalo en `wg0.conf`
```
[Interface]
Address = 10.0.0.1/24
ListenPort = 51820
PrivateKey = aKIhmSD....v22HAPnpx11Q=
MTU = 1280
PostUp = iptables -A FORWARD -i wg0 -j ACCEPT; iptables -t nat -A POSTROUTING -o ens3 -j MASQUERADE; iptables -t nat -A PREROUTING -i ens3 -p tcp --dport 443 -j DNAT --to-destination 10.0.0.2:443
PostDown = iptables -D FORWARD -i wg0 -j ACCEPT; iptables -t nat -D POSTROUTING -o ens3 -j MASQUERADE; iptables -t nat -D PREROUTING -i ens3 -p tcp --dport 443 -j DNAT --to-destination 10.0.0.2:443

[Peer]
PublicKey = V1SVDO....0DUoimFA=
AllowedIPs = 10.0.0.2/32
```
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
# AllowedIPs = 10.0.0.0/24, <IP_PUBLICA_VPS>/32
AllowedIPs = 0.0.0.0/0, ::/0 # Si quieres acceder
PersistentKeepalive = 25
```
El `PersistentKeepalive` es vital para que no se caiga la conexión detrás del NAT de tu casa.

### Shortcuts

Levantar/Apagar servidor
```
sudo wg-quick up/down wg0
```


Levantar/Apagar cliente
```
sudo wg-quick up/down wg0
```

Mostrar configuración
```
sudo wg show
```