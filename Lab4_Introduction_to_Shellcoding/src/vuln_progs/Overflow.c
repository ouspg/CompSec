//2# Sourcecode from Buffer overflows

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