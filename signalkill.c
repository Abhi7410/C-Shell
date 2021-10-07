#include "headers.h"

void kill_sig(int jobnum, int sig)
{
   
    int pid = searchbyJob(jobnum);

    if (pid == -1)
    {
        write(2, "\033[01;33mNo job with given job number exists.\033[0m\n",49);

        return;
    }

    if (kill(pid, sig) < 0)
    {
        write(2, "\033[01;33mError in sending signal.\033[0m\n", 40);
    }

    return;
}