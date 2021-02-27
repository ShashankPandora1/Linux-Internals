#include "main.h"

extern pid_t pid;
extern echo_val echo_stat;

void signal_handler(int signum)                 //signal handler
{
    if ( pid != 0 && pid != echo_stat.msh_pid )
    {
        if ( signum == SIGINT )                 //if sigint received kill the currently running process
            kill(pid, SIGINT);

        if ( signum == SIGTSTP )                //for SIGTSTP stop the current running process
            kill(pid, SIGTSTP);
    }
}
