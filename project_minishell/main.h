#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdio_ext.h>                      //including all the required header files
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>

#define BUILT_IN    1
#define EXTERNAL    2                       //defining macros for command type

#define BOLD        "\x1b[1m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"              //defining color macros
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE       "\x1b[37m"
#define RESET       "\x1b[0m"

#define PATH_MAX    100                     //max size of path

typedef struct echo_values_store
{
    int exit_stat;
    int msh_pid;
    char msh_path[100];
}echo_val;                                  //structure to store echo command related values

void get_curr_path();                                       //function prototype to get and store current path
void scan_input(char *prompt, char *input_str);             //fucntion prototype to scan the input from the user
void clear_screen();                                        //function prototype to clear the screen
int check_command_type(char *input_str);                    //function prototype to check the command type
void execute_internal_command(char *input_str);             //function prototype to execute builtin commands
void execute_external_command(char *input_str);             //function prototype to execute external commands
int n_pipe(char *args[], int cmd_count, int *cmd_loc);     //function prototype for n pipe
void set_echo_vals(char *argv[]);                           //function prototyte to set the echo command values
void echo_execute(char *arg2);                              //function prototype to execute exho commands
void signal_handler(int signum);                            //function prototype for signal handler
void job_list();                                            //function prototype to print jobs list
void foreground();                                          //function prototype to run stopped processes

#endif
