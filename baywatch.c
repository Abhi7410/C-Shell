#include "headers.h"


void interrupt(char *time)
{
    FILE *f;
    f = fopen("/proc/interrupts", "r");

    char *buff = strinit;
    strinitiation(1024, buff);

    fgets(buff, 100000, f);

    char *sptr;

    for (int i = 0;;i++)
    {
        char *token = strinit;
        strinitiation(1024, token);

        token = strtok_r(buff, " \t", &sptr);
        buff = NULL;

        if (token == NULL)
            break;

        printf("%s\t", token);
    }

    printf("\n");
    fclose(f);
    char *strptr;

    while (1)
    {
        f = fopen("/proc/interrupts", "r");

        char *buff1 = strinit;
        strinitiation(1024, buff1);
        fgets(buff1, 100000, f);

        char *buff2 = strinit;
        strinitiation(1024, buff2);
        fgets(buff2, 100000, f);

        char *buff3 = strinit;
        strinitiation(1024, buff3);
        fgets(buff3, 100000, f);
        

        char *token = strinit;
        strinitiation(1024, token);

        token = strtok_r(buff3, " \t", &strptr);
        buff3 = NULL;
        bool ostwald = false;
        for (int x = 0;; x++)
        {
            token = strtok_r(buff3, " \t", &strptr);

            if (token == NULL)
                ostwald = true;

            if (token[0] == 'I')
                ostwald = true;

                if(ostwald==true)
                    break;

            printf("%s\t", token);
        }

        printf("\n");
        fclose(f);

        int tt = atoi(time);
        sleep(tt);
    }

    return;
}

void newborn(char *time)
{
    FILE *f;
    char buf[200];

    for (int kk = 0;;kk++)
    {
        f = fopen("/proc/loadavg", "r");
        fgets(buf, sizeof(buf), f);

        char *token = strinit;
        strinitiation(1024, token);

        token = strtok(buf, " \t\n");
     
        int ger = 4;
        while(ger--)
        {
            token = strtok(NULL, " \t\n");
         
            if (token == NULL)
            {    
                return;
            }
        }
        printf("%s\n", token);

        fclose(f);
        int tt = atoi(time);
        sleep(tt);
    }
}
void dirty(char *time)
{
   
    while (1)
    {
        FILE *f;
        f = fopen("/proc/meminfo", "r");
        // fgets(buf, sizeof(buf), f);
        int count = 0;
        char buf[250];
        char *token = strinit;
        strinitiation(1024, token);
        while (fgets(buf, sizeof(buf), f))
        {
            count++;
            
            if (count == 17)
            {
                token = strtok(buf, " \n");
                token = strtok(NULL, " \n");
               
                strcat(token, " ");
                strcat(token, "kB");
                printf("%s\n", token);
                break;
            }
        }

        fclose(f);
        int t = atoi(time);
        sleep(t);
    }
}
void baywatch(char *var)
{
    char *input = strinit;
    strinitiation(1024, input);

    char *time = strinit;
    strinitiation(1024, time);

    char *command = strinit;
    strinitiation(1024, command);

    char *sptr;
    int kkk = 0;
    input = strtok_r(var, " \t", &sptr);
    while (1)
    {
        input = strtok_r(NULL, " \t", &sptr);
        
        if (input == NULL)
            break;

        if (kkk == 0)
            time = input;
        if (kkk == 1)
            command = input;

        if (kkk >= 2)
        {
            YELLOW();
            printf("Invalid arguments\n");
            RESET();
            return;
        }
        kkk++;
    }

 

    if (strcmp(command, "interrupt") != 0 && strcmp(command, "newborn") != 0 && strcmp(command, "dirty") != 0)
    {
        YELLOW();
        printf("Baywatch: Incorrect command\n");
        RESET();
        return;
    }

    li ppid;
    ppid = fork();

    if (ppid == 0)
    {
        int berlin = 0;
        if (strcmp(command, "interrupt") == 0)
        {
            berlin = 1;  
        }
        if (strcmp(command, "newborn") == 0)
        {
            berlin = 2;
        }
        if (strcmp(command, "dirty") == 0)
        {
            berlin = 3;
        }
        if(berlin==1)interrupt(time);
        if (berlin == 2)newborn(time);
        if (berlin == 3)dirty(time);

        exit(0);
    }

    if (ppid > 0)
    {
        // printf("parent id and child id %d %ld\n",getpid(),ppid);
        while (1)
        {
            char ch = getc(stdin);
            if (ch == 'q')
            {

                kill(ppid, SIGKILL);
                waitpid(ppid, NULL, WUNTRACED);
                return;
            }
        }
    }
}