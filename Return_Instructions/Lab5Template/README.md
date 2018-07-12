# Answer template for Lab 5: Shellcoding

Make a step-by-step report from what you did. (What, why and how?)
You can use screenshots, code snippets and anything, what Markdown enables you to use. Answer at least for the questions presented in each section.
They should be same than in actual instructions.

You can add source files to [src](src) folder and screenshots to [img](img) folder.

**Answer to this document, and push changes to Git!**

## Task 1 : Basics of buffer overflows

### A) Creating a program with improper input validation and analyzing overflow

* What is the role of the rip register and ret instruction?

* Add source file of your vulnerable program to [src](src) folder.

* What is causing the buffer overflow?

* Provide a screenshot and command of situation, where you managed to reach instruction pointer register.

### B) Adding hidden (non-used) function to previous program. (And still executing it)

* You can add function to the source file you previously created here, or just show it as code snippet.

* Describe to location of newly added function memory address.

* How did you execute function by just overflowing the input?


## Task 2 : Arbitary code execution

### A) Making a simple program to open Shell.

* Add source file of your program to [src](src) folder.

## B) Transforming functionality to machine instructions

* Add source file of your assembly program to [src](src) folder.
* Describe each line of assembly code. You can make this by adding comments to source.
* Does x86 instruction set has advantages over x64 in some cases?
* Describe how did you turn your assembly code to shellcode, and the results of it. Provide screenshot of situation, where you tested the execution of it.

### C) Making the final payload and executing it

How did I find the required information to open shell by overflowing input?

Make a step-by-step report (what, why and how), including command line commands you used to success of executing arbitary code on vulnerable program,by finally opening local shell outside of GDB.
Include a screenshot of the final situation, when you were able to open shell.

## Task 3 : Defeating No-eXecute

### A) Return-to-libc (aka ret2libc)

> ***In this task, you should make example implementation of this ret2libc method. It could be for example spawning local shell. This time, **do not** disable NX protection (do not use -z execstack flag in compiler). Disabling other protections is still required. Like previously, make step by step report(what, why, how) including source files and command line commands which lead you to get shell access.***


### B) Return-oriented programming (aka ROP)

> ***Try to get previously mentioned example (ROP_hello) to work by yourself. Next, make simple example implementation of ROP technique.***

> ***Example: This could be spawning a local shell. To not make it same as ret2libc method, print some text before spawning shell, and print also something after exiting the shell. In this way we can apply some ROP - chain.***

## Task 4 : A bit more advanced ROP implementation

> Implement **one** of the described tasks, and make step-by-step report (what,why and how) for what you did.