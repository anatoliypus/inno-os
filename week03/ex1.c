#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CELLS_AMOUNT 5

int foo(int age);

int main() {
    const int x = 10;
    int * q = &x;
    int const * p = malloc(sizeof(const int) * CELLS_AMOUNT);

    int* temp_ptr = p;
    for (int i = 0; i < CELLS_AMOUNT; i++) {
        *(temp_ptr+i) = x;
    }
    
    for (int i = 0; i < CELLS_AMOUNT; i++) {
        printf("%p\n", p+i);
    }

    printf("Type 5 ages:\n");

    temp_ptr = p;
    for (int i = 0; i < CELLS_AMOUNT; i++) {
        scanf("%d", temp_ptr+i);
    }

    temp_ptr = p;
    for (int i = 0; i < CELLS_AMOUNT; i++) {
        *(temp_ptr+i) = foo(*(temp_ptr+i));
    }

    free(p);
}

int foo(int age) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900 - age;
}