#include "main.h"

int status;
pid_t pid;
echo_val echo_stat;

/* jobs */
int jobs[20];
pid_t j_pid[20];
char j_cmd[20][20];
int i_jobs = 0;

void execute_external_command(char *input_str)
{
    char **args, *command;
    int cmd_loc[100] = {0};
    int cmd_count = 1, i = 0;

    command = (char *)malloc((strlen(input_str) + 1) * sizeof(char));
    strcpy(command, input_str);                 //creating and coying to a new string

    strtok(command, " ");

    args = (char **)malloc(100 * sizeof(char *));       //allocate memory for 2D array
    
    for ( int i = 0; i < 100; i++ )
        args[i] = (char *)malloc(30 * sizeof(char));

    while ( command != NULL )                           //creating 2d array for commands for n-pipe
    {
        if ( !strcmp(command, "|") )
        {
            args[i] = NULL;
            cmd_loc[cmd_count++] = i + 1;
        }

        else
            strcpy(args[i], command);

        i++;
        command = strtok(NULL, " ");
    }

    args[i] = NULL;

    int stdin_cpy = dup(0), stdout_cpy = dup(1);        //creating duplicate of stdin and stdout

    n_pipe(args, cmd_count, cmd_loc);                   //calling n pipe function to execute the commands

    dup2(stdin_cpy, 0);                                 //revert 0 and 1 to original fd
    dup2(stdout_cpy, 1);

    close(stdin_cpy);
    close(stdout_cpy);                                  //close duplicates

    for ( int i = 0; i < 100; i++ )
        free(args[i]);
    
    free(command);                                      //free the memory
    free(args);
}

int n_pipe(char *args[], int cmd_count, int *cmd_loc)
{
    int fd[2];

    for ( int i = 0; i < cmd_count; i++ )
    {
        pipe(fd);                                       //creating pipe
        pid = fork();                                   //create child process

        if ( !pid )                                     //child process
        {
            setpgrp();

            if ( i != cmd_count - 1 )                   //if not last command create clone of write of pipe as stdout
                dup2(fd[1], 1);

            close(fd[0]);                               //close the fds
            close(fd[1]);
            
            execvp(args[cmd_loc[i]], &args[cmd_loc[i]]);
            fprintf(stderr, "Error: %s command not found\n", args[cmd_loc[i]]);

            exit(1);
        }

        else if ( pid > 0 )                             //parent process
        {
            if ( waitpid(pid, &status, WUNTRACED) != -1 )       //keep track of the runnning process
            {
                if ( WIFEXITED(status) )                        //get and store the exit status of last terminated process
                    echo_stat.exit_stat = WEXITSTATUS(status);

                else if ( WIFSIGNALED(status) )                 //if signalled go to this block
                    echo_stat.exit_stat = WTERMSIG(status) + 128;

                if ( WIFSTOPPED(status) )                       //if stopped with ctrl+z print the message
                {
                    echo_stat.exit_stat = WSTOPSIG(status) + 128;
                    
                    printf("[%d]+ Stopped\t\t", ++i_jobs);

                    sprintf(j_cmd[i_jobs], "%s %s", args[cmd_loc[i]], args[cmd_loc[i] + 1]);
                    printf("%s", j_cmd[i_jobs]);

                    j_pid[i_jobs] = pid;                        //store the pid in an array

                    printf("\tpid: %d\n", pid);
                }
            }
            pid = 0;
            dup2(fd[0], 0);                             //set the read end of pipe as stdin

            close(fd[0]);
            close(fd[1]);
        }
    }
    return 0;
}
