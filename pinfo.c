#include "headers.h"
#define ll long int

void pinfo(long int p)
{
    ll pid;
    pid = ((p == -1)) ? getpid() : p ;
  //if no pid given in commandline then process id of calling process is taken as argument

    char* filename = strinit;
    strinitiation(1024,filename);
    sprintf(filename, "/proc/%ld/stat", pid);

    
    //1--pid
    //2--filename executable
    //3--one character from the string "RSDZTW" where R is running, 
    //S is sleeping in an interruptible wait, D is waiting in uninterruptible disk sleep, Z is zombie, 
    //T is traced or stopped (on a signal), and W is paging.
    //4-- parent pid  ppid


    //for more use "man proc"
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
    //if file is empty saddd
        perror(":(");
        return;
    }

    char *viarr = strinit;
    strinitiation(1024, viarr);

    fgets(viarr, 10000, f);

    char *sptr;
    char *strptr;
    char *state;
    char *virtual;

    char *var = strinit;
    strinitiation(1024, var);

    for (int ID = 0;; ID++)
    {
        char *token = strinit;
        strinitiation(1024, token);

        token = strtok_r(viarr, " \t", &sptr);
        viarr = NULL;

        if (token == NULL)
            break;

        strcat(var, token);
        strcat(var," ");
    }
    char *gpay;
    //those 52 valuees in which we need some selective ones only
    for (int ID = 0;; ID++)
    {
        char *subtoken = strinit;
        strinitiation(1024,subtoken);

        //using space delinmeter
        subtoken = strtok_r(var, " ", &sptr);
        var = NULL;

        if (subtoken == NULL)
            break;

        if(ID==2)
            state = subtoken;
        if(ID == 22)
            virtual = subtoken;
        if(ID == 1)
            gpay = subtoken;
    }

    // printf("%s\n", var);
    char *pineapple = strinit;
    strinitiation(1024, pineapple);
    sprintf(pineapple, "/proc/%ld/exe", pid);

    char *path = strinit;
    strinitiation(1024, path);

    readlink(pineapple,path, 1024);

    fclose(f);
    if(p== -1)
    {
        if(strcmp(state,"R")==0 || strcmp(state,"S"))
            strcat(state, "+");
    }
    printf("pid -- %ld\n", pid);
    printf("Process Status -- %s\n", state);
    printf("memory -- %s\n", virtual);
    printf("Executable Path -- %s\n", path);

    free(path);
    free(pineapple);
    free(filename);
    free(viarr);
}