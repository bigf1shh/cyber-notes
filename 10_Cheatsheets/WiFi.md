
## Scan Wifi Network

```
iw wlan0 scan
iwlist wlan0 scan
```

## Connect to wifi network

```bash
wpa_passphrase <essid> >> /etc/wpa_supplicant.conf
wpa_supplicant -B -D <driver:wext> -i wlan0 -c /etc/wpa_supplicant.conf
```

## Mode monitor

Set interface in mode monitor /managed

```bash
ifconfig wlan0 down
iwconfig wlan0 mode monitor #iwconfig wlan0 mode managed
ifconfig wlan0 up
```
## Aircrack-ng
### Scan Wifi Network

```bash
airodump-ng -i wlan0 -c <channel> -b <band:abg> --bssid <bssid>
```

## WPS Attack

1. Set mode monitor
2. Kill wpa_supplicant
3. reaver
	```bash
	reaver -i wlan0
	```