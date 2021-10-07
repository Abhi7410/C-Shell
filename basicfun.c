#include "headers.h"

//checking directory status
int Dir_stat(char *file)
{
    struct stat st;

    if (stat(file, &st) < 0)
        return -1;

    if (S_ISDIR(st.st_mode))
        return 1;

    if (S_ISREG(st.st_mode))
        return 1;

    else
        return 0;
}
//isDir
int isDir(char *file)
{
    struct stat st;
    if (stat(file, &st) < 0)
    {
        return -1;
    }
    if (S_ISDIR(st.st_mode))
    {

        return 1; //if file is a directory
    }
    else
        return 0;
}
//IsFile
int isFile(char *file)
{
    struct stat st;
    if (stat(file, &st) < 0)
    {
        return -1;
    }
    if (S_ISREG(st.st_mode))
    {
        return 1; //if file is a regular file
    }
    else
        return 0;
}

void strinitiation(int N,char* str)
{
    for (int i = 0; i < N; i++)
    {
        str[i] = '\0';
    }
}

void strmatching(int l, int N, char* var2, char* var)
{
    int j = 0;
    for (int i = l; i < N ; i++)
    {
        var2[j] = var[i];
        j++;
    }
}

void RED()
{
    printf("\033[01;31m");
}
void BLACK()
{
    printf("\033[01;30m");
}
void CYAN()
{
    printf("\033[01;36m");
}
void PURPLE()
{
    printf("\033[01;35m");
}
void WHITE()
{
    printf("\033[01;37m");
}
void YELLOW()
{
    printf("\033[01;33m");
}
void RESET()
{
    printf("\033[0m");
}

//clear
void Clear()
{
    printf("\e[1;1H\e[2J");
}
//shell start

void shellStart()
{

    printf("\n");
    RED();
    for (int i = 0; i < 20; i++)
    {
        if (i % 2 == 1)
            printf(" * ");
        else
            printf(" | ");
    }
    RESET();
    WHITE();
    printf("W  E  L  C  O  M  E");
    RESET();
    RED();
    for (int i = 0; i < 20; i++)
    {
        if (i % 2 == 1)
            printf(" * ");
        else
            printf(" | ");
    }
    RESET();
    printf("\n");
    printf("\n");
    RED();
    for (int i = 0; i < 18; i++)
    {
        if (i % 2 == 1)
            printf(" * ");
        else
            printf(" | ");
    }
    RESET();
    WHITE();
    printf("T  O     M  Y     S  H  E  L  L ");
    RESET();
    RED();
    for (int i = 0; i < 18; i++)
    {
        if (i % 2 == 1)
            printf(" * ");
        else
            printf(" | ");
    }
    RESET();
    printf("\n");
    printf("\n");
}

int months(char *str)
{
    if(strncmp(str,"Jan",3)==0)
        return 1;
    if (strncmp(str, "Feb",3) == 0)
        return 2;
    if (strncmp(str, "Mar",3) == 0)
        return 3;
    if (strncmp(str, "Apr",3) == 0)
        return 4;
    if (strncmp(str, "May",3) == 0)
        return 5;
    if (strncmp(str, "Jun",3) == 0)
        return 6;
    if (strncmp(str, "Jul",3) == 0)
        return 7;
    if (strncmp(str, "Aug",3) == 0)
        return 8;
    if (strncmp(str, "Sep",3) == 0)
        return 9;
    if (strncmp(str, "Oct",3) == 0)
        return 10;
    if (strncmp(str, "Nov",3) == 0)
        return 11;
    if (strncmp(str, "Dec",3) == 0)
        return 12;
   
}

