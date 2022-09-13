#include <stdio.h>

void printPattern1(int n);
void printPattern2(int n);
void printPattern3(int n);

int main() {
    printPattern1(7);
    printf("\n\n");
    printPattern2(7);
    printf("\n\n");
    printPattern3(7);
    return 0;
}

void printPattern1(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void printPattern2(int n) {
    for (int i = 1; i <= n / 2; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    if (n % 2 == 1) {
        for (int i = 1; i <= n / 2 + 1; i++) {
            printf("*");
        }
        printf("\n");
    }
    for (int i = n / 2; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void printPattern3(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("*");
        }
        printf("\n");
    }
}
