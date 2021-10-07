#include "headers.h"

void pip_build(char *str)
{

    char *sptr;
    char *token = strinit;
    strinitiation(1024, token);
    //for multi pipe strs
    token = strtok_r(str, "|", &sptr);
    str = NULL;

    int cnt = 0;
    char *char_array[200];
    char_array[cnt] = token;


    int stdout_save = dup(STDOUT_FILENO);
    int stdin_save = dup(STDIN_FILENO);

    for (int j = 0;; j++)
    {
        token = strtok_r(str, "|", &sptr);
        if (token == NULL)
            break;
        else
        {
            ++cnt;
            char_array[cnt] = token;
        }
    }
    //STDOUT_FILENO is an integer file descriptor (actually, the integer 1). it may use for write syscall
  
    int fd[2];

    for (int k = 0; k < cnt + 1; k++)
    {
        // make a pipe (fds go in fd[0] and fd[1])
        if (pipe(fd) < 0)
        {
            YELLOW();
            printf("Piping Error\n");
            RESET();
        }

        int pid = fork();
        if (pid < 0)
        {
            YELLOW();
            printf("Fork error: No child process\n");
            RESET();
        }
        //child process
        if (pid == 0 && k == cnt)
        {
            close(fd[0]);
            dup2(stdout_save, 1);

            command(char_array[k]);
            close(fd[1]);

            exit(0);
        }
        else if(pid ==0 && k < cnt)
        {
            close(fd[0]);
            dup2(fd[1], 1);
            command(char_array[k]);
            close(fd[1]);

            exit(0);
        }
        //parent process
        else if (pid > 0)
        {
            close(fd[1]);
            wait(NULL);

            dup2(fd[0], 0);
            close(fd[0]);
        }
    }

    if (dup2(stdout_save, 1) < 0)
    {
        YELLOW();
        printf("Dup2 Error stdout");
        RESET();
    }
    if (dup2(stdin_save, 0) < 0)
    {
        YELLOW();
        printf("Dup2 Error stdin");
        RESET();
    }

    return;
}