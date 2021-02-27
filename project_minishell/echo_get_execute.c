#include "main.h"

extern echo_val echo_stat;

void set_echo_vals(char *argv[])                    //func definition to set the echo command values
{
    echo_stat.msh_pid = getpid();                   //get the pid of minishell and store
    
    getcwd(echo_stat.msh_path, 80);                 //set the shell path
    strcat(echo_stat.msh_path, (argv[0] + 1));
}

void echo_execute(char *arg2)                   //fucntion call to execute echo command as per the arg2 value
{
    if ( !strcmp(arg2, "$?") )
        printf("%d\n", echo_stat.exit_stat);    //for $? print exit status of last running program

    else if ( !strcmp(arg2, "$$") )
        printf("%d\n", echo_stat.msh_pid);      //print the minishell pid

    else if ( !strcmp(arg2, "$SHELL") )
        printf("%s\n", echo_stat.msh_path);     //print the shell path

    else
        printf("%s\n", arg2);                   //if nothing matches print the message as it is
}
