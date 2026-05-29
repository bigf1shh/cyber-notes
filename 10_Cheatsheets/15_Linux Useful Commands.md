

## File separators
Input file Separator https://en.wikipedia.org/wiki/Input_Field_Separators
bash $IFS
urlencode space %20
urlencode linebreak %0a
urlencode returncarriage %0d

## OpenSSL bypass
How to use curl against old/deprecated protocols and cyphers
```
curl -k --tls-max 1.0 --ciphers DEFAULT@SECLEVEL=0 -s https://domain.com:443/index.php
```
