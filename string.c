/*----------------------------------------------------------------------------------------------------*/
/*IO函数*/
#include <stdio.h>
#include <stdlib.h>

/*string相关函数头文件*/
#include <string.h>

/*含有size_t类型定义，size_t为无符号整数类型,但这里不等于unsigned int*/
#include <stddef.h>

#include <Windows.h>
#include <unistd.h>
#include <fcntl.h>

/*----------------------------------------------------------------------------------------------------*/
#define MAX_STR_NUM     10
#define MAX_STR_SIZE    100

#define ARRAYTEST_SIZE  5

#define MAX_ERROR_NUM   50

#define ASCII_NUM       128

/*----------------------------------------------------------------------------------------------------*/
const char * const jan = "jan";

const char * const separator = "--------------------------------------------------------------------------\n";

const char * const token_sep = ",.";

HANDLE hCom = NULL;

/*定义于堆上，初始值为0*/
char dst[MAX_STR_NUM][MAX_STR_SIZE] = {{'\0',},};

static void comSet(void);

/*----------------------------------------------------------------------------------------------------*/
void main ( int argc, char **argv)
{
    int index = 0;
    char *ptr = NULL;
    char *token = NULL;

    /*定义于栈，为防止使用随机值，定义时至少包含一个初始值*/
    int arraytest[ARRAYTEST_SIZE] = {0,};

    /*输出重定向*/
    FILE *out = NULL;
    /*输入重定向*/
    FILE *in= NULL;
    /*stdout,stdin可都重定向到一个设备如串口，也可只重定向其中一个*/

    DWORD wCount;//读取的字节数
    BOOL bReadStat;

    int comfd;

    comSet();

    comfd = open("COM1", O_RDWR);

    dup2(comfd, fileno(stdin));
    dup2(comfd, fileno(stdout));

#if 0
    /*如果命令行参数第二个是--re则进行重定向到命令行第三个参数制定的文件*/
    if((argc >= 3) && (strcmp(*(argv+1), "--re") == 0))
    {
        /*输出重定向，将结果打印到文本*/
        //out = freopen(*(argv+2), "w", stdout);

        /*输出重定向，将结果打印到串口*/
        out = freopen(*(argv+2), "w", stdout);
        /*输入重定向，从串口读取数据*/
        in = freopen(*(argv+2), "r", stdin);
        /*通过VSPD创建虚拟串口1,2并连接，程序通过COM1发送，在COM2中将显示结果,从COM2发送，程控通过COM1接收结果*/

        /*判断重定向是否成功*/
        //if((out == NULL) || (in == NULL))
        if((in == NULL))
        {
            perror("STDOUT redirectiong Error");

            exit(EXIT_FAILURE);
        }
    }

#endif

    printf("argc = %d \n", argc);
    /*argc的个数包含程序名称，程序名称为第一个*/

    for(index = 0; index < argc; index++)
    {
        printf("argv[%d] = %s \n", index, *(argv+index));
        /*第一个命令行参数为程序名称（有时也含具体路径）*/
    }

    printf(separator);
    /*-----------------------------------------------------------------------------------------------*/
    ptr = malloc(MAX_STR_SIZE * sizeof (char));
    if(ptr == NULL)
    {
        perror("Malloc Error");

        exit(EXIT_FAILURE);

    }

#if 0
    for( ; ; )
    {
        bReadStat=ReadFile(hCom,ptr,100,&wCount,NULL);

        if(bReadStat)
        {
            ptr[wCount]='\0';
            printf("%s\n",ptr);
        }
    }
#endif

    for( ; ; )
    {
        scanf("%s", ptr);

        printf("The input string is %s \n", ptr);
    }

    free(ptr);

#if 0



    /*array 初始值测试*/
    for(index = 0; index < ARRAYTEST_SIZE; index++)
    {
        printf("The arraytest initial value is arraytest[%d] = %d\n", index, arraytest[index]);
    }

    printf(separator);
    /*-----------------------------------------------------------------------------------------------*/
    /*sizeof 与类型长度*/
    printf("The length of int is %d bytes.\n", sizeof(int));
    printf("The length of char is %d bytes.\n", sizeof(char));
    printf("The length of char* is %d bytes.\n", sizeof(char *));
    printf("The length of char** is %d bytes.\n", sizeof(char**));
    printf("The length of size_t is %d bytes.\n", sizeof(size_t));
    printf("The length of unsigned int is %d bytes.\n", sizeof(unsigned int));

    /*数组名称与代表长度*/
    printf("The size of dst is %d, and the size of dst[0] is %d, and the size of dst[0][0] is %d,\n", sizeof(dst), sizeof(dst[0]), sizeof(dst[0][0]));
    /*dst为数组总大小，dst[0]为后一维大小,dst[0]][0]为后后一维大小*/
    /*也即：写法中，除写出的部分外，剩下的维的长度,最小维为数组类型的长度*/

    printf(separator);
    /*-----------------------------------------------------------------------------------------------*/
    /*数组名与地址*/
    printf("The addr of dst is %d, and the addr of dst+1 is %d\n",(dst),(dst+1));
    printf("The addr of dst[0] is %d, and the addr of dst[0]+1 is %d\n",(dst[0]),(dst[0]+1));
    printf("The addr of dst[0][0] is %d, and the addr of dst[0][0]+1 is %d\n",(dst[0][0]),(dst[0][0]+1));
    /*数组名变化表示最高维变化*/
    /*也即：写法中，写出部分的变化，相当于剩下部分最高维的变化，最小维为具体数值*/
    /*表示地址时：dst相当于dst+0,相当于dst[0],同样,dst[0]+1相当于dst[0][1]*/
    /*程序中dst[index]相当于dst+index,也等于index[dst]*/

    printf(separator);
    /*-----------------------------------------------------------------------------------------------*/
    for(index = 0; index < argc; index++)
    {
        if(index >= MAX_STR_NUM)
        {
            printf("The input strings num is more than the strorage num.\n");

            break;
        }

        if((strlen(*(argv+index)) + strlen(jan)) >= MAX_STR_SIZE)
        {
            printf("The string in dst[%d] is longer than the storage area.\n", index+1);
        }
        else
        {
            printf("argv[%d] = %s, Length = %d \n", index, *(argv+index), strlen(*(argv+index)));
            /*第一个命令行参数为程序名称（有时也含具体路径）,长度不包含字符串结尾的NUL,就是直观看到的个数*/
        
            printf("dst[%d] befor strcpy is %s\n", index, dst[index]);

            strcpy(dst[index], *(argv+index));

            printf("dst[%d] after strcpy is %s\n", index, dst[index]);

            if(strcmp(*(argv+index), jan) > 0)
            {
                printf("argv[%d] = %s is bigger than jan\n", index, *(argv+index));
            }
            else if (strcmp(*(argv+index), jan) < 0)
            {
                printf("argv[%d] = %s is less than jan\n", index, *(argv+index));
            }
            else
            {
                printf("argv[%d] = %s is equel to jan\n", index, *(argv+index));
            }
            
            strcat(dst[index], jan);

            printf("dst[%d] after strcat is %s\n", index, dst[index]);

            /*打印 jan 后面的字符*/
            ptr = strstr(dst[index], jan);          /*确认jan在该字符串中*/
            if(ptr != NULL)
            {
                ptr += strlen(jan);                    /*将查找到的位置调整到jan的后面*/
                printf("The string after jan using strstr is %s \n", ptr);

            }

            /*打印 jan 后面的字符，注意与strstr的区别*/
            ptr = dst[index] + strspn(dst[index], jan);
            printf("The string after jan using strspn is %s \n", ptr);

            /*strstr中 jan 作为一个整体查找；strspn中jan作为3个字符查找*/

            for(token = strtok(dst[index], token_sep); token != NULL; token = strtok(NULL, token_sep))
            {
                printf("Token in dst[%d] is %s\n", index, token);

            }

            printf("\n");
        }
    }

    /*打印操作系统返回的错误信息，用循环模拟*/
    for(index = 0; index < MAX_ERROR_NUM; index++)
    {
        ptr = strerror(index);
        printf("No:%d Error info is %s\n", index, ptr);
    }

    /*打印ASCII字符表*/
    for(index = 0; index < ASCII_NUM; index++)
    {
        printf("ASCII NO:0x%X is %c\n", index, index);
        /*相同的数值，用不同的格式打印，结果不同，即：printf函数按照格式做了转换*/
        /*在串口调试工具中，不可打印字符会出错*/

    }

#endif 
}

static void comSet(void)
{
    COMMTIMEOUTS TimeOuts;
    DCB dcb;
    
    hCom=CreateFile(TEXT("COM1"), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if(hCom == (HANDLE)(-1))
    {
        perror("COM Error\n");

        exit(EXIT_FAILURE);
    }
    else
    {
        printf("COM OK\n");
    }


    SetupComm(hCom,1024,1024); //输入缓冲区和输出缓冲区的大小都是1024

    //设定读超时
    TimeOuts.ReadIntervalTimeout=1000;
    TimeOuts.ReadTotalTimeoutMultiplier=500;
    TimeOuts.ReadTotalTimeoutConstant=5000;

    //设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier=500;
    TimeOuts.WriteTotalTimeoutConstant=2000;

    SetCommTimeouts(hCom,&TimeOuts); //设置超时


    GetCommState(hCom,&dcb);

    dcb.BaudRate=9600; //波特率为9600
    dcb.ByteSize=8; //每个字节有8位
    dcb.Parity=NOPARITY; //无奇偶校验位
    dcb.StopBits=ONE5STOPBITS; //两个停止位

    SetCommState(hCom,&dcb);


    PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR); //清空缓冲区

    CloseHandle(hCom);
}

/*
 * 1.调试信息使用标准输入输出。结果等信息使用fprintf输出到指定的文件流，使用sprintf进行格式转换。
 *
 */
