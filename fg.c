#include "headers.h"

void fg(int jobnum)
{
    int jpid = searchbyJob(jobnum);
    int pgid = getpgid(jpid); //pgid is process if of calling process and jpid is pid of child process

    if (jpid == -1)
    {
        YELLOW();
        printf("Bg process with given job number doesn't exist.\n");
        RESET();
        return;
    }

    //The tty command of terminal basically prints the file name of the
    // terminal connected to standard input. tty is short of teletype,
    //but popularly known as a terminal it allows you to interact with the
    // system by passing on the data (you input) to the system, and displaying
    //  the output produced by the system (dev/pts/1)
    signal(SIGTTIN, SIG_IGN); //tty input for background process
    signal(SIGTTOU, SIG_IGN); //tty output for background process

    //SIG_DFL 	default signal handling
    // SIG_IGN   signal is ignored

    if (tcsetpgrp(STDIN_FILENO, pgid) == -1)
    {
        perror("TCSETPGRP ERROR"); //The function tcsetpgrp() makes the process group with process group ID pgrp the foreground process group
        // on the terminal associated to fd, which must be the controlling terminal of the calling process, and still be associated with its session.
        exit(1);
    }
    kill(jpid, SIGCONT); //CONTINUE IF STOPPED

    int status;

    //change to group for control z
    waitpid(jpid, &status, WUNTRACED);
    //The waitpid() system call suspends execution of the current process until a child specified by pid argument has changed state
    //WUNTRACED   return if a child has stopped(but not traced via ptrace(2)). Status for traced children which have stopped is provided even if this option is not specified.
    if (status != 0)
    {
        printf(":(\n");
    }
    if (tcsetpgrp(STDIN_FILENO, shellpgid) == -1)
    {
        perror("TCSETPGRP ERROR");

        exit(1);
    }

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    char *com = searchbyName(jpid);

    delete (jpid); //linked list deletion

    if (WIFSTOPPED(status) == 1)
    {
        insert(jpid, com); //linkedlist insertion
    }

    return;
}