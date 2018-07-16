# Buffer overflow problems

There is a quite descriptive phrase on [CWE](http://cwe.mitre.org/top25/#CWE-120) website about the problem: "Buffer overflows are Mother Nature's little reminder of that law of physics that says: if you try to put more stuff into a container than it can hold, you're going to make a mess."

In practise *software* buffer overflow means that the space reserved for data is insufficient for the data being stored.

Conversely, buffer over-read means that read processing might read more than it should.

Some high-level programming languages (C/C++/Objective-C) are enabling direct memory management and are not checking input against storage to prevent buffer overflows, and therefore making it possible to cause buffer overflow, when *input data* is improperly validated or sanitized. (In most cases: user input)

When we are talking about user input, we might think about text at first, but this input could be anything: for example images, pdf -, audio - or video files.

The are two basic categories for overflows:

* stack overflows - data in the stack is overflowed

* heap overflows - data in the dynamically allocated memory is overflowed

Heap overflows are rare and challenging to exploit. We are getting better examples from stack overflows and therefore focusing on them.

## Stack overflows

We mentioned data and the space reserved for it. Insufficient space could cause overflow, but where and how more precisely?

Vast majority of current modern computer computation uses stack to storage local data. Stack is pile of data, what is contolled with FILO (first in, last out) method.
In most of the current operating systems, each application has its own stack.
Stack is a region in computer memory, starting from higher address, growing to lower address.

When application is executed, stack and registers are used for handling the execution flow of the program. Stack is divided into frames, where each of them contains running function of the program, containing data of local variables, called function parameters, function return addresses etc. For example, nesting three function calls in program could open three stack frames.

More precise information is provided [here.](http://www.tenouk.com/Bufferoverflowc/Bufferoverflow2a.html)

The place or reason, why stack overflow happens, is usually local variable. The size for variable is defined too small in the code.

Let's have a look on stack. Each line describes data section in correct order inside stack:

*higher memory address* :arrow_up:

|Data type|Address|Data|Comment|
-|-|-|-
|Function 1 parameter I|0xAB08 | 0x4141| Parameter 1(AA in ascii) passed to function
|Function 1 parameter II|0xAB06 | 0x4242| Parameter 2(BB in ascii) passed to function
|Function 1 return address|0xAB04 | 0xff6E| Place where function returns after completion
|Function 1 Saved EBP address|0xAB02 | 0xAB09| Stack pointer of previous frame
|Function 1 Local variables|0xAB02 | 0x0000| Reserved space for local variables, used in function
|Function 2 parameter I|0xAB00 | 0x0000| 
|Function 2 parameter II|0xAAFE | 0x0000| 
|Function 2 etc...|... | ...| ...
|Buffer|... | ...| Available stack space

*lower memory address* :arrow_down:

|
|---|---|---




0xAB08 | 0x0000| 
0xAB0A | 0x0000| Buffer end
0xAB0C | 0x1234| <- other data






Sources:

* [Apple Secure Coding Guide: Avoiding Buffer Overflows and Underflows](https://developer.apple.com/library/content/documentation/Security/Conceptual/SecureCodingGuide/Articles/BufferOverflows.html)

* [ BUFFER OVERFLOW 6
The Function Stack](http://www.tenouk.com/Bufferoverflowc/Bufferoverflow2a.html)
* [7. Memory : Stack vs Heap](https://www.gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html)
* [x86 Assembly Guide](http://www.cs.virginia.edu/~evans/cs216/guides/x86.html)




**A 12 byte buffer is shown on the above. How many X can be stored in to the buffer without overflow:**
* Char
* Int
* Float

## Buffer overflow example 1: tampering with data

### How to get access to data?

```c
#include <stdio.h> 
#include <string.h>

int main(void) { 

char buffer[15];
int testValue = 0; 

printf("\n Enter security code to print secret >"); 
gets(buffer);
if(strcmp(buffer, "CSE-Oulu")) { 
printf ("\n Wrong Password \n");
} 
else { 
testValue = 1; 
} 
if(testValue){ 
/* Do something*/
printf ("My secret: I love Assembly language"); 
} 
return 0; 
}
```

## Buffer overflow – solution 1

* Yes, yes, of course, you could just examine the program file, because we have not taken any steps to protect the security code or the secret:
```shell
$ gcc -o overflow overflow.c
$ hexdump –C overflow

00000730  0a 45 6e 74 65 72 20 73  65 63 75 72 69 74 79 20   |.Enter security |
00000740  63 6f 64 65 20 74 6f 20  70 72 69 6e 74 20 73 65   |code to print se|
00000750  63 72 65 74 3e 00 25 73  00 43 53 45 2d 4f 75 6c   |cret>.%s.CSE-Oul|
00000760  75 00 0a 57 72 6f 6e 67  20 63 6f 64 65 21 00 00   |u..Wrong code!..|
00000770  0a 4d 79 20 73 65 63 72  65 74 3a 20 49 20 6c 6f   |.My secret: I lo|
00000780  76 65 20 41 73 73 65 6d  62 6c 79 20 6c 61 6e 67   |ve Assembly lang|
00000790  75 61 67 65 00 00 00 00  01 1b 03 3b 34 00 00 00   |uage.......;4...|
```

## Buffer overflow – solution 2
* The program works:

```shell
$ ./overflow
Enter security code to print secret>ohno
Wrong code!
$ ./overflow
Enter security code to print secret>CSE-Oulu
My secret: I love Assembly language
```
* Or does it?

```shell
$ ./overflow
Enter security code to print secret>aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wrong code!
My secret: I love Assembly language
$ ./overflow
Enter security code to print secret>aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wrong code!
My secret: I love Assembly language
Segmentation fault (core dumped)
```

* What if the overflow could reach an area of memory, where the execution will branch to later?
* Then, the malevolent input could be crafted to include machine language instructions, that the unwitting buggy program would then execute.
* Or what if the program allows to read more data than intended?

How easy is it to change execution flow of this program?
```c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void stackoverflow(char* string) {
    char buffer[20];
    strcpy(buffer, string);
    printf("%s\n", buffer);
}

int main(int argc, char** argv) {
    printf("Starting very vulnerable program...\n");
    printf("Printing arguments of the program: \n");
    stackoverflow(argv[1]);
    return 0;
}
```
