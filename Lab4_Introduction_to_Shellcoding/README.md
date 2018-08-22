Lab 4: Introduction to Shellcoding and a bit more
====

Input validation and sanitization is one of the major challenges in software development. Improperly implemented validation and sanitization could lead to unexpected or unwanted situations, which have negative effect for functionality and thus security of software.

Buffer overflows and buffer over-reads should be familiar topic from the lectures. These are some of the results from invalid input validation, and could lead in the worst case to possibility of arbitrary code execution in the system of vulnerable program.

Misusing these flaws with specified payloads has been used as a classic way to get unauthorized shell access to compromised system. This method can be called as 'shellcoding', as **traditionally** shellcoding refers to anything, when piece of code is used as 'payload'  to get local or remote shell access. The meaning of this term has evolved: nowadays goal could be any imaginable task. 

Executing payloads in vulnerable program could lead to privilege escalation. Vulnerable program which is running with system privileges, could execute arbitary code with same privileges. Therefore if payload is able to spawn shell, it's done with system privileges. Aquiring shell access this way usually leads to full control of the system. This has lead shell spawning to be one of the most common goals of attackers.

The intention of this exercise is to achieve hands-on experience by exploring software with improperly validated input. Further, by taking advantage of shellcoding, we should be aware of dangers what unintended behaviour of software could inflict to overall system.

 *The goal or intention of this exercise is **not** to courage to abuse or instruct these skills for something inappropriate. Can systems be truly secure, if they can't handle open discuss and testing?*

---
Grading
---
Make a short step-by-step report (what, why and how) of following tasks, and include source codes and the most important command line commands used in those tasks. It's recommended to read all tasks before starting. Actual instruction for what to do, is ***in bold and italics*** on each task.

You are elgible to following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate some poorly implemented ones.
*Upper grade requires that all previous tasks have been done as well.*

It is estimated, that you are able to do Tasks 1 & 2 during lab session (4 hours).

Tasks 3 & 4 are more advanced than earlier ones. Implementation will very likely take time outside of lab.

Task|Grade/Level|Description|
----|:---:|-----------|
[Task 1](#task-1--basics-of-buffer-overflows "Task 1 : Basics of buffer overflows") | - |  Analyzing buffer overflow and changing execution flow
[Task 2](#task-2--arbitary-code-execution "Task 2 : Arbitary code execution") | 2 - 3| Arbitary code execution in vulnerable program
[Task 3](#task-3--defeating-no-execute "Task 3 : Defeating No-eXecute") | 4 | Code reuse attack techniques: ret2libc & ROP
[Task 4](#task-4--a-bit-more-advanced-rop-implementation "Task 4 : A bit more advanced ROP implementation") | 5 | Taking ROP to next level

By completing Task 1 and Task 2 A&B, you are eglible for passing the lab and getting minimum grade 2 from this lab. Completion of C part increases grade to 3.

Grade 1 can be aquired by doing lecture tasks/diary from the corresponding lectures.

Difficulty on tasks is expected to be exponentially raising as you go forward with them. Without understanding of previous task, next one could be very ambiguous.

*Return completed tasks to your private GitHub repository!
There will be answer template or more instructions.*

---

Some prerequisites
---

You have to use C/C++ programming language in cases, when you want to create program with buffer overflow vulneralibity.

At this point, you should have basic knowledge about how computer stack/memory and registers are working.

Tasks are possible to do in both 32 - and 64 bit machine instructions as long as machine has support for them. Implementation will differ and be more challenging depending on version. It's recommended to use 32 - bit version, as you can find more examples from it: it could be generally easier to start with.

Tasks have been tested in Kali Linux x86_64 (Debian 4.14.12) and Ubuntu 18.04 LTS. Task 3A is not possible to do with latest Ubuntu.

You might have to note following Linux protections

* Stack canaries (SSP)
* Non-executable pages or stacks (NX)
* Address Space Layout Randomization (ASLR)
* Less known, no need to note unless specified in task: (ASCII ARMOR, RELRO, PIE, D_FORTIFY_SOURCE, PTR_MANGLE)

Find a way to disable them if needed.
The most are compiler options.

More information about protections in Ubuntu (and overall) can be found [here](https://wiki.ubuntu.com/Security/Features).

On later tasks, we try to bypass some of them: specifically mentioning not to disable them.


### More readings for those who have interested:

A bit outdated but still excellent book for getting solid grasp of basics: 
*The Shellcoder's Handbook: Discovering and Exploiting Security Holes (Chris Anley, Felix Lindner,  Gerardo Richarte and John Heasman)*

## Advanced tools used in  this exercise

These are recommended to use in later tasks:
* [radare2](https://github.com/radare/radare2) - advanced disassembler and forensics tool
* [pwntools](https://github.com/Gallopsled/pwntools) - controlled generation and execution of payloads

These can be used in first tasks as well, but it is not necessary.

---
Task 1 : Basics of buffer overflows
------
In this first task, we are using simple program with buffer overflow vulneralibity for analyzing the behaviour of system. With specifically crafted input, we will change the behaviour to something unintended for purpose of the program, but intended to us.

### A) Using program with improper input validation and analyzing overflow.
 
We want to understand very basics of what is actually happening in the stack and in the registers of the machine at the time when overflow occurs.

Short intro to buffer overflows and analyzing tutorial can be found [here](Tutorials/Tutorial1A_Analyzing_overflow.md).

Try it out by yourself. It is not necessary, if you are already very familiar with topic and able to answer to bolded questions.

Based on analyzing tutorial:

What makes this particular (rip) register so interesting? What does ret instruction have to do with rip register in most cases of buffer overflows?

This leads to conclusion, that in most cases we might need to put our buffer overflow in external function, and it's recommended to do so in this lab for not making things too hard. Depending on Operating System and architecture (x86/x64), overflowing return address of main function might not be that easy.

> ***Explain shortly the role of the rip register and ret instruction, and why we are interested about them. Explain what is causing the overflow in [example program. ](Info/Buffer_overflows.md).  Further, analyze this program with gdb and try to find suitable size for overflow (padding size), which starts to fill up instruction pointer register. You can also make your own program, if you want.***

### B) Adding hidden (non-used) function to previous program. (And still executing it)

In short introduction to buffer overflows at previous task, there was an example about accessing secret data by just overflowing the input. In this task, we are willing to do something similar, in a bit different way. We are changing the execution flow of program to something we want.

Let's add a new function to previously used program , but never actually use it.

We are going to execute this function by overflowing program with specified input (in other words, with our crafted payload). 

This payload uses some memory address what you should be able to figure out based on tutorial in A section. Suitable padding should be used that address can be overflowed to right place. Shortly, by *overflowing to correct place (with specific size of padding) with correct memory address , execution can jump to location of this memory address. Increase padding little by little.*

Example scenario would be something like this. The function which is never actually called, is printing something and opening shell:

```shell
# ./Overflow $(python -c 'print "A" * 10')
AAAAAAAAAA
# .$(python -c 'print "A" * 20 + "\x11\x11\x11\x11"')
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGUUUUAccidental shell access appeared
# exit
exit
Illegal instruction
#

```
Note, that using script like above expects that program is taking input as argument. Also, the way how memory address is actually used as input, is not so straightforward. (Is your system Little- or Big-endian?)

You probably have to disable protections meantioned in prerequisities to be able to succeed.

> ***Find a way to disable these protections. Use gdb or similar program to analyze your program. Disassembling might be helpful. Find suitable address, and figure out what should be overflowed with it and how to get correct values into it, and finally execute function this way.***

Tip: If your hidden function contains printing - add newline ending to string. Otherwise it might not be printing anything what can be actually seen.


---
Task 2 : Arbitary code execution
----
The goal of this task is to create bit more advanced payload: some arbitary code that we are willing to execute, by passing it to our previously created vulnerable program. Notably this means execution of our own program inside of another program.

In practise, first we need functionality for payload in C/C++ code, and then it should be transformed to machine code. Transform means in this case rewriting: it is not good idea to get assembly code from your binary, which you made earlier.

 Later this machine code should be combined with other instructions to be suitable as payload. 

It's not necessary to do functionality in C/C++ at first, if the assembly language is well known, but we are doing it now for learning purposes.

Finally our machine code is somehow executed in vulnerable program.

Extra: Maybe the most known white paper about this method can be found [here][0].

### A) Making a simple program to open Shell.

 The origin of shellcoding was to access to shell with usage of speficially crafted payloads.
 Let's respect the traditions. It should be easy to understand.

> ***Make a simple program, which opens local shell. Example would be in execution like this:***

```shell
# gcc -o simpleshell Simpleshell.c 
# ./simpleshell 
# exit
# 
```
This program represents functionality of our later arbitary code.


### B) Transforming functionality to machine instructions

 To be able to execute arbitary code in our vulnerable program we made in Task 1, we need to transfer payload functionality to direct machine instructions.
 
 This means that we are going to turn code into assembly code, and further transforming it into shellcode. In the other words, rewriting previous functionality from A task into IA-32 assembly. (Or other instruction set, if system does not support this.)

You can find short introduction to assembly and shellcoding here: https://0x00sec.org/t/linux-shellcoding-part-1-0/289 

And some more here:
http://hackoftheday.securitytube.net/2013/04/demystifying-execve-shellcode-stack.html


It's possible to this for x86 or x64 machines, but x86 (32 - bit) version is recommended.

Final shellcode could look something like this (but it's probably longer):

```shell
\x62\x69\x89\xe3\x31\x6e\x2f\x73\x6\x31\xc0\x50\x68
```

You should confirm, that your shellcode is actually working. There are examples in both provided links. Vulnerable binary must be compiled for same instruction set(x86/x64) than shellcode.

> ***Transfer (rewrite) your C/C++ code functionality as it is to assembly and further to shellcode.***


### C) Making the final payload and executing it

At this point our executable part of payload should be ready-to-go. The question then arises: how we can actually execute whole payload in a vulnerable program?

Previously in Task 1 we have executed specific function from vulnerable program by using crafted payload, which contained just one address in addition of padding, which filled the input buffer.

We can probably still use same vulnerable program again for executing payload. You still have to compile vulnerable program correctly to disable some protections.

This time we are executing arbitary code, which is probably totally unrelated to vulnerable program. We are using virtual space of other program to run our own program.

Once we have confirmed, that executable payload is working (should have been done in the end of 2B ), we can go forward.

The idea for executing this payload:

1. Store executable instructions to memory space of the program
2. Somehow make machine to execute payload as program from the start of this location.

Storing itself isn't a problem, payload goes as input to the program. As we are storing payload inside the program, *executable instructions should not overflow*. Your program's size for input should be enough: your executable instructions can fit there.

At this point you should know the size of your payload in bytes. Increase the buffer size of vulnerable program if needed.

Try to find suitable padding before proceeding now, so you can overflow return addresses. You can test it like in Task 1.

In this case, more likely the problem is to find  out the address of the beginning of our payload, and then execute it. There are many ways to achieve this, but here are few examples:

1. At the time of program execution, when input is actually used and stored, you can try to disassemble registers and addresses (Maybe right after execution of unsafe library function?), and try to find your payload instructions. If you find permanent place, you could try to figure out the address of it, and call your code from there. You can try this in gdb first, but address outside of it should not be hard to guess afterwards. Think about how local variables or function parameters are stored. This could guide you to look at for correct place.

2. Another choice is just to guess the location of shellcode. We have disabled some protections, so we know, that in every program, stack starts from same address. We just need to guess the correct offset from it. Manually this could be very hard. You could try create script, which finds base address, changes address, and tries to run payload each time on it.

> ***Make a step-by-step report like previously (what, why and how), including command line commands and sourcefiles you used to success of executing arbitary code on vulnerable program,by finally opening local shell outside of GDB.***

Tip: *Does NOP sled sound familiar?*

---
Task 3 : Defeating No-eXecute
----
In previous task we have executed some arbitary code straight from the stack. This is bit simple and old method, and has been prevented some (long) time ago.

NX - bit (no-eXecute) [was created][1] to separate areas in memory for storage of instructions and for storage of data.
Processors will not execute data marked by NX - bit; in practice data which is just 'data'.

This makes execution of our payload in the stack very hard, in case when it is stored as input to vulnerable program's memory area.

But what if we are *not* executing code in the stack?
Previous prevention method has lead to forming of *code reuse attack techniques* (ret2libc, ROP, JOP, COOP etc.). These techniques are focusing on to using existing code to build required functionality. But from where to get code for reusing?

*Presence of ASLR could be bypassed with speficic implementation and combination of these techniques as well, but that will be left outside of this exercice, as it makes things a bit more complicated. Usually it requires information leak aswell. By default it will probably prevent everything what we are doing next.*

From previously mentioned techniques, we are taking short glance to ret2libc and ROP, which are some basic and original techniques.

### A) Return-to-libc (aka ret2libc)

One solution for this is... are libraries. Spefically: dynamic libraries, which are launched during only at the execution of the program.
We can safely say, that it's very rare case if program is not using any libraries.

Library functions are not marked by NX - bit : they are existing instructions. By overflowing stack suitably, we might be able to execute library function with parameters we want.
We could craft our payload in intention of using functions from libraries by overflowing return addresses to point towards them.
Reusing functions of vulnerable program is possible as well, but it might not be that beneficial.

One very common library is **libc** (which probably named this method as 'ret2libc'), which grants a lot of flexibility. And the most useful function from there, could be *system()*. By giving */bin/sh* as an argument, we could start a shell.
If we somehow can pass correct argument to system() function, code isn't executed in stack, it's executed in the address of system(). This was one of the eariliest methods to bypass NX protection.

> ***In this task, you should make example implementation of this ret2libc method. It could be for example spawning local shell. This time, **do not** disable NX protection (do not use -z execstack flag in compiler). Disabling other protections is still required. Like previously, make step by step report(what, why, how) including possible source files and command line commands which lead you to get shell access.***

To be noted: 
* You should check, if ASCII Armoring is present in your system. It should be disabled additionally for this task. In some systems, it might not be possible. It is recommended to use Kali Linux in this task.
* This task is much easier to get done with 32 - bit binaries, because of they way how function parameters are passed in practice, when compared to 64-bit system. (Stack vs registers?)

One simple implementation can be found from [this][2] paper for example.

Extra: Method was firstly introduced [here][3].

### B) Return-oriented programming (aka ROP)

Return-to-libc method brings some limitations: we are very dependant about the libraries' functions and arguments (and vulnerable program's text segment's). Sometimes the overall functionality what we are willing to achieve is very hard to implement with just pure existing functions. With ret2libc technique, pure function calls with parameters are limited only to two calls. This will be explained later.

Return-oriented programming is more sophisticated version of ret2libc;
instead of reusing library functions, we are additionally reusing **code chunks** (instruction
sequences) from libraries and from the program itself. These areas are in program's executable memory.

In practise, we are using these sequences, which ends to **ret** instrcution. This instruction is meaningful to us, as we can chain these code chunks (which are usually called as 'gadgets') to build the actual 'bigger' code we need. After gadget is executed, execution flow can be set so, that new gadget will be executed, and so on. By using some special gadgets, we can control the stack so, that we can chain these calls as much as we want.

Intel style example maybe as simple as it can get:
```shell
pop eax ;ret
```
By giving enough reusable code, ROP is [*Turing complete*][4].

But how we are actually getting and executing these gadgets?

 We could manually disassemble binaries and look for them, but that could take a lot of effort. Luckily there are now some tools what we are able to use.

One very frequently updated and multipurpose tool - [radare2](https://github.com/radare/radare2) is used as example.
Let's use once again our vulnerable program as target what we created in Task 1. Tutorial for ROP and example for using radare2 (and pwntools) with it, is [here. ](Tutorials/Tutorial3B_Radare2_and_gadgets.md) 
Pwntools is Python library, which helps to generate more controllable and readable payload.

Simple, but practical demonstration of ROP technique can be found [here](https://tc.gtisc.gatech.edu/cs6265/2016/l/lab07-rop/README-tut.txt).

Extra: White paper introducing the ROP can be found [here][5].

> ***Try to get previously mentioned example (ROP_hello) [here](src/pwntools_example/ROP_hello.py) to work by yourself. Next, make simple example implementation of ROP technique. This could be spawning a local shell for example. To not make it same as ret2libc method, print some text before spawning shell, and print also something after exiting the shell. In this way we can apply some ROP - chain.***

Tip: If you are being bit unlucky, and are facing some function addresses containing null bytes in non-Ascii-Armored system, try out some alternative functions. For example putchar function has putchar_unlocked alternative.

---
Task 4 : A bit more advanced ROP implementation
----
Ready for some challenge?

Implement **one** of the described following tasks, and make step-by-step report (what,why and how) for what you did:

* Complete *two* challenges here: https://ropemporium.com/
It's recommended, that ret2win challenge is the first and another one of them. Especially in this task, we are more interested about explanations (what/why) than commands or payloads itself. Take care of doing report!


* You can make simple example ROP implementation in **32-bit**(or in 64-bit, it's not restricted) system, which bypasses **ASLR**. (Is .text segment always randomized? Or is ret2plt method familiar?). You can create suitable vulnerable program yourself.

* You can make simple example ROP implementation, which bypasses **stack canaries (aka cookies)**. (Compile with '-fstack-protector-all' - flag)
You can create suitable vulnerable program yourself.

* Do following pieces of code look familiar? This describes common way to open *remote* shell access. Make an attack implementation of remote shell with NX protected binary. You can find working assembly/C-code [here](src/remoteShell), which can help to understand, what payload could contain.

``` c
dup2(s, 0);
dup2(s, 1);
dup2(s, 2);
execve("/bin/sh", 0, 0);
```


* **Something interesting** in shellcoding, but we haven't dealt with it yet?
Feel free to implement and show us what you got. It does not necessary need to be related for ROP. **Your task has to be approved by assistant before you can start doing it.** Depending on estimated workload, this task could be extendable to final coursework.



[//]: # (Hidden sourcelist for providing all the links.)

[0]: http://www.cs.umd.edu/class/fall2017/cmsc414/readings/stack-smashing.pdf "Aleph One(Elias Levy)  - Smashing The Stack For Fun And Profit"

[1]: https://www.scribd.com/document/60416747/NX-bit "Argento Daniele, Boschi Patrizio & Del Basso Luca - NX bit : A hardware-enforced BOF protection"

[2]: https://www.shellblade.net/docs/ret2libc.pdf "InVoLuNTaRy - Performing a ret2libc Attack : Defeating a non-executable stack"

[3]: http://seclists.org/bugtraq/1997/Aug/63 "Solar Designer (Alexander Peslyak) - Getting around non-executable stack (and fix)"

[4]: https://www.sba-research.org/wp-content/uploads/publications/woot12.pdf "Andrei Homescu,
Michael Stewart,
Per Larsen,
Stefan Brunthaler &
Michael Franz  - 
Microgadgets: Size Does Matter In Turing-complete Return-oriented
Programming"

[5]: https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf "Hovav Shacham - The Geometry of Innocent Flesh on the Bone: Return-into-libc without Function Calls (on the x86)"
