#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000

static int malloc_counter = 0;
static int total_leak_size = 0;
int arr[SIZE];

void *(*original_malloc)(size_t size);
void (*original_free)(void *);

void *malloc(size_t size)
{
    if (!original_malloc)
    {
        original_malloc = dlsym(RTLD_NEXT, "malloc");
    }

    void *ptr = original_malloc(size);

    malloc_counter++;
    total_leak_size += size;

    return ptr;
};

void free(void *ptr)
{
    if (!original_free)
    {
        original_free = dlsym(RTLD_NEXT, "free");
    }
    malloc_counter--;
    total_leak_size -= sizeof(ptr);

    original_free(ptr);
};

__attribute__((destructor)) void end(void)
{
    if (malloc_counter > 0)
    {
        printf("Total Leaks: %d\n", malloc_counter);
        printf("Total Leak Size: %d bytes\n", total_leak_size);
    }
}