#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/reg.h>

//take in a program and its arguments as a single argument
//will run this in another process and report statics on the system calls that it uses        
//These statistics will be reported in an output file, specified on the command line
//At the bare minimum, use PTRACE_TRACEME, PTRACE_SYSCALL, PTRACE_PEEKUSER, PTRACE_SETOPTIONS requests, and PTRACE_O_TRACESYSGOOD
//In the output, each system call should be on its own line
//Report the system call number, followed by a tab, followed by the number of times that system call was called
//Results should be in order of increasing system call count

int main(int argc, char **argv)
{
    if(argc != 3){
        perror("Incorrect argument amount");
    }
    //File handling
    char *newProg[] = {argv[1]};
    FILE *out_file;
    out_file = fopen(argv[2], "w");
    
    //Tokenize the arguments
    char delim =' ';
    char *ptr = strtok(newProg, &delim);
    while(ptr != NULL){
        ptr = strtok(NULL, &delim);
    }

    //Create the child process
    long orig_rax;

    pid_t pid = fork();
    struct user_regs_struct regs;
    int count = 0;
    int in_call = 0;

    //Separate child from parent
    if(pid == -1){
        perror("fork");
        exit(1);
    }else if (pid == 0){
        ptrace(PTRACE_TRACEME, pid, NULL, NULL);
        execvp(newProg[0], newProg);
    }else{
        //Parent waits for child
        int status;
        wait(&status);
        ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);

        while(status ==1407){
            orig_rax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_RAX, NULL);
            if(!in_call){
                //printf("SystemCall %ld\n", orig_rax);
                fprintf(out_file,"SystemCall %ld\n", orig_rax);
                in_call = 1;
                count++;
            }else{
                in_call = 0;
                ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
                wait(&status);
            }
        }
        //printf("Number of system calls: %d\n", count);
        fprintf(out_file, "Number of system calls: %d\n", count);

        //DEAD CODE
       /* while(1){
            if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP){
                // stopped before or after a system call -- query the child and print out info
                orig_rax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_RAX, NULL);
                printf("The child made a syscall %ld\n", orig_rax);
                ptrace(PTRACE_CONT, pid, NULL, NULL);
            }
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                // child has exited or terminated
                break;
            }
            p//trace(PTRACE_SYSCALL, 0, 0, 0);  // ignore any signal and continue the child
        } */

    }
    fclose(out_file);
    return 0;
}