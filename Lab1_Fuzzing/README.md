# **Computer security lab 1: Fuzzing**
This week’s theme is fuzzing. Tasks can be done with Kali Linux, see the [course mainpage](https://github.com/ouspg/CompSec) for instructions how to run the virtual machine (VM). Kali VM provided has all the required tools installed already. If you have your own computer with Ubuntu for example, you can use it too, just install all the required tools.
 
In a nutshell, fuzzing is a software testing method that feeds malformed and unexpected input data to a program, device or system. The programs that are used to perform fuzz testing are commonly called fuzzers. The one and only goal of fuzzing is to crash the target system. From the security perspective, the goal is to analyze those found flaws for possible exploits.

In this exercise you will learn basic usage of 2 common fuzzers; Radamsa and American Fuzzy Lop (AFL). You will also use AddressSanitizer, a memory error detection tool, and Valgrind, a debugging tool, which are often used alongside different fuzzers.

## Some prerequisities & tools
Basic understanding of C/C++ programming language is required.

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


## **Task 1**: Mutated test case generation with Radamsa

**A)** Try out Radamsa using command line tool. Print 10 malformed samples of "Fuzztest 1337" using _echo_.

**Provide the command line you used to do this.**
```
```

 **B)** What you just did can be done to various types of files too. Next, generate a bunch of .txt test samples for later usage. Create a .txt file, that contains text: "12 EF" and nothing more. Use radamsa to generate 100 fuzzed samples of the file and to name them fuzz1, fuzz2, fuzz3,...etc.

 __Hint__: Create a new, separate folder for the samples.

**Provide the content of 2 different samples that radamsa created**
```
```

**Command line used to create the samples**
```
```

## **Task 2**: Analyzing a C-program with AddressSanitizer, fuzztesting with AFL
**A)** Your task is to analyze an example c-program *example.c*. Compile the code with appropriate sanitizer flags to enable AddressSanitizer. Run the compiled program and analyze what happens.

**Command line used to compile the program**
```
```
**Screenshot of the result after running the program**
```
```
**What is the error and what is causing it in this program**
```
```


**B)** In the following task you will be using American Fuzzy Lop (AFL), it is installed in the Kali Linux virtual machine. If you are using your own computer you can download it as follows:
```
~$ wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
```
You can find the target program sourcecode following this link: [unrtf0.21.5.tar.gz](https://ftp.gnu.org/gnu/unrtf/unrtf-0.21.5.tar.gz). This tool can be used to convert .rtf files into other, more readable formats (see README for more). Extract the package, **_configure_ it with appropriate AFL compiler flags and then _compile_**.

__Hint__: configure, make, make install. See AFL [quick start guide](http://lcamtuf.coredump.cx/afl/README.txt) for help

During this task, use the example .rtf file from AFL folder (**/usr/share/afl/testcases/others/rtf/small-document.rtf**). You can try that your unrtf is working properly using command line:
```
~$ /path/to/unrtf --html /path/to/testfile
```
Start fuzzing unrtf with AFL using the example .rtf file as input. You need to create 2 folders, one for input files and one for results output. Input folder must include the small-document.rtf file mentioned above. See AFL [quick start guide](http://lcamtuf.coredump.cx/afl/README.txt) for instructions on how to start the fuzzer. 

Run the fuzzer, see what happens in the status window. Good description of the status window can be found [here](http://lcamtuf.coredump.cx/afl/status_screen.txt).

__Hint__: You are fuzzing a binary. To copy your input file into in/ folder for AFL to use, you can do for example:
```
~$ cp /path/to/testfile /path/to/whereyouwanttocopyit
```
**Command lines used to configure and compile unrtf**
```
```
**Command line used to run AFL**
```
```
**Screenshot of the AFL status screen after stopping the fuzzer**
```
```
**What do you think are the most trivial pieces of information in the status screen?**
```
```
Did you find any crashes (you should)? Awesome! Next you need to reproduce one crash to see what went wrong. You can find the crashes where you specified the output folder when starting AFL fuzzer. Browse into the .../out/crashes folder, and take one .rtf file that caused crash under inspection. Runt unrtf with this file as you did with the example file earlier, but this time under Valgrind. Take a look at the Valgrind [documentation](http://valgrind.org/docs/manual/quick-start.html) for help.

**Take a screenshot of the Valgrind result after running a testcase succesfully**
```
```
**What can you tell about the crash?**
```
```

## **Task 3**: Creating your own small C-program and fuzztesting it

In this task you will write a small C program of your own and fuzztest it. In task 1 you created a .txt file containing "12 EF" and fuzzed samples of it, in this task we will use them. Your program must take a text file as an input and check the file for following requirements:
- First token is an **integer**
- Second token is a **string**
- Only two tokens are present
- If the content of the text file is as specified above, return code 0, otherwise 1

Compile and link your program with AddressSanitizer using appropriate flags.

Run your program with the previously generated 100 test cases. A simple shell script loop for example is an easy way to run the test cases.

**Provide the C-code of your program**
```
```
**Take a screenshot of the AddressSanitizer results after running your program with the testcases. Show at least 3 ASan outputs.**
```
```

## **Task 4**: Contribute to a existing open-source project. Set up a fuzzer and report findings.

Contribute to an existing open-source software (OSS) project by setting up a fuzzing environment and documenting the process and results. You can choose the target software by yourself and use one of the 2 fuzzers introduced during the lab exercise, or pick some other that you think serves the purpose better. 

You should read for example [this guide](https://github.com/ouspg/fuzz-testing-beginners-guide) to get started. Please note that in case a real bug is found in the software, it is very important to document the results in a way that the issue can be easily reproduced. The guide has some good pointes of what information you should provide.

To be continued.. Work in progress.
