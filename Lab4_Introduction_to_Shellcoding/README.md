Computer Security Lab 4: Introduction to Shellcoding and a bit more
====

Responsible person/main contact: Niklas Saari

## Preliminary tasks
It would be good to read the background and prerequisites sections beforehand.

Particularly, the article presented by Aleph One offers a good introduction to stacks and their legacy (and current) vulnerabilities. This can be found from [here.](http://phrack.org/issues/49/14.html#article)

Background
---

Input validation and sanitization is one of the major challenges in software development. Improperly implemented validation and sanitization could lead to unexpected or unwanted situations, which have a negative effect on functionality and thus security of software.

Buffer overflows and buffer over-reads should be a familiar topic from the lectures. These are some of the results from invalid input validation, and could lead in the worst case to the possibility of arbitrary code execution in the system of a vulnerable program.

Misusing these flaws with specified payloads has been used as a classic way to get unauthorized shell access to the compromised system. This method can be called as 'shellcoding', as **traditionally** shellcoding refers to anything, when a piece of code is used as a 'payload'  to get local or remote [shell](https://en.wikipedia.org/wiki/Shell_(computing)) access. The meaning of this term has evolved: today's goal could be any imaginable task.

Executing payloads in vulnerable programs could lead to privilege escalation. Vulnerable program which is running with system privileges could execute arbitrary code with the same privileges. Therefore, if a payload is able to spawn a shell, it's done with system privileges (read more about SUID [here](https://vickieli.medium.com/becoming-root-through-an-suid-executable-47473173a6ec)). Acquiring shell access this way usually leads to full control of the system. This has led to shell spawning to be one of the most common goals of attackers. History of shellcoding traces back to an explanation in the article of Aleph One, introduced in [here.](http://phrack.org/issues/49/14.html#article)

The intention of this exercise is to achieve hands-on experience by exploring software with improperly validated input. Further, by taking advantage of shellcoding, we should be aware of the dangers that unintended behavior of software could inflict on the overall system.

 *The goal or intention of this exercise is **not** encourage abuse or instruct these skills for something inappropriate. Can systems be truly secure, if they can't handle open discussion and testing?*

---
Grading
---
<details open><summary>Details </summary>
Make a short step-by-step report (what, why and how) of following tasks, and include source codes and the most important command line commands used in those tasks. It's recommended to read all tasks before starting. Actual instruction for what to do, is ***in bold and italics*** on each task.

You are eligible for the following grades in this exercise by doing tasks as defined. Great ideas and implementations could compensate for some poorly implemented ones.
*Upper grade requires that all previous tasks have been done as well.*

It is estimated that you are able to do Tasks 1 & 2 during the lab session (4 hours).

Tasks 3 & 4 are more advanced than earlier ones. Implementation will very likely take much more time.

Task|Grade/Level|Description|
----|:---:|-----------|
[Task 1](#task-1--basics-of-buffer-overflows "Task 1 : Basics of buffer overflows") | 1 |  Analyzing buffer overflow and changing execution flow
[Task 2](#task-2--arbitrary-code-execution "Task 2 : Arbitrary code execution") | 2 - 3| Arbitrary code execution in vulnerable program
[Task 3](#task-3--defeating-no-execute "Task 3 : Defeating No-eXecute") | 4 | Code reuse attack techniques: ret2libc & ROP
[Task 4](#task-4--a-bit-more-advanced-rop-implementation "Task 4 : A bit more advanced ROP implementation") | 5 | A bit more advanced ROP implementation

By completing Task 1, grade 1 can be achieved.

By doing Task 2 A&B, you are eligible for grade 2 from this lab. Completion of C part increases grade to 3.

Difficulty on tasks is expected to be exponentially rising as you go forward with them. Without understanding the previous task, the next one could be very ambiguous.

*Return completed tasks to your private GitHub repository!
There will be an answer template.*

</details>

---

Some prerequisites
---
This exercise is recommended to do with Kali Linux.

You have to use C/C++ programming language in cases when you want to create a program with buffer overflow vulnerability.

At this point, you should have basic knowledge about how computer stack/memory and registers are working.

Tasks are possible to do in both 32 - and 64 bit machine instructions as long as the machine has support for them. Implementation will differ and be more challenging depending on the version. It's recommended to use the 32 - bit version, as you can find more examples from it: it could be generally easier to start with.

Tasks have been tested in Kali Linux x86_64. Task 3A is not possible to do with the latest Ubuntu, Arch Linux or any mature Linux environment which is intended for daily use.

On Kali Linux, you might need to install 32-bit support for `gcc`. This can be done as
```console
sudo apt-get update && sudo apt-get install gcc-multilib -y
```

You might have to note following Linux protections

* Stack canaries (SSP)
* Non-executable pages or stacks (NX)
* Address Space Layout Randomization (ASLR)
* Less known, no need to note unless specified in task: (ASCII ARMOR, RELRO, PIE, D_FORTIFY_SOURCE, PTR_MANGLE)

> Check from [here](https://www.win.tue.nl/~aeb/linux/hh/protection.html) for some compiler flags.

Find a way to disable them if needed.
Most are compiler options.

More information about protections in Ubuntu (and overall) can be found [here](https://wiki.ubuntu.com/Security/Features).

On later tasks, we try to bypass some of them: specifically mentioning not to disable them.

**Encoding really matters in these tasks, for example Python 2 print produces *just* data, whereas Python 3 print produces *encoded string* by default.** 

### More readings for those who are interested:

A bit outdated but still an excellent book for getting a solid grasp of the basics: 
*The Shellcoder's Handbook: Discovering and Exploiting Security Holes (Chris Anley, Felix Lindner,  Gerardo Richarte and John Heasman)*

## Advanced tools used in this exercise

These are recommended to use in later tasks:
* [radare2](https://github.com/radare/radare2) - advanced disassembler and forensics tool
* [pwntools](https://github.com/Gallopsled/pwntools) - controlled generation and execution of payloads

These can be used in first tasks as well, but it is not necessary.

---
Task 1 : Basics of buffer overflows
------
In this first task, we are using a simple program with buffer overflow vulnerability for analyzing the behavior of the system. With specifically crafted input, we will change the behavior to something unintended for the purpose of the program, but intended to us.

### A) Using a program with improper input validation and analyzing overflow.
 
We want to understand the very basics of what is actually happening in the stack and in the registers of the machine at the time when overflow occurs.

> Short intro to buffer overflows and analyzing tutorial can be found [here](Tutorials/Tutorial1A_Analyzing_overflow.md).

Try it out by yourself. It is not necessary, if you are already very familiar with the topic and able to answer bolded questions.

Based on analyzing tutorial:

What makes this particular (`rip`) register so interesting? What does `ret` instruction have to do with `rip` register in most cases of buffer overflows?

This leads to the conclusion, that in most cases we might need to put our buffer overflow in an external function, and it's recommended to do so in this lab for not making things too hard. Depending on Operating System and architecture (x86/x64), overflowing the return address of the main function might not be that easy.

You can do this task as 32 - bit or 64 - bit versions. By default, the program is compiled as 64-bit in provided Kali Linux. By changing compiler flags, the program can be compiled as 32-bit as well.

In this case, stack canaries might cause problems if you are using a distribution other than Kali Linux. Those have to be disabled.

> ***Explain briefly the role of the `rip` register and `ret` instruction, and why we are interested in them. Explain what is causing the overflow in [example program. ](src/vuln_progs/Overflow.c).  Further, analyze this program with gdb and try to find a suitable size for overflow (padding size), which starts to fill up the instruction pointer register. You can also make your own program, if you want.***

### B) Adding hidden (non-used) function to previous program. (And still executing it)

In a short introduction to buffer overflows at the previous task, there was an example about accessing secret data by just overflowing the input. In this task, we are willing to do something similar, in a bit different way. We are changing the execution flow of the program to something we want.

Let's add a new function to the previously used program , but never actually use it.

We are going to execute this function by overflowing the program with specified input (in other words, with our crafted payload). 

This payload uses some memory address that you should be able to figure out based on the tutorial in section A. Suitable padding should be used so that the address can be overflowed to the right place. Shortly, by *overflowing to the correct place (with specific size of padding) with the correct memory address , execution can jump to the location of this memory address. Increase padding little by little.*

Example scenario would be something like this. The function which is never actually called, is printing something and opening the shell:

```shell
# ./Overflow $(python -c 'print "A" * 10')
AAAAAAAAAA
# ./Overflow $(python -c 'print "A" * 20 + "\x11\x11\x11\x11"')
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGUUUUAccidental shell access appeared
# exit
exit
Illegal instruction
#

```
Note, that using a script like above expects program to take input as an argument. Also, the way memory address is actually used as input, is not so straightforward. (Is your system Little- or Big-endian?)

You probably have to disable protections mentioned in prerequisites to be able to succeed. In this case, stack canaries might cause problems, if you are using distribution other than Kali Linux.



> ***Find a way to disable these protections. Use gdb or similar programs to analyze your program. Disassembling might be helpful. Find a suitable address, and figure out what should be overflowed with it and how to get the correct values into it, and finally execute the function this way.***

Tip: If your hidden function contains printing - add a newline ending to the string. Otherwise it might not be printing anything that can be actually seen.


---
Task 2 : Arbitrary code execution
----
The goal of this task is to create a bit more advanced payload: some arbitrary code that we are willing to execute, by passing it to our previously created vulnerable program. Notably this means execution of our own program inside of another program.

In practice, first we need functionality for payload in C/C++ code, and then it should be transformed to machine code. Transform means in this case rewriting: *it is **NOT** a good idea to get assembly code automatically from your binary*, which you made earlier. 

 Later this machine code should be combined with other instructions to be suitable as a payload. 

It's not necessary to do functionality in C/C++ at first, if the assembly language is well known, but we are doing it now for learning purposes.

Finally our machine code is somehow executed in the vulnerable program.

Extra: Maybe the most known white paper about this method can be found [here][0].

### A) Making a simple program to open Shell.

 The origin of shellcoding was access to shell with usage of specifically crafted payloads.
 Let's respect the traditions. It should be easy to understand.

> ***Make a simple program, which opens a local shell. Example would be execution like this:***

```shell
# gcc -o simpleshell Simpleshell.c 
# ./simpleshell 
# exit
# 
```
This program represents functionality of our later arbitrary code.


### B) Transforming functionality to machine instructions

 To be able to execute arbitrary code in our vulnerable program we made in Task 1, we need to transfer payload functionality to direct machine instructions.
 
 This means that we are going to turn C/C++ code into assembly code, and further transform it into shellcode. In the other words, **rewriting** (do not try to generate automatically with gcc for example) previous functionality from A task into IA-32 assembly. (Or other instruction set, if the system does not support this.)

You can find a short introduction to assembly and shellcoding here: https://0x00sec.org/t/linux-shellcoding-part-1-0/289 

And some more here:
http://hackoftheday.securitytube.net/2013/04/demystifying-execve-shellcode-stack.html

And one post more: https://dhavalkapil.com/blogs/Shellcode-Injection/

It's possible to do this for x86 or x64 machines, but the x86 (32 - bit) version is recommended.

Final shellcode could look something like this (but it's probably longer):

```shell
\x62\x69\x89\xe3\x31\x6e\x2f\x73\x6\x31\xc0\x50\x68
```

You should confirm that your shellcode is actually working. There are examples in both provided links. Vulnerable binary must be compiled for the same instruction set (x86/x64) than shellcode.

> ***Transfer (rewrite) your C/C++ code functionality as it is to assembly and further to shellcode.***

**NOTE**: It seems that provided virtual machines do have additional protections in these days by having too up-to-date kernel. When testing your shellcode by assinging it into the variable, take a look for [mprotect](https://man7.org/linux/man-pages/man2/mprotect.2.html) syscall, which can be used to make static variables executable again. Example usage can be seen for example [here.](https://gist.github.com/securitytube/5318838#gistcomment-3614284) 

One Stackoverflow post about explaining this matter can be found in [here.](https://stackoverflow.com/questions/9960721/how-to-get-c-code-to-execute-hex-machine-code/55893781#55893781)

### C) Making the final payload and executing it

At this point our executable part of the payload should be ready-to-go. The question then arises: how can we actually execute the whole payload in a vulnerable program?

Previously in Task 1 we have executed a specific function from the vulnerable program by using a crafted payload, which contained just one address in addition to padding, which filled the input buffer.

We can still use the same vulnerable program again for executing payload. You still have to compile the vulnerable program correctly to disable some protections.

This time we are executing arbitrary code, which is probably totally unrelated to the vulnerable program. We are using the virtual space of another program to run our own program.

Once we have confirmed that the executable payload is working (should have been done at the end of 2B ), we can go forward.

The idea for executing this payload:

1. Store executable instructions to memory space of the program
2. Somehow make the machine execute the payload as a program from the start of this location.

Storing itself isn't a problem, payload goes as input to the program. As we are storing payload inside the program, *executable instructions should not overflow, as otherwise code might be split and it won't work*. Your program's size for input should be enough: your executable instructions can fit there.

At this point you should know the size of your payload in bytes. Increase the buffer size of the vulnerable program if needed.

Try to find suitable padding before proceeding now, so you can overflow return addresses. You can test it like in Task 1.

In this case, more likely the problem is to find  out the address of the beginning of our payload, and then execute it. There are many ways to achieve this, but here are few examples:

1. At the time of program execution, when input is actually used and stored, you can try to disassemble registers and addresses (Maybe right after execution of an unsafe library function?), and try to find your payload instructions. If you find a permanent place, you could try to figure out the address of it, and call your code from there. You can try this in gdb first, but addresses outside of it should not be hard to guess afterwards. Think about how local variables or function parameters are stored. This could guide you to look for the correct place.

2. Another choice is just to guess the location of the shellcode. We have disabled some protections, so we know that in every program, the stack starts from the same address. We just need to guess the correct offset from it. Manually this could be very hard. You could try to create a script, which finds the base address, changes the address, and then tries to run the payload each time on it.

You can do this task at first inside GDB, to run your arbitrary code for finally opening the shell.

To get full points from this task, you should execute it outside of GDB.

More information can be found [here][0], how to succeed.

In GDB, ASLR is not enabled by default. When you want to spawn the shell outside of gdb, you have to disable ASLR manually. This can be done with:
```
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space 
```

> ***Make a step-by-step report like previously (what, why and how), including command line commands and sourcefiles you used to successfully execute arbitrary code on the vulnerable program, by finally opening the local shell outside of GDB.***

Tip: *Does the NOP sled sound familiar?*

---
Task 3 : Defeating No-eXecute
----
In previous the task we have executed some arbitrary code straight from the stack. This is a bit simple and old method, and has been prevented some (long) time ago.

NX - bit (no-eXecute) [was created][1] to separate areas in memory for storage of instructions and for storage of data.
Processors will not execute data marked by NX - bit; in practice data which is just 'data'.

This makes execution of our payload in the stack very hard, in case when it is stored as input to the vulnerable program's memory area.

But what if we are *not* executing code in the stack?
THe previous prevention method has led to forming of *code reuse attack techniques* (ret2libc, ROP, JOP, COOP etc.). These techniques are focusing on using existing code to build required functionality. But from where to get code for reusing?

*Presence of ASLR could be bypassed with specific implementation and combination of these techniques as well, but that will be left outside of this exercise, as it makes things a bit more complicated. Usually it requires information leakage as well. By default it will probably prevent everything that we are doing next.*

From previously mentioned techniques, we are taking a short glance at ret2libc and ROP, which are some basic and original techniques.

### A) Return-to-libc (aka ret2libc)

One solution for this is... are libraries. Specifically: dynamic libraries, which are launched only during at the execution of the program.
We can safely say that it's a very rare case if a program is not using any libraries.

Library functions are not marked by NX - bit : they are existing instructions. By overflowing the stack suitably, we might be able to execute library functions with parameters we want.
We could craft our payload with the intention of using functions from libraries by overflowing return addresses to point towards them.
Reusing functions of the vulnerable program is possible as well, but it might not be that beneficial.

One very common library is **libc** (which probably named this method as 'ret2libc'), which grants a lot of flexibility. And the most useful function from there, could be *system()*. By giving */bin/sh* as an argument, we could start a shell.
If we somehow pass correct argument to the system() function, code isn't executed in the stack, it's executed in the address of system(). This was one of the earliest methods to bypass NX protection.

> ***In this task, you should make an example implementation of this ret2libc method. It could be for example spawning a local shell. This time, **do not** disable NX protection (do not use -z execstack flag in compiler). Disabling other protections is still required. Like previously, make a step by step report(what, why, how) including possible source files and command line commands which lead you to get shell access.***

To be noted: 
* You should check if ASCII Armoring is present in your system. It should be disabled additionally for this task. In some systems, it might not be possible. It is recommended to use Kali Linux in this task.
* This task is much easier to get done with 32 - bit binaries, because of how function parameters are passed in practice, when compared to a 64-bit system. (Stack vs registers?)

One simple implementation can be found from [this][2] paper for example.

Extra: Method was firstly introduced in [here][3].

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

Simple, but practical demonstration of ROP technique can be found [here](https://tc.gts3.org/cs6265/2016/l/lab07-rop/README-tut.txt).

Extra: White paper introducing the ROP can be found [here][5].

> ***Try to get previously mentioned example (ROP_hello) [here](src/pwntools_example/ROP_hello.py) to work by yourself. Next, make simple example implementation of ROP technique. This could be spawning a local shell for example. To not make it same as ret2libc method, print some text before spawning shell, and print also something after exiting the shell. In this way we can apply some ROP - chain.***

Tip: If you are being bit unlucky, and are facing some function addresses containing null bytes in non-Ascii-Armored system, try out some alternative functions. For example putchar function has putchar_unlocked alternative.

---

Task 4 : A bit more advanced ROP implementation
----
You have an option to do pre-defined task below **or** suggest some other task you would do. Something interesting in shellcoding, but we haven't dealt with it yet? Feel free to implement and show us what you got. It does not necessary need to be related for ROP particularly, but in the most cases it probably must. *Your task has to be approved by assistant before you can start doing it.*

## Defeating ASLR (kinda) - pre-defined task

As the name implies, ASLR (Address Space Layout Randomization) randomizes locations in the virtual memory where modules are loaded.

In this task, the executable is compiled with Position Independent Executable (PIE)
disabled; therefore, ASLR is disabled for this executable. But hardcoding e.g., libc function addresses into the exploit is not possible in this task because of ASLR.

Before starting working on this task confirm that ASLR is enabled:

```console
$ cat /proc/sys/kernel/randomize_va_space
2
```

If not, enable ASLR:

```console
$ echo 2 | sudo tee /proc/sys/kernel/randomize_va_space
2
```

Your objective is to:

1. Find the buffer overflow vulnerability
2. Figure out how it could be used to read memory. Hints:
   1. Does the executable import functions that can print strings (or memory) to stdout?
3. Use that to disclose imported libc function addresses. Hints:
   1. Checkout .got.plt.
   2. Remember to enter the main loop again after every read (ret back to loop start)
      * Be careful that you ret to a correct place, otherwise, segfault is likely.
4. Find libc version and base address using that information. Hints:
   * Use libc database, such as https://libc.blukat.me/
5. Compute your desired libc function (or gadget address) using that information
6. Create a ROP chain that opens a local shell using e.g., system or execve

See [task4.c](./src/vuln_progs/task4.c) for the vulnerable program source code.
The 32-bit binary is in [prog_bin/](./prog_bin). The binary was compiled using:

```console
gcc task.c -m32 -no-pie -o task4
```

I recommend that you develop your exploit using pwntool script, similar to the one seen below. This one debugs the program using gdb and sets up breakpoints at locations `main` and `0x8049246`.
In gdb, assembly can be viewed using `layout asm` and the stack can be printed using `x/20xw $esp`. Similarly, `x/20xw $ebp` prints current stack frame. See [GDB documentation](https://www.gnu.org/software/gdb/documentation/).

```python
#!/usr/bin/python3
import pwn
import pwnlib.util.packing as packing
import struct

pwn.context.terminal = ['/usr/bin/x-terminal-emulator', '-e']
pwn.context.log_level = 'debug'

io = pwn.pwnlib.gdb.debug('./program', '''
break main
break *0x8049246
''')

# put your exploit here

io.interactive()
```

> ***Make step by step report. Explain in detail how you developed the exploit.***

[//]: # (Hidden sourcelist for providing all the links.)

[0]: http://www.cs.umd.edu/class/fall2017/cmsc414/readings/stack-smashing.pdf "Aleph One(Elias Levy)  - Smashing The Stack For Fun And Profit"

[1]: https://www.scribd.com/document/60416747/NX-bit "Argento Daniele, Boschi Patrizio & Del Basso Luca - NX bit : A hardware-enforced BOF protection"

[2]: https://shellblade.net/files/docs/ret2libc.pdf "InVoLuNTaRy - Performing a ret2libc Attack : Defeating a non-executable stack"

[3]: http://seclists.org/bugtraq/1997/Aug/63 "Solar Designer (Alexander Peslyak) - Getting around non-executable stack (and fix)"

[4]: https://www.sba-research.org/wp-content/uploads/publications/woot12.pdf "Andrei Homescu,
Michael Stewart,
Per Larsen,
Stefan Brunthaler &
Michael Franz  - 
Microgadgets: Size Does Matter In Turing-complete Return-oriented
Programming"

[5]: https://cseweb.ucsd.edu/~hovav/dist/geometry.pdf "Hovav Shacham - The Geometry of Innocent Flesh on the Bone: Return-into-libc without Function Calls (on the x86)"

