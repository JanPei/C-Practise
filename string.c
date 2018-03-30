#include <stdio.h>
#include <string.h>

void main ( int argc, char **argv)
{
    int index = 0;

    printf("argc = %d \n", argc);

    for(index = 0; index < argc; index++)
    {
        printf("argv[%d] = %s\n", index, *(argv+index));
        
    }

}

