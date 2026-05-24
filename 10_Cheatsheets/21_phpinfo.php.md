Interesting info

![[Pasted image 20260104174118.png]]
- When fopen is in the On position we can use data wrappers
- Not sure about the above. To exploit data:// warppers, the `allow_url_include` setting needs to be enabled

![[Pasted image 20260104174220.png]]
- You’re in for a good LFI time when both of these are set to On.

![[Pasted image 20260104174250.png]]

![[Pasted image 20260104174314.png]]
- We could put a file here

Now we know that this web app is run by root from /srv/http directory.