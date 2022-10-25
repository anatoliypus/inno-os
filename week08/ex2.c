#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Please enter the N value:\n");
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("There is an error in input data.\n");
        return EXIT_FAILURE;
    }

    int * ptr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        ptr[i] = i;

    printf("The array:");
    for (int i = 0; i < n; i++)
        printf(" %d", ptr[i]);
    printf("\n");
    
    free(ptr);
}