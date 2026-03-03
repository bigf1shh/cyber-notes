# Detecting SQLi

https://portswigger.net/web-security/sql-injection/cheat-sheet
## Intruder
#### Payloads
1. `quick-SQLi.txt`
2. `Generic-BlindSQLi.fuzzdb.txt`
3. URL encode payloads
4. Match/replace
	1. `or -> ||`
	2. `and -> &&`
5. OAST Interaction
	1. Stacked queries
	2. Union select
#### Indicators of sqli
1. Errors in results: (error, sqli, 500...)
2. Length of responses
3. Response received (time)
#### Update csrf
1. Macros https://portswigger.net/support/using-burp-suites-session-handling-rules-with-anti-csrf-tokens

#### Bypass WAF
1. XML (HTML) encode payloads -> **Hackvertor**