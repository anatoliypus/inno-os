#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>

#define SIZE 1024

int main() {
    void * ptrs[10];

    for (int i = 0; i < 10; i++) {
        void * mem = malloc(SIZE);
        ptrs[i] = mem;
        memset(mem, 0, SIZE);
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        printf("Iteration %d:\n", i);
        printf("\tmax resident set size %ld\n", usage.ru_maxrss);
        printf("\tintegral shared text memory size %ld\n", usage.ru_ixrss);
        printf("\tintegral unshared data size %ld\n", usage.ru_idrss);
        printf("\tintegral unshared stack size %ld\n", usage.ru_isrss);
        printf("\tpage reclaims %ld\n", usage.ru_minflt);
        printf("\tpage faults %ld\n", usage.ru_majflt);
        printf("\tswaps %ld\n", usage.ru_nswap);
        sleep(1);
    }

    for (int i = 0; i < 10; i++) {
        free(ptrs[i]);
    }
}
