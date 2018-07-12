//1# Example from Buffer Overflows
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