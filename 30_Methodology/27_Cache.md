## Web Cache Deception

![[WEB Cache Deception.xmind]]
### Search presence of Cache

1. X-Cache header
2. Response times
3. Cache-Control*

### Path mapping

1. Find rules of cache based on extensions
2. Search path mapping discrepancy (`/my-account/abc.js` returns the same as `/my-account`
3. Craft an exploit
##### Discrepancies
#### Identify path delimiter in origin server

1. Try endpoint with random values at the end `/my-accountabc` (find evidence of caching)
2. Intruder snipper attack `/my-account§§abc` to find values that may be used as delimiter

#### Investigate path delimiter discrepancies

1. Add the `?` character (**previously found**) after `/my-account` and add a static file extension to the path. For example, update the path to `/my-account?abc.js`. Try every charachter previously found
### Investigate normalization discrepancies

1. Add arbitrary directory followed by encoded dot segment `/aaa/..%2fmy-account` (finding if origin server is resolving dot segment)
2. Search static directories with evidence of caching like `/resources`. Add encoded dot segment and check if cache is resolving `/resources/..%2fYOUR-RESOURCE`
3.  Investigate if there is a cache directory cache rule `/resources/aaa`
### Crafting Exploit

1. Try your guess `/resources/..%2fmy-account`
2. payload -> `<script>document.location="https://YOUR-LAB-ID.web-security-academy.net/resources/..%2fmy-account?wcd"</script>`

## Exploiting normalization by the cache-server

##### Look for delimiters
1. Look for path delimiter by origin -> When the server answer with the same content, the parameter is a delimiter.
2. Look for path delimiter by cache -> Chek Cache Headers. When cache miss the same request, the delimiter is working for the cache.
##### Look for normalization
1. Normalization by origin -> Play with dynamic generated request. When the server answer with expected file, origin is normalizing.
2. Normalization by Cache -> check cache headers.
Payload -> `/profile;%2f%2e%2e%2fstatic`
- The cache interprets the path as: `/static`
- The origin server interprets the path as: `/profile`