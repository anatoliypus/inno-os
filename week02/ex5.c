#include <stdio.h>

long tribonacci(int n);

int main() {
    printf("%ld\n%ld\n", tribonacci(4), tribonacci(36));
    return 0;
}

long tribonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n >= 1 && n <= 2) {
        return 1;
    }
    long n1 = 0;
    long n2 = 1;
    long n3 = 1;
    long n4 = 2;
    for (int i = 4; i < n; i++) {
        n1 = n2;
        n2 = n3;
        n3 = n4;
        n4 = n1 + n2 + n3;
    }
    return n4;
}
