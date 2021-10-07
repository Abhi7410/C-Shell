#include "headers.h"

void redirect(char *line)
{
    char *line2 = strinit;
    strcpy(line2, line);
    char *comm = strinit;
    int lll = strlen(line2);
    // for (int i = 0; i < lll; i++)
    int ccc = 0;
    while (ccc < lll)
    {
        if ((line2[ccc] == '<') || (line2[ccc] == '>'))
            break;

        comm[ccc] = line2[ccc];
        ccc++;
    }

    //parsing by space
    char *subtoken = strinit;
  
    char *sptr;
    char *token = strinit;
   

    subtoken = strtok_r(line2, " \t", &sptr);
    line2 = NULL;

    while (subtoken != NULL)
    {
        strcat(token, subtoken);
        subtoken = strtok_r(line2, " \t", &sptr);
    }

    bool ampersand = false;
    int len = strlen(token);
    if (token[len - 1] == '&')
    {
        ampersand = true;
    }

    char *re_input = strinit;

    char *re_output = strinit;

    char *re_apoutput = strinit;
    

    bool flag = false;

    int ipfd = dup(STDIN_FILENO);  //input fd
    int opfd = dup(STDOUT_FILENO); //outpud fd

    int i = 0;

    while (i <= len-1)
    {
        if (token[i] == '<')
        {
            //error correction if < <
            if (i + 1 < len)
            {
                if (token[i + 1] == '<' || token[i + 1] == '>' || i == (len-1))
                {

                    YELLOW();
                    printf("Syntax error near unexpected token. ");
                    RED();
                    printf("LOL\n");
                    RESET();
                    flag = true;
                    break;
                }
            }

            i++;
            int j = 0;
            //taking the text after < 
            strinitiation(1024, re_input);

            while (token[i] != '<' && token[i] != '>' && i < len)
            {
                re_input[j] = token[i];
                j++;
                i++;
            }

            char *file = strinit;
            // strinitiation(1024, file);    //1
            sprintf(file, "%s", re_input);
            close(ipfd); //oldfd closing
            ipfd = dup(open(file, O_RDWR, 0777));

            if (ipfd == -1)
            {
                YELLOW();
                printf("ERROR IN INPUT FILE.\n ");
                RESET();
                flag = true;
                break;
            }
            continue;
        }

        else if (token[i] == '>')
        {
            //append case
            if (token[i + 1] == '>')
            {
                i++;
                //error correction if < <
                if (i + 1 < len)
                {
                    if (token[i + 1] == '<' || token[i + 1] == '>' || i == len-1)
                    {

                        YELLOW();
                        printf("Syntax error near unexpected token. ");
                        RED();
                        printf("LOL\n");
                        RESET();
                        flag = true;
                        break;
                    }
                }
                i++;
                int j = 0;
                strinitiation(1024, re_apoutput);

                while (token[i] != '<' && token[i] != '>' && i < len)
                {
                    re_apoutput[j] = token[i];
                    j++;
                    i++;
                }

                char *file = strinit;
                strinitiation(1024, file);
                sprintf(file, "%s", re_apoutput);

                close(opfd); //closing old_fd
                opfd = dup(open(file, O_RDWR | O_CREAT | O_APPEND, 0644));
                if (opfd == -1)
                {
                    YELLOW();
                    printf("ERROR IN OUTPUT FILE.\n"); 
                    RESET();
                    flag = true;
                    break;
                }

                continue;
            }

            //overwrite case
            else
            {
                //error correction if ><
                if (i < len-1)
                {
                    if (token[i + 1] == '<' || i == len-1)
                    {

                        YELLOW();
                        printf("Syntax error near unexpected token. ");
                        RED();
                        printf("LOL\n");
                        RESET();
                        flag = true;
                        break;
                    }
                }

                i++;
                int j = 0;
                strinitiation(1024, re_output);
                
                while (token[i] != '<' && token[i] != '>' && i < len)
                {
                    re_output[j] = token[i];
                    j++;
                    i++;
                }

                char *file = strinit;
                strinitiation(1024, file);
                sprintf(file, "%s", re_output);

                // printf("> file is %s ",file);
                close(opfd);
                opfd = dup(open(file, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644));
                if (opfd < 0)
                {
                  
                    char temp[200] = " ";
                    sprintf(temp, "Program %s", file);
                    printf("%s\n", temp);
                    flag = true;
                    break;
                }

                // printf("opfd is %d\n",opfd);

                continue;
            }
        }

        else
            i++;
    }

    if (flag)
        return;

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    int pid = fork();

    // printf("pid is %d\n",pid);

    if (pid < 0)
    {
     
        perror("Fork Error");
        return;
    }

    if (pid == 0) //child process
    {

        if (dup2(opfd, STDOUT_FILENO) < 0)
        {
           
            perror("Unable to dupcliate file descriptor\n");
            exit(1);
        }
        close(opfd);

        if (dup2(ipfd, STDIN_FILENO) < 0)
        {
           
            perror("Unable to duplicate file descriptor\n");
            exit(1);
        }

        close(ipfd); //what if ipfd was originally 0? !!!!!!!!!!!!!

        if (ampersand)
            strcat(comm, " &");

        command(comm);

        exit(0);
    }

    if (pid > 0) //parent process
    {
        wait(NULL);
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(ipfd);
        close(opfd);
    }
}