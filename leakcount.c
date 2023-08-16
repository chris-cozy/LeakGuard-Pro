#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <program> [arguments]\n", argv[0]);
        return 1;
    }

    // Create argument list for the program being checked
    char *arg_list[argc];
    for (int i = 1; i < argc; i++)
    {
        arg_list[i - 1] = argv[i];
    }
    arg_list[argc - 1] = NULL;

    // Create the child process
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork error");
    }
    else if (pid == 0)
    {
        // Child process: run the program to be checked
        execvp(arg_list[0], arg_list);
        perror("Execvp error");
        exit(1);
    }
    else
    {
        // Parent process: wait for child
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}