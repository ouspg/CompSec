# **Computer security lab 2: Fuzzing**
This week’s theme is fuzzing. The tasks should be done using Ubuntu, a virtual machine image can be found in the course folder in the university drive.
 


## Some prerequisities & tools
Basic understanding of C/C++ programming language is required.

Make yourself familiar with the tools used to complete the exercises:

### **Radamsa** - https://gitlab.com/akihe/radamsa

### **AFL** (American Fuzzy Lop) - http://lcamtuf.coredump.cx/afl/

### **AddressSanitizer** - https://github.com/google/sanitizers/wiki/AddressSanitizer

### **Valgrind** - http://valgrind.org/docs/manual/quick-start.html

If you use the Ubuntu VMWare image to complete the exercise, you should start by installing VMWare Tools to make your life easier using the VM.

## Task 1:
#### Step 1.
Let's try out Radamsa using command line tool. Print 10 malformed samples of "Fuzztest 1337" using _echo_. 
>***Provide the command line you used to do this.***
```
paste here
```

#### Step 2.
 What you just did can be done to various types of files too. Let's generate a folder full of .txt test samples for later usage. Create a .txt file, that contains text: "12 EF". Use radamsa to generate 100 fuzzed samples of the file. Create a new separate folder for the samples.
>***Provide 2 different samples that radamsa created***
```
paste here
```
>***Command line used to create the samples***
```
paste here
```
## Task 2:
Your task is to analyze an example c-program *example.c*. Compile the code with appropriate sanitizer flags to enable AddressSanitizer. Run the compiled program and analyze what happens.

>***Command line used to compile the program***
```
paste here
```
>***Screenshot of the result after running the program***

See Return_Instructions readme how to add image

>***What is the error and what is causing it in this program***
```
answer here
```
## Task 3:
#### Step 1. 
Download and install AFL
```
~$ wget http://lcamtuf.coredump.cx/afl/releases/afl-latest.tgz
```
You can find the target program sourcecode in the VM home folder: unrtf0.21.5.orig.tar.gz. This tool can be used to convert .rtf files into other formats (see README for more). Extract the package, **_configure_ it with appropriate AFL compiler flags and then _compile_**.

During this task, use the example .rtf file from AFL folder **.../afl-X.XX/testcases/others/rtf/small-document.rtf**. You can try that your unrtf is working properly:
```
~$ /path/to/unrtf --html /path/to/testfile
```
Start fuzzing unrtf with AFL using the example .rtf file. See AFL readme for instructions on how to start the fuzzer. Run the fuzzer, see what happens in the status window. Good description of the status window can be found [here](http://lcamtuf.coredump.cx/afl/status_screen.txt).

If you get an error regarding core dump notifications, try:
```
~$ sudo su
~$ echo core>/proc/sys/kernel/core_pattern
~$ exit
```
>***Command line used to configure unrtf***
```
paste here
```
>***Command line used to run AFL***
```
paste here
```
>***Screenshot of the AFL status screen after stopping the fuzzer***

See Return_Instructions readme how to add image

>***What do you think are the most interesting pieces of information in the status screen?***
```
answer here
```
### Step 2.
Did you find any crashes (you should)? Awesome! Let's reproduce one to see what went wrong. You can find the crashes where you specified the output folder when starting AFL fuzzer. Browse into the .../out/crashes folder, and take one .rtf file that caused crash under inspection. Runt unrtf with this file as you did with the example file earlier, but this time under Valgrind. Take a look at the Valgrind documentation how to do it, if you didn't already.

>***Take a screenshot of the Valgrind result after running a testcase succesfully***

See Return_Instructions readme how to add image

>***What can you tell about the crash?***
```
answer here
```

## Task 4:
In this task you will write a small C program of your own and fuzztest it. In task 1 you created a .txt file containing "12 EF" and fuzzed samples of it, in this task we will use them. Your program must take a text file as an input and check the file for following requirements:
- First token is an **integer**
- Second token is a **string**
- Only two tokens are present
- If the content of the text file is as specified above, return code 0, otherwise 1

Compile and link your program with AddressSanitizer using appropriate flags.

Run your program with the previously generated 100 test cases. A simple shell script loop for example is an easy way to run the test cases.

>***Provide the C-code of your program***
```c
paste your code here
```

>***Take a screenshot of the AddressSanitizer results after running your program with the testcases. Show at least 3 ASan outputs.***

See Return_Instructions readme how to add image
## Task 5: WIP?
