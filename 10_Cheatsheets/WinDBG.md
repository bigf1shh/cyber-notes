## Unassemble from memmory

```windbg
u kernel32!GetCurrentThread
```

## Reading from memmory

##### Display bytes

```windbg
db esp
```

##### Display words

```windbg
dw esp
```

##### Display double words

```windbg
dd esp

dW esp (with ASCII)
```

```windbg
dW KERNELBASE+0x40
```
##### Display qwords

```windbg
dq esp

dc esp (with ASCII)
```

```windbg
dc KERNELBASE
```

##### Parameter L change amount of displayed data

```windbg
dd esp L2 (2*dd)
```

##### Display data referenced from a memory

```windbg
dd poi(esp)
```

#### Dumping Structures

```windbg
dt ntdll!_TEB -> Show structure fields and offsets

dt -r ntdll!_TEB @$teb -> Show recursively nested structures and its data

dt ntdll!_TEB @$teb ThreadLocalStoragePointer -> Show specific field

?? sizeof(ntdll!_TEB)

```

#### Writing to Memory

```windbg
ed esp 41414141
```

```windbg
ea esp "Hello World"
```

#### Searching the memmory space

- s search
- -d double word
- 0 searching start address
- L?80000000 entire process memory space

```windbg
 s -d 0 L?80000000 41414141
```

#### Registers

```windbg
r
r ecx
r ecx=41414141
```

## Breakpoints
#### Software breakpoints

Set breakpoint

```windbg
bp kernel32!WriteFile
```

List breakpoints

```windbg
bl
```

Enable/Disable

```windbg
bd 0
be 0
```

Clear

```windbg
bc 0
```

#### Unresolved function breakpoints

```windbg
bu ole32!WriteStringStream
```

#### Breakpoint Based-Actions

```windbg
bp kernel32!WriteFile ".printf \"The number of bytes written is: %p\", poi(esp + 0x0C);.echo;g"
```

##### Conditional Breakpoints

```windbg
bp kernel32!WriteFile ".if (poi(esp+0xC) != 4) {gc} .else {.printf \"The number of bytes written is 4\";.echo;}"
```

gc -> go from conditional breakpoint

#### Hardware Breakpoints

Arguments:
1. ba -> breakpoint access
2. e/r/w -> execute, read, write
3. size of bytes for the memory access
4. Memory address

```windbg
ba e 1 kernel32!WirteFile
```

## Stepping

```windbg
p -> step over
t -> step into
g -> go
pt -> step to the next return
ph -> step until a branching execution is reached (conditional/inconditional branches/function calls/return instructions)
```

## Additional features

##### List modules
```windbg
lm
.reload /f
lm m kernel*
```

#### Examining symbols

```windbg
x kernelbase!CreateProc*
```

#### Calculator

args in hex by default
result -> dec = hex
```windbg
? 77269bc0 - 77231430
? 77269bc0 >> 18
```

#### Data output

0n -> decimal
0y -> binary

```windbg
? 0n41414141

? 0y100110101

.formats
```

#### PseudoRegisters

20 predefined pseudoregisters. From $t0 to $t19

Better to prefix them with @ char

```windbg
r @$t0 = (41414141 - 414141) * 0n10
? @$t0 >> 8
```