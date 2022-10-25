#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void * my_realloc(void * ptrmem, size_t new_size, size_t old_size) {
    if (ptrmem == NULL)
        return malloc(new_size);
    
    if (new_size == 0) {
        free(ptrmem);
        return NULL;
    }

    if (new_size < 0 || old_size < 0) {
        exit(EXIT_FAILURE);
    }

    if (new_size <= old_size) {
        return ptrmem;
    }

    void * new_ptr = malloc(new_size);
    memcpy(new_ptr, ptrmem, old_size);
    free(ptrmem);
    return new_ptr;
}

// Testing

int main() {
    printf("Print initial size of array:\n");
    int size;
    scanf("%d", &size);

    int * ptr = my_realloc(NULL, size * sizeof(int), 0);
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }

    printf("Elements:");
    for (int i = 0; i < size; i++) {
        printf(" %d", ptr[i]);
    }
    printf("\n");

    printf("Print new size of array:\n");
    int new_size;
    scanf("%d", &new_size);

    ptr = my_realloc(ptr, new_size * sizeof(int), size * sizeof(int));
    for (int i = size; i < new_size; i++) {
        ptr[i] = i;
    }

    printf("Elements:");
    for (int i = 0; i < new_size; i++) {
        printf(" %d", ptr[i]);
    }
    printf("\n");

    free(ptr);

    return 0;
}