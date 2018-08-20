#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
   char * buffer = malloc(1024);
   sprintf(buffer, "%d", argc);
   printf("%s",buffer);
}
