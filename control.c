#include "headers.h"


void c_signal(int sig)
{
    int pid = getpid();
    int currgpid = getpgid(pid);

    if (shellpgid != currgpid)
    {
        kill(pid, SIGINT);
        display();
    }
}


void z_signal(int sig)
{
    int pid = getpid();
    int currgpid = getpgid(pid);

    if (shellpgid != currgpid)
        kill(pid, SIGTSTP);

    // else
    //     display();
}

void signal_handler(int sig)
{
    int status;
    int childpid = waitpid(-1, &status, WNOHANG); //This flag specifies that waitpid should return immediately instead of waiting

    if (childpid == -1) //wait for any child process
        return;

    if (childpid > 0) // wait for the child process whose process group ID is equal to the calling process
    {

        char *com = searchbyName(childpid); //calling command for status

        int err = delete (childpid); //delete returns

        if (err == -2) //if we find nothing
        {
            return;
        }
        char *buff = strinit;
        strinitiation(1000, buff);

        //WIFEXITED returns true when proccesses are normally terminated.

        if (!WIFEXITED(status)) //This macro queries the child termination status provided by the wait and waitpid functions, and determines whether the child process ended normally.
        {

            sprintf(buff,"\n%swith pid %d exited abnormally.\n", com, childpid);
            write(2, buff, 100);
            display();
            fflush(NULL);
            return;
        }

        //If the value of WIFEXITED(stat_val) value of WEXITSSTATUS is non-zero, this macro evaluates to the low-order 8 bits of
        // the status argument that the child process passed to _exit() or exit(), or the value the child process returned from main().
        int exit_status = WEXITSTATUS(status);
        sprintf(buff,"\n%swith pid %d exited normally.\n", com, childpid);
        write(2, buff, 100);
        display();
        fflush(NULL);

        return;
    }
}
