#include "main.h"

char path[PATH_MAX];

extern pid_t j_pid[20];
extern int i_jobs;
extern pid_t pid;

void execute_internal_command(char *input_str)      //function call to iterate
{
    char *command = (char *)malloc((strlen(input_str) + 1) * sizeof(char));

    strcpy(command, input_str);                     //allocate memory and copy the string
    char *token = strtok(command, " ");

    if ( !strcmp(token, "exit") )
        exit(EXIT_SUCCESS);                         //if user enters exit terminate the program

    else if ( !strcmp(token, "pwd") )               //print the current path
        printf("%s\n", path);

    else if ( !strcmp(token, "cd") )                //go to new directory
    {
        token = strtok(NULL, " ");                  //get the next token
        if ( chdir(token) == -1 )
            perror("chdir");

        else
            get_curr_path();                        //and update the current path name
    }

    else if ( !strcmp(token, "mkdir") )             //create new folder
    {
        token = strtok(NULL, " ");

        if ( mkdir(token, 0755) == -1 )             //as per the permissions
            perror("mkdir");
    }

    else if ( !strcmp(token, "rmdir") )
    {
        token = strtok(NULL, " ");

        if ( rmdir(token) == -1 )                   //remove the directory
            perror("rmdir");
    }

    else if ( !strcmp(token, "echo") )
    {
        token = strtok(NULL, " ");
        echo_execute(token);
    }

    else if ( !strcmp(token, "fg") )
    {
        if ( i_jobs > 0 )
        {
            kill(j_pid[i_jobs], SIGCONT);           //if fg is entered run the last stopped program
            pid = j_pid[i_jobs];
            i_jobs -= 1;
            foreground();
        }
        else
            printf("Error: No stopped processes\n");
    }

    else if ( !strcmp(token, "bg") )                //for programs running in background
    {
    }

    else if ( !strcmp(token, "jobs") )
        job_list();                                 //print the list of jobs

    else if ( !strcmp(token, "clear") )
        clear_screen();                             //clear the screen

    else
        fprintf(stderr, "Error: Command not found\n");

    free(command);
}

void clear_screen()
{
    printf("\e[1;1H\e[2J");                     //regular expression for clearing the screen
}

void get_curr_path()
{
    if ( getcwd(path, PATH_MAX) == NULL )
        perror("getcwd");                                       //get the current path and store in path variable
}