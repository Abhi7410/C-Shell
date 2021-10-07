#include "headers.h"
#define li long int



char root_dir[] = "";
int gjnum; //keep track of all background jobs
int shellpid;
int shellpgid;
char *cdprev;
char *cdprevpath;
char *cdreqprev;
char *cdreqprevpath;
struct Node *head = NULL;
struct Node *start = NULL;


int main()
{
    int status = 1; //1 means no error, 0 means error

    system("clear");

    getcwd(root_dir, 1024);

    cdprev = strinit;
    strinitiation(1024, cdprev);
    cdprevpath = strinit;
    strinitiation(1024, cdprev);
    cdreqprev = strinit;
    strinitiation(1024, cdprev);
    cdreqprevpath = strinit;
    strinitiation(1024, cdprev);


    strcat(cdreqprev, "\0");
    strcat(cdreqprevpath, root_dir);
    strcat(cdprev, "\0");
    strcat(cdprevpath, root_dir);

    // read, parse, execute loop
    shellStart();

    shellpid = getpid();
    shellpgid = getpgid(shellpid); //calling parrent

    signal(SIGCHLD, signal_handler); //for child process background process abruption
    signal(SIGTSTP, z_signal);//for forground job to stop with contropl+z
    signal(SIGINT, c_signal); //
  
    gjnum = 0;
    // printf("%s", root_dir);
    // history_read();
    inithist();
    do
    {
      
        display(); //displaying the username and hostname with prompt

        //reading input
        char *rline = strinit;
        strinitiation(1024, rline);
        li len = 0;
        li char_read = getline(&rline, &len, stdin);
        int length = (int)strlen(rline);
        rline[length - 1] = '\0';

        if (char_read == -1)
        {
            // printf("CTRL + D captured\n"); //ctrl + D
            exit(0);
        }
        // update_history(rline);
        add_history(rline);
        execute_history();
        command(rline);

        // printf("exited command\n");

    } while (status);

    return 0;
}