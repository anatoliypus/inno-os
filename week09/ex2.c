#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024

// Actually, the amount of swaps remains zero even with big values.
// But I`ve noticed that amount of free pages decreases.
// Unfortunately, could not find any interesting regularities in the top command output.

int main() {
    void * ptrs[10];

    for (int i = 0; i < 10; i++) {
        void * mem = malloc(SIZE);
        ptrs[i] = mem;
        memset(mem, 0, SIZE);
        sleep(1);
    }

    for (int i = 0; i < 10; i++) {
        free(ptrs[i]);
    }
}
