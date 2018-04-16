#include <stdio.h>
#include <string.h>
#include <stddef.h>

void main ( int argc, char **argv)
{
    int index = 0;

    printf("argc = %d \n", argc);

    for(index = 0; index < argc; index++)
    {
        printf("argv[%d] = %s, Length = %d \n", index+1, *(argv+index), strlen(*(argv+index)));
    }
  
    printf("The length of int is %d bytes.\n", sizeof(int));
    printf("The length of char is %d bytes.\n", sizeof(char));
    printf("The length of char* is %d bytes.\n", sizeof(char *));
    printf("The length of char** is %d bytes.\n", sizeof(char**));
    printf("The length of size_t is %d bytes.\n", sizeof(size_t));
}

