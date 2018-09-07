Computer Security Lab 1: Fuzzing
====

This week’s theme is fuzzing. Tasks can be done with Kali Linux, see the [course mainpage](https://github.com/ouspg/CompSec) for instructions how to run the virtual machine (VM). Kali VM provided has all the required tools installed already. If you have your own computer with Ubuntu for example, you can use it too, just install all the required tools.
 
In a nutshell, fuzzing is a software testing method that feeds malformed and unexpected input data to a program, device or system. The programs that are used to perform fuzz testing are commonly called fuzzers. The main goal of fuzzing is to make the target system behave *unexpectedly*. From the security perspective, the goal is to analyze those found flaws for possible exploits (estimate the size of risk) and finally figure out a way to fix it.

In this exercise you will learn basic usage of 2 common fuzzers; Radamsa and American Fuzzy Lop (AFL). You will also use AddressSanitizer, a memory error detection tool, and Valgrind, a debugging tool (and memory error detector as well), which are often used alongside different fuzzers.

## Some prerequisities & tools
Basic understanding of C programming language is required.

Make yourself familiar with the tools used to complete the exercises:

### **Radamsa** - https://gitlab.com/akihe/radamsa

### **AFL** (American Fuzzy Lop) - http://lcamtuf.coredump.cx/afl/

### **AddressSanitizer** (ASan) - https://github.com/google/sanitizers/wiki/AddressSanitizer

### **Valgrind** - http://valgrind.org/docs/manual/quick-start.html

It is estimated, that you are able to do Tasks 1,2 & 3 during the lab session (4 hours). Upper grade requires that all previous ones have been done as well.

Task #|Grade/Level|Description|
-----|:---:|-----------|
Task 1 |   | Mutated test case generation with Radamsa
Task 2 | 2 | Analyzing a C-program with AddressSanitizer, fuzztesting with AFL
Task 3 | 3 | Creating your own small C-program and fuzztesting it
Task 4 | 4/5 | Contribute to a existing open-source project. Set up a fuzzer and report findings.
---

Grade 1 can be aquired by doing lecture questionnaires from the corresponding lectures.

## **Task 1**: Mutated test case generation with Radamsa

**A)** Try out Radamsa using command line tool. Print 10 malformed samples of "Fuzztest 1337" using _echo_.

**Provide the command line you used to do this.**


 **B)** What you just did can be done to various types of files too. Next, generate a bunch of .txt test samples for later usage. Create a .txt file, that contains text: "12 EF" and nothing more. Use radamsa to generate 100 fuzzed samples of the file and to name them fuzz1, fuzz2, fuzz3,...etc.

 __Hint__: Create a new, separate folder for the samples.

**Provide the content of 2 different samples that radamsa created**


**Command line used to create the samples**

---
## **Task 2**: Analyzing a C-program with AddressSanitizer, fuzztesting with AFL
**A)** Your task is to analyze an example c-program *example.c*. Compile the code with appropriate sanitizer flags to enable AddressSanitizer. Run the compiled program and analyze what happens.

**Command line used to compile the program**

**Screenshot of the result after running the program**

**What is the error and what is causing it in this program?**

---

**B)** In the following task you will be using American Fuzzy Lop (AFL), it is installed in the Kali Linux virtual machine. 

You can find the target program sourcecode following this link: [unrtf0.21.5.tar.gz](https://ftp.gnu.org/gnu/unrtf/unrtf-0.21.5.tar.gz). This tool can be used to convert .rtf files into other, more readable formats (see README for more). Extract the package, **_configure_** it to use AFL's wrappers and then **_compile_**. 

When source code is available, you should instrument the program for use with AFL by using AFL's own compilers that work as drop-in replacements for **gcc/g++** (NOTE: afl-gcc might not work properly in all systems, better use clang) and **clang/clang++**. You can do as following, leave the quotations and modify *add_here* fields:
```
~$ ./configure CC="add_here" CXX="add_here" --prefix=$HOME/unrtf
~$ make
~$ make install
```
__Hint__: See AFL [documentation](http://lcamtuf.coredump.cx/afl/README.txt) how to instrument programs to use AFL compilers.

 This way, with --prefix flag, you are installing the binary into your home directory, instead of giving it root access to do whatever the installer likes, which is not recommended to every binary you can find.


During this task, use the example .rtf file from AFL folder (**/usr/share/afl/testcases/others/rtf/small_document.rtf**). You can try that your unrtf is working properly using command line:
```
~$ ~/unrtf/bin/unrtf --html /path/to/testfile
```
Start fuzzing unrtf with AFL using the example .rtf file as input. You need to create 2 folders, one for input files and one for results output. Input folder must include the small-document.rtf file mentioned above. See AFL [documentation](http://lcamtuf.coredump.cx/afl/README.txt) for instructions on how to start the fuzzer. 

Run the fuzzer, see what happens in the status window. Good description of the status window can be found [here](http://lcamtuf.coredump.cx/afl/status_screen.txt).

__Hint__: You are fuzzing a binary. To copy your input file into in/ folder for AFL to use, you can do for example:
```
~$ cp /path/to/testfile /path/to/whereyouwanttocopyit
```
**Command line used to configure unrtf**

**Command line used to run AFL**

**Screenshot of the AFL status screen after stopping the fuzzer**

**What do you think are the most significant pieces of information in the status screen? Why are they?**

---
Did you find any crashes (you should)? Awesome! Next you need to reproduce one crash to see what went wrong. You can find the crashes where you specified the output folder when starting AFL fuzzer. Browse into the .../out/crashes folder, and take one .rtf file that caused crash under inspection. Runt unrtf with this file as you did with the example file earlier, but this time under Valgrind. Take a look at the Valgrind [documentation](http://valgrind.org/docs/manual/quick-start.html) for help.

**Take a screenshot of the Valgrind result after running the program**

**What can you tell about the crash?**

---
## **Task 3**: Creating your own small C-program and fuzztesting it

In this task you will write a small C program of your own and fuzztest it. In task 1 you created a .txt file containing "12 EF" and fuzzed samples of it, in this task we will use them. Your program must take a text file as an input and check the file for following requirements:
- First token is an **integer**
- Second token is a **string**
- Only two tokens are present
- If the content of the text file is as specified above, return code 0, otherwise 1

Compile and link your program with AddressSanitizer using appropriate flags.

Run your program with the previously generated 100 test cases. A simple shell script loop for example is an easy way to run the test cases.

**Provide the C-code of your program**

**Take a screenshot of the AddressSanitizer results after running your program with the testcases. Show at least 3 ASan outputs.**

---
## **Task 4**: Contribute to a existing open-source project. Set up a fuzzer and report whole process and possible findings.

Contribute to an existing open-source software (OSS) project by setting up a fuzzing environment and documenting the total process and results. You can choose the target software by yourself and use one of the 2 fuzzers introduced during the lab exercise, or pick some other that you think serves the purpose better. **You should do all the testing inside a virtual machine in case there are potentially malicious files being handled.**

You should read for example [this guide](https://github.com/ouspg/fuzz-testing-beginners-guide) to get started. Please note that in case a real bug is found from the software, it is very important to document the findings in a way that the issue can be easily reproduced. The guide has some good points of what information you should provide. It is not mandatory for the student to file a "real" bug report, but if you find something new, we highly recommend to do so.

You should grab the most recent vesion of the source code. Few open-source projects as an example:

- [Chromium](https://www.chromium.org/Home) - An open-source browser project started by Google.
- [VLC media player](https://www.videolan.org/vlc/index.html) - A common open-source media player from VideoLAN. Vast attack-surface as the player uses many different libraries to hande audio/video encoding. See [features](https://www.videolan.org/vlc/features.html).
- [ImageMagick](https://www.imagemagick.org/script/index.php) - An open-source suite for displaying, converting and editing image, supporting over 200 file formats.
- See [American Fuzzy Lop](http://lcamtuf.coredump.cx/afl/) main page for a comprehensive list of tools it has found bugs on. Newer versions of software can spawn new bugs, but the most common tools are usually tested the most so they might not be the best to start with.

You should at minimum to provide the following information in the documentation:
- Which fuzzer was used
- Brief explanation of the target software and why you chose it
  - Are you fuzzing the whole software or some specific part of it? 
  - Is software using some libraries? Are those fuzzed as well?
- Operating system and version information. Version numbers of target software, target software libraries, fuzzer and operating system are very important! Can you explain why?
- Compiler and debugger flags
- Initial testcase(s) and the one(s) producing a possible crash
  - Necessary steps to reproduce the crash
- It is not necessary to find any bugs. It is enough, if you can prove that you have fuzzed with good code-coverage and they way how input was mutated (=what kind of input fuzzer created overall))

