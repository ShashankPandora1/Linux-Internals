/*-----------------------------------------------------------------------------------------------------------
 *
 *  Author Name     : Shashank Pandora
 *  Organisation    : Emertxe Information Technologies (P) Ltd.
 *  Date            : 10/10/2020
 *  Description     : Write a C program to implement your own minishell to execute limited sets of command
 *
 *----------------------------------------------------------------------------------------------------------*/


#include "main.h"

int main(int argc, char **argv)
{
    clear_screen();                         //calling clear screen fucntion to clear the screen
    
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);        //registering signals SIGINT and SIGTSTP for all the processes

    get_curr_path();                        //getting current path for shell prompt message

    set_echo_vals(argv);                    //calling echo fucntion to set the values for echo command

    char prompt[70] = "minishell", input_str[70];

    scan_input(prompt, input_str);

    return 0;
}
