
## Vulnerabilities in Password-Based

1. Bruteforce Password
2. Bruteforce Username
3. Enumerating Username

### Username enumeration
1. Via different responses
2. Via response timing
3. Via account lock

### Bypass lock account
1. Login with valid credentials
2. Send multiple credentials per request
## Vulnerabilities in multifactor auth

1. Skip 2factor and go to "log in"
2. Log in with a valid user and then send "victim user" in verification step
### BruteForcing 2FA

Use Turbo intruder/Macros for logging with valid credentials while trying to bruteforce 2fa (useful to bypass rate limit)

## Vulnerabilities in other auth methods

### Keeping user logged in

##### Brute-force staye-logged-in cookies

If the method used in encryption stay-logged-in cookie is guesseable, we can brute force cookie. -> Useful to bypass Rate Limit protection)

### Resetting user passwords

- **Via broken logic.** Check if tokens are being checked. Maybe you can change victim's password with your session.
- Via poisoning middleware. When requesting the password reset link, include some headers that could poison middleware
	- `X-Forwarded-Host`
	- `X-Forwarded-For`
	- `X-Forwarded...`

### Changing user passwords

If the username is provided in a hidden field, an attacker might be able to edit this value in the request to target arbitrary users. This can potentially be exploited to enumerate usernames and brute-force passwords.

# Business Logic Vulnerabilities

# Access Control