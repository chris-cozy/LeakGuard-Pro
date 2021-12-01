//shim library that implements the two functions
#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000

//Use data structures to represent the memory allocations
//Leakcount does not need to communicate with the shim
//Leakcount should not do anything between starting the child and the child process finishing
//This makes it so that the process doesn't even know there is communication, could even use regular file I/O

//An easier option is to make everything happen in the shim. A consideration is when to actually print leaks in the shim.
//For a memory allocation to be considered a leak, the child process needs to finish to give any allocation the opportunity to be freed
//This means that the shim output can't happen earlier than that point
//In the project-write up there are mentions and resources about compiler constructors and destructors which will make this easier

//Could make an array of the malloc sizes, then when one is freed, change the value to 0 

int malloc_counter = 0;
int total_leak_size = 0;
int arr[SIZE];

//Constructor and Destructor
//Plan: Create a Destructor that decides which allocations are leaks and outputs to the terminal
/*
__attribute__((constructor)) void begin (void){
    printf("START\n");
}
*/
__attribute__((destructor)) void end (void){
    printf("TOTAL   %d  %d\n",malloc_counter, total_leak_size);
}

//Calling original version of malloc
void *(*original_malloc) (size_t size);
void (*original_free)(void *);

//Not responsible for allocating memory, the stdlib's malloc is still responsible for that. This malloc is a middle man between the two
void *malloc(size_t size){
    original_malloc = dlsym(RTLD_NEXT, "malloc");
    void *ptr = original_malloc(size);

    malloc_counter++;
    total_leak_size += size;

    return ptr;
};


void free (void *ptr){
    malloc_counter--;
    total_leak_size = total_leak_size - sizeof(ptr);

    original_free = dlsym(RTLD_NEXT, "free");
    original_free(ptr);
};


