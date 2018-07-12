## Buffer overflow problems


* **CWE-119: Improper Restriction of Operations within the Bounds of a Memory**
    * http://cwe.mitre.org/data/definitions/119.html
*  Software buffer overflow means, that the space reserved for data is insufficient for the data being stored
* Conversely, buffer over-read means that read processing might read more than it should.

* More about buffer overflows: https://developer.apple.com/library/content/documentation/Security/Conceptual/SecureCodingGuide/Articles/BufferOverflows.html
and http://www.tenouk.com/Bufferoverflowc/Bufferoverflow2a.html

|Address|Data|Comment|
|---|---|---
0xAB00 | 0x0000| Buffer start
0xAB02 | 0x0000| 
0xAB04 | 0x0000| 
0xAB06 | 0x0000| 
0xAB08 | 0x0000| 
0xAB0A | 0x0000| Buffer end
0xAB0C | 0x1234| <- other data

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
[ttokola@cse-cn0001 ~/compsectesti]$ gcc -o overflow overflow.c
[ttokola@cse-cn0001 ~/compsectesti]$ hexdump –C overflow

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
[ttokola@cse-cn0001 ~/compsectesti]$ ./overflow
Enter security code to print secret>ohno
Wrong code!
[ttokola@cse-cn0001 ~/compsectesti]$ ./overflow
Enter security code to print secret>CSE-Oulu
My secret: I love Assembly language
```
* Or does it?

```shell
[ttokola@cse-cn0001 ~/compsectesti]$ ./overflow
Enter security code to print secret>aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wrong code!
My secret: I love Assembly language
[ttokola@cse-cn0001 ~/compsectesti]$ ./overflow
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
