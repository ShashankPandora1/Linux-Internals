#include "main.h"

extern char path[PATH_MAX];

void scan_input(char *prompt, char *input_str)      //scan for the user input
{
    int type, prompt_flag = 0;

    while ( 1 )                                     //iterate loop infinite times
    {
        if ( !prompt_flag )                         //if prompt message not changed
            printf(BOLD GREEN"%s"RESET":"BOLD BLUE"%s"RESET"$ ", prompt, path);     //print current prompt message

        else
            printf("%s", prompt);                   //if changed print the updated shell message
        
        memset(input_str, '\0', strlen(input_str) + 1); //clear the input string 
        scanf("%[^\n]", input_str);                 //read input from user
        getchar();

        if ( !input_str[0] )                        //if nothing entered and pressed enter
            continue;

        /* if first 4 characters of string are 'PS1=' then change the prompt message */ 
        if ( !strncmp(input_str, "PS1=", 4) )       //if user want to change the prompt message go to this block
        {
            prompt_flag = 1;                        //set the flag

            strcpy(prompt, &input_str[4]);          //update the message
            continue;
        }
        
        /* else treat it like a normal command */
        type = check_command_type(input_str);       //function call to check the command type

        if ( type == BUILT_IN )
            execute_internal_command(input_str);    //if builtin call this function

        else        /* EXTERNAL */
            execute_external_command(input_str);
    }
}

int check_command_type(char *input_str)             //functin def to check command type
{
    char *builtins[] = {"echo", "cd", "pwd", "mkdir", "rmdir", "exit", "clear", "fg", "bg", "jobs", NULL};
                                                                                //defining an array for builtins
    char *command = (char *)malloc((strlen(input_str) + 1) * sizeof(char));
    strcpy(command, input_str);                     //allocate memory and store the input string in a new string
    
    strtok(command, " ");                           //tokenize the string as per the space character

    for ( int i = 0; builtins[i] != NULL; i++ )     //iterate as per the builtin array
    {
        if ( !strcmp(builtins[i], command) )        //if mataches return back as BUILT_IN macro
        {
            free(command);
            return BUILT_IN;
        }
    }
   
    free(command);                                  //free the memory
    return EXTERNAL;                                //if doesn't match treat it like a normal command
}
