#include "headers.h"

void repeat_com(int x, char *str)
{

    if (strcmp(str, "pwd ") == 0)
    {

        for (int i = 0; i < x; i++)
        {
            Pwdbuild();
        }
        return;
    }
    if (strncmp(str, "echo ", 4) == 0)
    {

        for (int i = 0; i < x; i++)
        {
            for (int j = 5; j < strlen(str); j++)
            {
                printf("%c", str[j]);
            }
            printf("\n");
        }
        return;
    }

    if (strncmp(str, "cd", 2) == 0)
    {

        char *strptr;

        char *subtoken = strinit;
        strinitiation(1024, subtoken);

        subtoken = strtok_r(str, " ", &strptr);
        str = NULL;

        char *temp = strinit;
        strinitiation(1024, temp);
        // if(subtoken==NULL)
        //     return;
        int i = 0;
        int flag = 1;
        while (subtoken != NULL)
        {
            // printf("%s\n", subtoken);
            i++;

            subtoken = strtok_r(str, " ", &strptr);
            if (i == 1 && subtoken == NULL)
            {
                int error = chdir(root_dir);

                if (error != 0)
                {
                    perror(":(");
                }
                flag = 0;
                break;

            } //if it is single cd command
            if (subtoken == NULL)
                break;
            strcat(temp, subtoken);
            strcat(temp, " ");

            // printf("%s\n", temp);
        }
        // if(temp==NULL)
        //     return;

        //after tokeinising we get pure string to pass int the funciotn
        if (flag == 1)
        {
            for (int i = 0; i < x; i++)
            {
                /* code */
                Cdbuild(temp);
            }
        }

        free(temp);

        return;
    }
    if(strncmp(str,"pinfo ",6)==0)
    {
        long int temp = -1;
        char *strptr;
        char *subtoken = strinit;
        strinitiation(1024, subtoken);

        subtoken = strtok_r(str," ", &strptr);
        str = NULL;
        // printf("%s\n", subtoken);
        while (subtoken != NULL)
        {
            subtoken = strtok_r(str," ", &strptr);
            if (subtoken != NULL)
                sscanf(subtoken, "%ld", &temp); //rpcess id as argument last one will be integer
        }

        for (int i = 0; i < x;i++)
          {
              pinfo(temp);
              printf("\n");
          }

        return;
    }
    if (strncmp(str, "ls", 2) == 0)
    {

        int l = 0;  //l file names
        int a = 0;  //hidden
        int al = 0; //long format
        char *strptr;

        char *subtoken = strinit;
        strinitiation(1024, subtoken);

        subtoken = strtok_r(str, " ", &strptr);
        str = NULL;

        char *temp = strinit;
        strinitiation(1024, temp);
        temp[0] = ' ';

        int dir = 0;
        int lol_file = 0;
        // printf("done1\n");
        while (subtoken != NULL)
        {
            {
                if (Dir_stat(subtoken) == 1) // subtoken == '~'
                {
                    dir = 1;
                }
                else if (subtoken[0] == '~')
                {
                    dir = 1;
                    char *temp3 = strinit;
                    strinitiation(1024, temp3);
                    //to open the mentioned file
                    //copting its name
                    int j = 0;
                    for (int i = 1; i < strlen(subtoken); i++)
                    {
                        temp3[j] = subtoken[i];
                        j++;
                    }

                    char *temp = strinit;
                    strinitiation(1024, temp);

                    sprintf(temp, "%s%s", root_dir, temp3);

                    if (Dir_stat(temp) != 1)
                        lol_file = 1;

                    free(temp);
                    free(temp3);
                }
                else if (strcmp(subtoken, "-l") == 0)
                    l = 1;
                else if (strcmp(subtoken, "-a") == 0)
                    a = 1;
                else if (strcmp(subtoken, "-al") == 0)
                    al = 1;
                else if (strcmp(subtoken, "-la") == 0)
                    al = 1;

                else if (strcmp(subtoken, "ls") != 0)
                {
                    if (Dir_stat(subtoken) != 1)
                        lol_file = 1;
                }
            }

            strcat(temp, subtoken);
            strcat(temp, " ");

            subtoken = strtok_r(str, " ", &strptr);
        }

        if (dir == 0)
        {
            strcat(temp, ". ");
        }
        for (int i = 0; i < x; i++)
        {
            if (lol_file == 0)
                ExecuteLs(temp, l, a, al);
            else
                printf("ls: No such file or directory\n");
            // free(subtoken);
        }

        free(temp);
        return;
    }
    else
    {
     
        while (x--)
        {
            char *arg[50];
            int parts = 0; //last val of arg can be set as NULL
            char *commandpi = strinit;
            strinitiation(1024, commandpi); //saved bg process without &
            // printf("yha\n");
            char *tt = strinit;
            strinitiation(1024, tt);
            strcpy(tt, str);

            char *strptr;
            // printf("%s\n", tt);
            char *subtoken = strinit;
            strinitiation(1024, subtoken);

            subtoken = strtok_r(tt," ", &strptr);
            tt = NULL;
           
            while (subtoken != NULL)
            {
                // printf("%s\n", subtoken);
                arg[parts] = subtoken;
                strcat(commandpi, arg[parts]);
                strcat(commandpi, " ");
                parts++;

                subtoken = strtok_r(tt, " ", &strptr);
            }
            // printf("aya\n");
            arg[parts] = NULL;

            //commands executed with execvp

            int forkret = fork();

            if (forkret == -1)
            {
                perror("Error");

                exit(1);
            }

            if (forkret == 0)
            {

                if (execvp(arg[0], arg) == -1)
                {
                    perror("Error in child fg proccess");
                    exit(1);
                }
            }
            // printf("m\n");
            if (forkret != 0)
            {
                // printf("%d\n",x);

                int status;
                // printf("%d\n", x);
                waitpid(forkret, &status, WUNTRACED);

              
            }

            // printf("\n");
        }

        return;
    }
}