//arguments: another program and its arguments
//runs program in another process using either fork+exec*, popen, or system
//Inspects the program's calls to malloc and free
//Keeps track of leaks and how much space
//run program taken in as an argument. to do that it must be compiled as well
//fork+exec* use fork to create a child and have the child run the program

#include <unistd.h>
#include <stdio.h>  


int main(int argc, char **argv)
{
    //Declare arguments to the program being checked.
    char *arg_list[]={NULL};

    if(argc > 2){
        int index = 0;
        for(int i = 2; i < argc; i++){
            arg_list[index] = argv[i];
            index++;
        }
        arg_list[index] = NULL;

        //checks that arg_list is correct
        for(int j = 0; j < index+1; j++){
        printf("%s\n", arg_list[j]);
        }
    }

    
    //Create the child process
    pid_t pid = fork();

    //Separate child from parent
    if(pid == -1){
        //error, failed to fork

    }else if (pid == 0){
        //correctly runs the program to be checked
        execvp(argv[1], arg_list);

    }else if (pid > 0){
        //Parent waits for child
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}