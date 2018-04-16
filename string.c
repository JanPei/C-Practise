#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_STR_NUM     10
#define MAX_STR_SIZE    100


const char * const jan = "JanPei";

char dst[MAX_STR_NUM][MAX_STR_SIZE] = {{'\0',},};

void main ( int argc, char **argv)
{
    int index = 0;

    printf("argc = %d \n", argc);

    for(index = 0; index < argc; index++)
    {
        printf("argv[%d] = %s, Length = %d \n", index+1, *(argv+index), strlen(*(argv+index)));
    }

    printf("The size of dst is %d, and the size of dst[0] is %d\n", sizeof(dst), sizeof(dst[0]));

    for(index = 0; index < argc; index++)
    {
        if(index >= MAX_STR_NUM)
        {
            printf("The input strings is more than the strorage num.\n");

            break;
        }

        if(strlen(*(argv+index)) > MAX_STR_SIZE-1)
        {
            printf("dst[%d] the input string is longer than the storage area.\n", index+1);
        }
        else
        {
            printf("dst[%d] befor strcpy is %s\n", index+1, dst[index]);

            strcpy(dst[index], *(argv+index));

            printf("dst[%d] after strcpy is %s\n", index+1, dst[index]);
            
            strcat(dst[index], jan);

            printf("dst[%d] after strcat is %s\n", index+1, dst[index]);
        }
    }
  
    printf("The length of int is %d bytes.\n", sizeof(int));
    printf("The length of char is %d bytes.\n", sizeof(char));
    printf("The length of char* is %d bytes.\n", sizeof(char *));
    printf("The length of char** is %d bytes.\n", sizeof(char**));
    printf("The length of size_t is %d bytes.\n", sizeof(size_t));
}

