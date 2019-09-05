Computer Security Lab 1: Fuzzing
====

## Preliminary tasks

* Create Github account (although you probably already have one)
* Create your own fork of the CompSec-2019-AnswerTemplate **as instructed [here](../README.md#instructions)**
* Check the instructions on how to download and use the course's Kali Linux virtual machine
    * If you want to use your own computer, download and install VMWare Player to run the virtual machine. Virtualbox should work also.
* Get familiar with the documentation for following tools:
    * [Radamsa](https://gitlab.com/akihe/radamsa)
    * [AFL (American Fuzzy Lop)](http://lcamtuf.coredump.cx/afl/)
    * [AddressSanitizer (ASan)](https://github.com/google/sanitizers/wiki/AddressSanitizer)
    * [Valgrind](http://valgrind.org/docs/manual/quick-start.html)


## About the lab

* This document contains task descriptions and theory for the fuzz testing lab. If there are any differences between the return template and this file, consider this to be the up-to-date document.
* **You can use your own computer if you want.** Check the chapter "Prerequisities" for information on what you need to install. This lab has been made to be completed in a Linux environment and tested to work in the provided Kali Linux virtual machine.
* It is estimated, that you are able to do Tasks 1,2 & 3 during the lab session (4 hours). Upper grade requires that all previous ones have been done as well. You are not expected to be able to finish all the tasks during the lab session, so feel free to continue them at your own time.
* Check the deadline from Moodle and __remember that you have to return your name and GitHub repository information to Moodle before deadline.__


## Background

This week’s theme is fuzzing. Tasks are designed to be done with the provided Kali Linux virtual machine, see the [course mainpage](https://github.com/ouspg/CompSec) for instructions on how to run the virtual machine (VM). The provided Kali VM has all the required tools preinstalled, but if you have your own computer with some other Linux distribution, you are free to use it, just install all the required tools.

In a nutshell, fuzz testing a.k.a. fuzzing is a software testing method that includes feeding malformed and unexpected input data to a program, device or system. The programs that are used to perform fuzz testing are commonly called fuzzers. The main goal of fuzzing is to make the target system behave *unexpectedly*. From the security perspective, the goal is to find and analyze those unexpected behaviors for possible exploits and figure out how to fix them.

In this exercise you will learn basic usage of 2 common fuzzers; Radamsa and American Fuzzy Lop (AFL). You will also use AddressSanitizer, a memory error detection tool, and Valgrind, a debugging tool (and memory error detector as well), which are often used alongside different fuzzers.

## Prerequisites

Basic understanding of C programming language is required.

Make yourself familiar with the tools used to complete the exercises:

* **Radamsa** - https://gitlab.com/akihe/radamsa
* **AFL** (American Fuzzy Lop) - http://lcamtuf.coredump.cx/afl/
* **AddressSanitizer** (ASan) - https://github.com/google/sanitizers/wiki/AddressSanitizer
* **Valgrind** - http://valgrind.org/docs/manual/quick-start.html

## Grading

<details><summary>Details</summary>

Task #|Grade/Level|Description|
-----|:---:|-----------|
Task 1 | | Mutated test case generation with Radamsa
Task 2 | 2 | Analyzing a C-program with AddressSanitizer, fuzztesting with AFL
Task 3 | 3 | Library fuzzing and creating your own small C-program and fuzztesting it
Task 4 | 4/5 | Contribute to an existing open-source project. Set up a fuzzer and report findings.

Grade 1 can be acquired by doing lecture questionnaires from the corresponding lecture.
</details>

---

## Task 1

### Generating mutated test cases with Radamsa

**A)** Make yourself familiar with [Radamsa](https://gitlab.com/akihe/radamsa). Try it out in a terminal and print 10 malformed samples of ```Fuzztest 1337``` using *echo*.

**Provide the command line you used to do this.**

Radamsa can also handle various types of files. Next, you have to generate a bunch of *.txt* test samples for later usage. 

**B)** Create a *.txt* file that contains only the text ```12 EF``` and nothing more. Use Radamsa to generate 100 fuzzed samples of the file that are named ```fuzz1.txt```, ```fuzz2.txt```, ```fuzz3.txt```... etc. You should create a separate folder for the samples.

**Provide the content of 2 different samples that radamsa created**

**Command line used to create the samples**

---

## Task 2 

### A) Analyzing C program with AddressSanitizer

This repository contains an example C program called [example.c](misc/example.c). Your task is to analyze it using [AddressSanitizer (ASan)](https://github.com/google/sanitizers/wiki/AddressSanitizer). Compile the code with ```clang``` and appropriate [sanitizer flags](https://github.com/google/sanitizers/wiki/AddressSanitizerFlags#compiler-flags). Run the compiled program and analyze what happens.

**Command line used to compile the program**

**Screenshot of the result after running the program**

**What is the error and what is causing it in this program?**

---
### B) Fuzzing with AFL

In the following task, you will be using [American Fuzzy Lop (AFL)](http://lcamtuf.coredump.cx/afl/) to fuzz test a program called UnRTF. UnRTF is a tool that can be used to convert *.rtf* files to *HTML*, *LaTeX* etc. 

AFL is already installed in the provided Kali Linux virtual machine and the target program's source code is included in this repository ([unrtf0.21.5.tar.xz](misc/unrtf-0.21.5.tar.xz)). When the source code is available, you should instrument the program by using AFL's own wrappers that work as drop-in replacements for **gcc** and **clang** (NOTE: afl-gcc might not work properly in all systems, but it works with the provided Kali Linux vm). 

So, here's what you need to do:

1. **Extract** the source code package ([unrtf0.21.5.tar.xz](misc/unrtf-0.21.5.tar.xz)) and ```cd``` you way to the extracted directory.

2. **Configure** it to use AFL's wrappers:
    ```shell
    ~$ ./configure CC="<add_here>" --prefix=$HOME/unrtf
    ```
    The ```--prefix=HOME$/unrtf``` flag sets the installation location of the binary file to be your home directory. This is recommended, so you don't have to give it access to the root directory.

3. **Compile and build** the program:
    ```shell
    ~$ make
    ~$ make install
    ```

    __Hint__: See AFL [documentation](http://lcamtuf.coredump.cx/afl/README.txt) to learn about instrumenting programs to use AFL compilers.

4. Use AFL's example *.rtf* file located at ```/usr/share/afl/testcases/others/rtf/small_document.rtf``` to test that your UnRTF works by converting it to HTML:
    ```shell
    ~$ ~/unrtf/bin/unrtf --html /<path>/<to>/<testfile>
    ```

5. Create two folders, one for input files and one for result output. Copy the ```small_document.rtf``` into your input folder.
    ```
    ~$ mkdir <input_folder> <output_folder>
    ~$ cp /<path>/<to>/<testfile> /<path>/<to>/<input_floder>
    ```


6. Start fuzzing UnRTF with AFL using the example ```small_document.rtf``` file as input:
    ```shell
    afl-fuzz -i <input_folder> -o <output_folder> /<path>/<to>/<target_program>
    ```

    __Hint__: See AFL [documentation](http://lcamtuf.coredump.cx/afl/README.txt) on how to start the fuzzer. You are fuzzing the UnRTF binary, which is located at ```~/unrtf/bin/unrtf```.

7. Run the fuzzer until you get at least 50 unique crashes and observe the status window to see what is happening. A good description of the status window can be found [here](http://lcamtuf.coredump.cx/afl/status_screen.txt).

**Command line used to configure unrtf**

**Command line used to run AFL**

**Screenshot of the AFL status screen after stopping the fuzzer**

**What do you think are the most significant pieces of information on the status screen? Why are they important?**

---
### C) Reproducing crashes with Valgrind

You should now have found some crashes with the AFL. Next, you need to reproduce one of them to see, what exactly went wrong. You can find the crashes from the output folder you created previously. Make your way into the ```.../<output_folder>/crashes``` and take one of the *.rtf* files that caused a crash under inspection.

Run UnRTF with this file under Valgrind:

```shell
~$ valgrind --leak-check=yes ~/unrtf/bin/unrtf --html /<path>/<to>/<crashfile>
```

__Hint__: Make sure that you are actually running the UnRTF with a crash file! If you get "Error: Cannot open input file" before Valgrind's actual memory analysis output, you are trying to run the program without any input. See the Valgrind [documentation](http://valgrind.org/docs/manual/quick-start.html) for help.

**Take a screenshot of the Valgrind result after running the program**

**What can you tell about the crash?**

---

## Task 3


### A) Fuzz testing your own program

In this task, you will write a small C program and fuzz test it. In task 1, you created a *.txt* file containing ```12 EF``` and 100 malformed samples of it. We will use them in this task. Your program must take a text file as an input and check the file for the following requirements:
- The file contains **two and only tokens** that are separated with a space
- First token is an **integer**
- Second token is a **string**
- If the content of the text file is as specified above, return 1, otherwise 0

Compile and link your program with AddressSanitizer using appropriate flags.

Run your program with the previously generated 100 test cases. A simple shell script loop, for example, is an easy way to run the test cases. If you don't get enough ASAN outputs with the 100 test cases, try to do the test with 1 000 or 10 000 malformed inputs.

**Provide the C-code of your program**

**Take a screenshot of the AddressSanitizer results after running your program with the test cases. Show at least 3 ASAN outputs.**

---

### B) Fuzzing libraries

[OpenSSL](https://www.openssl.org/) is a widely-used open source cryptographic software library for Transport Layer Security and Secure Socket Layer protocols. In 2014, a buffer over-read vulnerability [CVE-2014-0160](https://nvd.nist.gov/vuln/detail/CVE-2014-0160) was found in the Heartbeat Extension of OpenSSL (up to version 1.0.1f) two years after the feature was introduced. The vulnerability allowed attackers to obtain memory contents from process memory remotely, and as a result, it compromised the integrity of secure communications.

Since this vulnerability is caused by a memory handling related bug, it is possible to find it using fuzzing tools like AddressSanitizer and AFL. In order to fuzz test the OpenSSL library, we have to have a binary file that uses the library as a fuzzing target. For that, we are going to use the provided [target.c](misc/target.c), which uses OpenSSL to simulate a server-client TLS handshake.

Your task is to do the following:
* **Download and extract the source code** for [OpenSSL 1.0.1f](misc/openssl-1.0.1f.tar.xz).
* **Instrument, compile and build OpenSSL and enable the AddressSanitizer**:
    ```shell
    ~$ AFL_USE_ASAN=1 CC=afl-clang-fast CXX=afl-clang-fast++ ./config -d -g
    ~$ make
    ```
* **Instrument and compile the fuzzing target** and enable AddressSanitizer:
    ```shell
    ~$ AFL_USE_ASAN=1 afl-clang-fast target.c -o target openssl/libssl.a openssl/libcrypto.a -I openssl/include -ldl
    ```
* **Create a dummy certificate**. Use OpenSSL to create for example a 512 bit RSA key. The certificate is only used during fuzzing, so it doesn't matter how secure it is:
    ```
    ~$ openssl req -x509 -newkey rsa:512 -keyout server.key -out server.pem -days 365 -nodes -subj /CN=a/
    ```
* After you have tested that the target program works, **start fuzzing the target program** with AFL:
    ```shell
    ~$ afl-fuzz -i in -o out -m none -t 5000 ./target
    ```
    The bug is rather easy to find, so you should be able to find a crash in less than 10 minutes. Use the ```clienthello``` file as seed for AFL. The file is just a standard SSL hello message that the client sends to the server to initialize a secure session. Create an input folder for AFL and place the file there. TLS/SSL handshake takes longer than just reading input from stdin, so raise the memory limit with ```-m none``` and the timeout limit with ```-t 5000``` just in case.
* **Run the target program with the crash file** you got from the AFL:
    ```shell
    ./target < <crash_file>
    ```
* To see more clearly why the crash occurred, convert the crash file into a *.pcap* file using ```od``` and Wireshark's ```text2pcap```:
    ```shell
    ~$ od -A x -t x1z -v <input_file> | text2pcap -T 443,443 - <output_file>
    ```
    This command can also be used to convert ```clienthello``` to *.pcap*.

**What is the more widely recognized name for this CVE-2014-0160 vulnerability?**

**What can you tell about the crash based on ASAN results and the pcap file? What is causing the vulnerability?**

**Take a screenshot of the AFL/ASAN results**

---

## Task 4

### Contribute to an existing open-source project. Set up a fuzzer and report the whole process and possible findings.

Contribute to some existing open-source software (OSS) project by setting up a fuzzing environment and documenting the total process and results. You can choose the target software by yourself and use one of the 2 fuzzers introduced during the lab exercise, or pick some other that you think serves the purpose better. **You should do all the testing inside a virtual machine in case there are potentially malicious files being handled.**

You should read for example [this guide](https://github.com/ouspg/fuzz-testing-beginners-guide) to get started. Please note that in case a real bug is found from the software, it is very important to document the findings in a way that the issue can be easily reproduced. The guide has some good points about what information you should provide. It is not mandatory for the student to file a "real" bug report, but if you find something new, we highly recommend to do so.

You should grab the most recent version of the source code. Few open-source projects as an example:

- [Chromium](https://www.chromium.org/Home) - An open-source browser project started by Google.
- [VLC media player](https://www.videolan.org/vlc/index.html) - A common open-source media player from VideoLAN. Vast attack-surface as the player uses many different libraries to handle audio/video encoding. See [features](https://www.videolan.org/vlc/features.html).
- [ImageMagick](https://www.imagemagick.org/script/index.php) - An open-source suite for displaying, converting and editing images, supporting over 200 file formats.
- See [American Fuzzy Lop](http://lcamtuf.coredump.cx/afl/) main page for a comprehensive list of tools it has found bugs on. Newer versions of software can spawn new bugs, but the most common tools are usually tested the most so they might not be the best to start with.

You should at minimum to provide the following information in the documentation:
- Which fuzzer was used
- A brief explanation of the target software and why you chose it
 - Are you fuzzing the whole software or some specific part of it? 
 - Is software using some libraries? Are those fuzzed as well?
- Operating system and version information. Version numbers of target software, target software libraries, fuzzer and operating system are very important! Can you explain why?
- Compiler and debugger flags
- Initial test case(s) and the one(s) producing a possible crash
 - Necessary steps to reproduce the crash
- It is not necessary to find any bugs. It is enough, if you can prove that you have fuzzed with good code-coverage and they way how input was mutated (=what kind of input fuzzer created overall))
