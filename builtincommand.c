#include "headers.h"

void command(char *str)
{
    char *abc = strinit;
    strinitiation(1024, abc);
    char *cde = strinit;
    strinitiation(1024, cde);

    char *sptr;
    char *strptr;

    strcpy(abc, str);
    //clear no included along with tokenise commands
    if (strcmp(abc, "clear") == 0)
    {
        Clear();
        return;
    }

    //parsing the command by ';' for semicolon based multiple commands

    for (int start = 1;; start++)
    {
        char *token = strinit;
        strinitiation(1024, token);

        token = strtok_r(abc, ";", &sptr);
        abc = NULL;

        if (token == NULL)
            break;

        char token2[1024] = "";
        strcpy(token2, token);

        cde = token;
        int back = 0;

        for (int i = 0;; i++)
        {
            char *subtoken = strinit;
            strinitiation(1024, subtoken);

            subtoken = strtok_r(cde, " \t", &strptr);
            cde = NULL;

            if (subtoken == NULL)
                break;
            //current working directory name on terminal using getcwd
            //PIPING
            int ipl= 0;
            for (int i = 0; i < 1024; i++)
            {
                /* code */
                if(token2[i]=='|')
                {
                    pip_build(token2);
                    ipl = 1;
                    break;
                }
            }

            if(ipl == 1)
                break;



            if (strcmp(subtoken, "pwd") == 0)
            {
                Pwdbuild();
                break;
            }
            //redirection
           
            int redirection = 0;
            for (int i = 0; i < 1024; i++)
            {
                if ((token2[i] == '<') || token2[i]=='>')
                {
                    redirect(token2);
                    redirection = 1;
                    break;
                }
            }
            if (redirection == 1)
                break;
//cd
            if (strcmp(subtoken, "cd") == 0)
            {
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

                    subtoken = strtok_r(cde, " \t", &strptr);
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
                    Cdbuild(temp);

                free(temp);
                break;
            }

            if (strcmp(subtoken, "echo") == 0)
            {
                char *temp = strinit;
                strinitiation(1024, temp);

                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (subtoken == NULL)
                        break;
                    {
                        strcat(temp, subtoken);
                        strcat(temp, " ");
                    }
                }
                //will print the data
                Echobuild(temp);
                free(temp);
                printf("\n");
                break;
            }
            if (strcmp(subtoken, "repeat") == 0)
            {
                char *temp = strinit;
                strinitiation(1024, temp);
                int c = 0;
                int l;
                while (subtoken != NULL)
                {
                    c++;
                    subtoken = strtok_r(cde, " \t", &strptr);
                    // if (c == 1 && subtoken == NULL)
                    // {
                    //     printf("InComplete Arguments\n");
                    //     return;
                    // }
                    if (subtoken == NULL)
                        break;
                    if (c == 1)
                    {
                        l = atoi(subtoken);
                    }
                    if(c>1)
                    {
                        strcat(temp, subtoken);
                        strcat(temp, " ");
                    }
                }
                //will print the data
                // printf("%d\n", l);
                repeat_com(l, temp);
                free(temp);
               
                break;
            }
            if (strcmp(subtoken, "history") == 0)
            {
                char *temp = strinit;
                strinitiation(1024, temp);

                int num = 0;
                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (subtoken == NULL)
                        break;
                    {
                        num = atoi(subtoken);
                    }
                }

                history(num);
                break;
            }

            if (strcmp(subtoken, "ls") == 0)
            {
                int l = 0;  //l file names
                int a = 0;  //hidden
                int al = 0; //long format

                char *temp = strinit;
                strinitiation(1024, temp);
                temp[0] = ' ';

                int dir = 0;
                int lol_file = 0;

                while (subtoken != NULL)
                {
                    {
                        if (Dir_stat(subtoken) == 1)
                        {
                            dir = 1;
                        }
                        else if (subtoken[0] == '~')
                        {
                            dir = 1;
                            char *temp3 = strinit;
                            strinitiation(1024, temp3);
                           
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

                    subtoken = strtok_r(cde, " \t", &strptr);
                }

                if (dir == 0)
                {
                    strcat(temp, ". ");
                }

                if (lol_file == 0)
                    ExecuteLs(temp, l, a, al);
                else{
                    YELLOW();
                    printf("ls: No such file or directory\n");
                    RESET();
                }
                free(temp);
                // free(subtoken);
                break;
            }

            if (strcmp(subtoken, "pinfo") == 0)
            {
                long int temp = -1;
                int count = 0;
                while (subtoken != NULL)
                {
                    count++;
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (subtoken != NULL)
                        sscanf(subtoken, "%ld", &temp);//rpcess id as argument
                  
                  
                }
                if(count>2)
                 {
                     YELLOW();
                     printf("Invalid number of arguments\n");
                     RESET();
                     break;
                 }
                pinfo(temp);
                break;
            }

            if (strcmp(subtoken, "jobs") == 0)
            {
                int flag = 0;
                int c = 0;
                subtoken = strtok_r(cde, " \t", &strptr);
                while (subtoken != NULL)
                {
                    // subtoken = strtok_r(cde, " \t", &strptr);
                    // printf("%s\n", subtoken);
                    if (c == 0)
                    {
                        if (strcmp(subtoken, "-r") == 0)
                            flag = 1;
                        if (strcmp(subtoken, "-s") == 0)
                            flag = 2;

                        break;
                    } 
                }
                // printf("aya\n");
                Jobs(flag);
                break;
            }
//signalkill
            if (strcmp(subtoken, "sig") == 0)
            {
                int jn;
                int sig;
                int c = 0;
                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (c == 0)
                        jn = atoi(subtoken);
                    if (c == 1)
                        sig = atoi(subtoken);
                    if (c == 3)
                    {
                        write(2, "Incorrect number of arguments.\n", 32);
                        return;
                    }
                    c++;
                }
                kill_sig(jn, sig);
                break;
            }
            if (strcmp(subtoken, "bg") == 0)
            {
                int jbbbi;
                int c = 0;
                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (c == 0)
                        jbbbi = atoi(subtoken);
                    if (c == 2)
                    {
                        YELLOW();
                        printf("Inavalid number of arguments\n");
                        RESET();
                        return;
                    }
                    c++;
                }

                bg(jbbbi);
                break;
            }
            //fg
            if (strcmp(subtoken, "fg") == 0)
            {
                int jbbbi;
                int c = 0;
                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (c == 0)
                        jbbbi = atoi(subtoken);
                    if (c == 2)
                    {
                        YELLOW();
                        printf("Inavalid number of arguments\n");
                        RESET();
                        return;
                    }
                    c++;
                }

                fg(jbbbi);
                break;
            }
            //baywatch
            if (strcmp(subtoken, "baywatch") == 0)
            {
                char *var = strinit;
                strinitiation(1024, var);

                while (subtoken != NULL)
                {
                    subtoken = strtok_r(cde, " \t", &strptr);
                    if (subtoken == NULL)
                        break;
                    strcat(var, subtoken);
                    strcat(var, " ");
                }

                baywatch(var);
                free(var);
                break;
            }
            //exit
            if (strcmp(subtoken, "q") == 0 || strcmp(subtoken,"exit")==0)
            {
                PURPLE();
                printf("BYE BYE\n");
                RESET();
                exit(0);
            }

            //commands executed with execvp
            char *arg[50];
            int parts = 0; //last val of arg can be set as NULL
            char *commandpi = strinit;
            strinitiation(1024, commandpi); //saved bg process without &
            // printf("yha\n");
            //recognizing bg or fg and saving values in arg array
            while (subtoken != NULL)
            {
                if (strcmp(subtoken, "&") == 0)
                    back = 1;

                else
                {
                    arg[parts] = subtoken;
                    strcat(commandpi, arg[parts]);
                    strcat(commandpi, " ");
                    parts++;
                }
                subtoken = strtok_r(cde, " \t", &strptr);
            }
            // printf("aya\n");
            arg[parts] = NULL;
            //for execv we need lalst pointer to be NULL

            int forkret = fork();

            if (forkret == -1)
            {
                perror("FORK-ERROR");

                exit(1);
            }

            if (forkret == 0) 
            {
                if (back == 0)
                {
                    if (execvp(arg[0], arg) == -1)
                    {
                        YELLOW();
                        printf("No such child process\n");
                        RESET();
                        exit(1);
                    }
                }

                else if (back == 1)
                {
                    setpgid(0, 0);
                    if (execvp(arg[0], arg) == -1)
                    {
                        YELLOW();
                        printf("No such child background process\n");
                        RESET();
                        exit(1);
                    }
                }
            }
            // printf("m\n");
            if (forkret > 0)
            {
                // printf("parent process id is %d\n",getpid());
                int status;
                if (back == 0)
                {
                    waitpid(forkret, &status, WUNTRACED);
                   //WUNTRACED also return if a child has stopped (but not traced via ptrace(2)). Status for traced children which have stopped is provided even if this option is not specified.

                    if (status != 0)
                    {
                        printf("\n");
                        return;
                    }

                    if (WIFSTOPPED(status) == 1)
                    {
                        insert(forkret, commandpi);
                    }
                }
                else if (back == 1)
                {
                    printf("[%d] %d\n", gjnum + 1, forkret);
                    insert(forkret, commandpi); //process is pushed in backgrund
                }
            }

            break;
        }
    }

    return;
}