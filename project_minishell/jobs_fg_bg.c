#include "main.h"

extern int i_jobs;
extern echo_val echo_stat;
extern int status;
extern char j_cmd[20][20];
extern int j_pid[20];
extern pid_t pid;

void job_list()                                     //function definition for jobs command
{
    if ( !i_jobs )
    {
        printf("Error: No pending jobs\n");
        return;
    }

    /* Print the pending jobs */
    for ( int i = 1; i <= i_jobs; i++ )
        printf("[%d]+ Stopped\t\t%s\tpid: %d\n", i, j_cmd[i], j_pid[i]);
}

void foreground()                                   //to execute stopped programs
{
    if ( waitpid(pid, &status, WUNTRACED) != -1 )   //keep the track if the process is stopped   
    {
        if ( WIFEXITED(status) )                    //if child exited
            echo_stat.exit_stat = WEXITSTATUS(status);      //set the exit status

        else if ( WIFSIGNALED(status) )             //if stopped by a signal set the exit status as per signal namae 
            echo_stat.exit_stat = WTERMSIG(status) + 128;

        if ( WIFSTOPPED(status) )                   //if program stopped by cy ctrl + z
        {
            echo_stat.exit_stat = WSTOPSIG(status) + 128;       //set the exit status

            printf("[%d]+ Stopped\t\t", ++i_jobs);              //print the stopped message

            printf("%s", j_cmd[i_jobs]);                        //print command name that stopped

            j_pid[i_jobs] = pid;

            printf("\tpid: %d\n", pid);                         //print pid of stopped program
        }
    }
    pid = 0;
}