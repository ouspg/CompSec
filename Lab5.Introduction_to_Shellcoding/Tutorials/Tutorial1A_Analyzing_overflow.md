# Analyzing simple program with buffer overflow vulneralibity

Usually, when overflow occurs, we are just seeing 'Segmentation Fault' error or strange behaviour in program... or maybe nothing at all. That is not too precise information.
We can use GNU Debugger for example to see, what's actually happening, when we are executing the program.

Some parts in this tutorial are not revealed nor fully explained, in purpose of to readers to find out or explain themselves.

Example of overflowing program with input, which is actually limited to some size inside program. Function 'stackoverflow' contains buffer overflow, and we are changing it's return address.

This 64-bit example is using Python script to generate argument for actual
program. We will have a look for register contents.

Here is short intro to the usage of gdb, if it is not familiar beforehand:
https://mohit.io/blog/gdb-assembly-language-debugging-101/



```shell
root@kali:~/Desktop/Shellcode# gcc -o test Overflow.c
root@kali:~/Desktop/Shellcode# gdb -q test
Reading symbols from test...(no debugging symbols found)...done.
(gdb) r "$(python -c 'print "A" * 9')"
Starting program: /root/Desktop/Shellcode/test "$(python -c 'print "A" * 9')"
[Inferior 1 (process 9552) exited normally]
(gdb) r "$(python -c 'print "A" * 10')"
Starting program: /root/Desktop/Shellcode/test "$(python -c 'print "A" * 10')"

Program received signal SIGSEGV, Segmentation fault.
0x0000004000000100 in ?? ()
(gdb) 

(gdb) info registers
rax            0x0	0
rbx            0x0	0
rcx            0x4141414141414141	4702111234474983745
rdx            0x414141	4276545
rsi            0x7fffffffe5b8	140737488348600
rdi            0x7fffffffe196	140737488347542
rbp            0x100000000a0	0x100000000a0
rsp            0x7fffffffe110	0x7fffffffe110
r8             0x555555554710	93824992233232
r9             0x7ffff7de7920	140737351940384
r10            0x5e	94
r11            0x7ffff7b97400	140737349514240
r12            0x555555554540	93824992232768
r13            0x7fffffffe2a0	140737488347808
r14            0x0	0
r15            0x0	0
rip            0x4000000100	0x4000000100

```
ASCII Hex-value for 'A' is 41. We can see how it is currently filling rcx and rdx registers, which are usually used for passing 4th and 3rd argument to functions. 
If we go little bit further and overflow some more...


```shell
(gdb) r "$(python -c 'print "A" * 20')"
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /root/Desktop/Shellcode/test "$(python -c 'print "A" * 20')"

#Looking rip register with input size of 20x A characters
rip            0x555555004141	0x555555004141
#Looking at rip register with input size of 21x A characters
rip            0x555500414141	0x555500414141
```

Finally rip register is getting filled with 'A's. This register is somehow meaningful to us.

Let's go some steps back and look a bit deeper.
We suppose now, that our program has function, where this overflow actually occurs. (In this case, instruction +29 uses that function named as *stackoverflow*.) We disassemble the main function, and see the addresses of each instruction:

```shell
Dump of assembler code for function main:
   0x0000555555554771 <+0>:	push   %rbp
   0x0000555555554772 <+1>:	mov    %rsp,%rbp
   0x0000555555554775 <+4>:	sub    $0x10,%rsp
   0x0000555555554779 <+8>:	mov    %edi,-0x4(%rbp)
   0x000055555555477c <+11>:	mov    %rsi,-0x10(%rbp)
   0x0000555555554780 <+15>:	mov    -0x10(%rbp),%rax
   0x0000555555554784 <+19>:	add    $0x8,%rax
   0x0000555555554788 <+23>:	mov    (%rax),%rax
   0x000055555555478b <+26>:	mov    %rax,%rdi
   0x000055555555478e <+29>:	callq  0x55555555473e <stackoverflow>
   0x0000555555554793 <+34>:	mov    $0x0,%eax
   0x0000555555554798 <+39>:	leaveq 
   0x0000555555554799 <+40>:	retq   
End of assembler dump.
```
Address right after stackoverflow function is: **0x0000555555554793**
This is important, as some point we should get into this instruction after completing 'stackoverflow' function.

**This time, execute program without a making buffer overflow**

Let's stop execution of program inside this stackoverflow function, just before the 'unsafe' instruction (in this case: standard library function allowing the buffer overflow), right after it and just before returning from this function, *by using breakpoints in gdb:*

```shell
Dump of assembler code for function stackoverflow:
   0x000055555555473e <+0>:	push   %rbp
   0x000055555555473f <+1>:	mov    %rsp,%rbp
   0x0000555555554742 <+4>:	sub    $0x20,%rsp
   0x0000555555554746 <+8>:	mov    %rdi,-0x18(%rbp)
   0x000055555555474a <+12>:	mov    -0x18(%rbp),%rdx
   0x000055555555474e <+16>:	lea    -0xf(%rbp),%rax
   0x0000555555554752 <+20>:	mov    %rdx,%rsi
   0x0000555555554755 <+23>:	mov    %rax,%rdi
   0x0000555555554758 <+26>:	callq  0x5555555545c0 <ReasonForOverflow>
   0x000055555555475d <+31>:	lea    -0xf(%rbp),%rax
   0x0000555555554761 <+35>:	mov    %rax,%rdi
   0x0000555555554764 <+38>:	mov    $0x0,%eax
   0x0000555555554769 <+43>:	callq  0x5555555545f0 <printf@plt>
   0x000055555555476e <+48>:	nop
   0x000055555555476f <+49>:	leaveq 
   0x0000555555554770 <+50>:	retq   
End of assembler dump.

(gdb) b * 0x555555554758
Breakpoint 1 at 0x555555554758
(gdb) b * 0x55555555475d
Breakpoint 2 at 0x55555555475d
(gdb) b * 0x555555554770
Breakpoint 3 at 0x555555554770
Starting program: /root/Desktop/Shellcode Lab2/Overflow $(python -c 'print "A" * 20')
```
Execute, and after first breakpoint:
Let's have a look for current stack of the program.
There is an interesting address from our main function: **0x55554793**. This was the address of instruction in main function right after of our stackoverflow function.
```shell
Breakpoint 1, 0x0000555555554758 in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe160:	0x00000001	0x00000000	0xffffe597	0x00007fff
0x7fffffffe170:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe180:	0xffffe1a0	0x00007fff	0x55554793	0x00005555
0x7fffffffe190:	0xffffe288	0x00007fff	0x00000000	0x00000002
0x7fffffffe1a0:	0x555547a0	0x00005555	0xf7a42f2a	0x00007fff
(gdb) 
```
Let's continue the execution to breakpoint 2.
Now we have passed by the potential unsafe instruction, what we haven't overflowed this time.
```shell
Breakpoint 2, 0x000055555555475d in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe160:	0x00000001	0x00000000	0xffffe59d	0x00007fff
0x7fffffffe170:	0x41414100	0x41414141	0x41414141	0x00414141
0x7fffffffe180:	0xffffe1a0	0x00007fff	0x55554793	0x00005555
0x7fffffffe190:	0xffffe288	0x00007fff	0x00000000	0x00000002
0x7fffffffe1a0:	0x555547a0	0x00005555	0xf7a42f2a	0x00007fff
(gdb) 
```
We can see, that address of **0x55554793** is still there. Additionally stack contains some 'A' letters, what we have used as input.
Let's execute to final breakpoint:



```shell
Breakpoint 3, 0x0000555555554770 in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe188:	0x55554793	0x00005555	0xffffe288	0x00007fff
0x7fffffffe198:	0x00000000	0x00000002	0x555547a0	0x00005555
0x7fffffffe1a8:	0xf7a42f2a	0x00007fff	0x00000000	0x00000000
0x7fffffffe1b8:	0xffffe288	0x00007fff	0x00040000	0x00000002
0x7fffffffe1c8:	0x55554771	0x00005555	0x00000000	0x00000000
(gdb)
```
So, the 3rd breakpoint was in last instruction (retq) of stackoverflow function. Looking at the stack above, current rsp is the address in main function, the one right after our stackoverflow function. Program should end normally, if we still continue. We have executed program without making buffer overflow.

What is the content of stack if we the execute program, by causing the buffer overflow to program?

Stack information in first breakpoint should stay same, but let's have a look on second breakpoint again, which is right after when overflow occurs.
```shell
(gdb) r $(python -c 'print "A" * 26')
Starting program: /root/Desktop/Shellcode Lab2/Overflow $(python -c 'print "A" * 26')

Breakpoint 1, 0x0000555555554758 in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe150:	0x00000001	0x00000000	0xffffe591	0x00007fff
0x7fffffffe160:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe170:	0xffffe190	0x00007fff	0x55554793	0x00005555
0x7fffffffe180:	0xffffe278	0x00007fff	0x00000000	0x00000002
0x7fffffffe190:	0x555547a0	0x00005555	0xf7a42f2a	0x00007fff
(gdb) continue
Continuing.

Breakpoint 2, 0x000055555555475d in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe150:	0x00000001	0x00000000	0xffffe591	0x00007fff
0x7fffffffe160:	0x41414100	0x41414141	0x41414141	0x41414141
0x7fffffffe170:	0x41414141	0x41414141	0x00414141	0x00005555
0x7fffffffe180:	0xffffe278	0x00007fff	0x00000000	0x00000002
0x7fffffffe190:	0x555547a0	0x00005555	0xf7a42f2a	0x00007fff
(gdb) 

```
With suitable amount of buffer overflow, our 'A' letters starts to fill more addresses than they should, replacing previously seen address **0x55554793**.

It's essential to think how stack works:
When function is called, arguments are usually passed backwards into stack before the actual calling of function. (Depending also on complier: 64 - bit systems could be using fastcall, which means that four first parameters are coming from registers.) Next, address where function should return, and old rbp address are pushed to stack.

Further, local variables have been defined, and suitable space in stack is reserved for them.

Continue to last breakpoint:
```shell
Breakpoint 3, 0x0000555555554770 in stackoverflow ()
(gdb) x/20x $rsp
0x7fffffffe178:	0x00414141	0x00005555	0xffffe278	0x00007fff
0x7fffffffe188:	0x00000000	0x00000002	0x555547a0	0x00005555
0x7fffffffe198:	0xf7a42f2a	0x00007fff	0x00000000	0x00000000
0x7fffffffe1a8:	0xffffe278	0x00007fff	0x00040000	0x00000002
0x7fffffffe1b8:	0x55554771	0x00005555	0x00000000	0x00000000
(gdb) 
```
Current rsp address is not the instruction address (0x55554793) in main function anymore.

If we continue executing the program:

```
(gdb) stepi
0x0000555500414141 in ?? ()
(gdb) nexti

Program received signal SIGSEGV, Segmentation fault.
0x0000555500414141 in ?? ()
(gdb) 
(gdb) print /x $rip
$1 = 0x555500414141
```

And we are back to wondering about this rip register.