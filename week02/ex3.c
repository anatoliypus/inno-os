#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

// ATTENTION
/* 
    NOTE: In exercise №3 and exercise №4 I`ve used pointers,
    which are prohibited. Actually, there were such cases,
    where not using pointer for an array of characters is
    unacceptable. For example, in function convert I have to
    somehow return the result. I cannot do it without pointers,
    because static variables would be erased.

*/
// ATTENTION

char* convert(const char* x, int s, int t);
int char_to_digit(char ch);
char digit_to_char(int d);

int main() {
    printf("Please type source number system:\n");
    int s;
    scanf("%d", &s);

    if (s < 2 || s > 10) {
        printf("Wrong number system is given\n");
        return s;
    }

    fflush(stdin);

    printf("Please type a number to convert:\n");
    char x[MAX_LENGTH];
    fgets(x, MAX_LENGTH, stdin);

    for (int i = 0; i < strlen(x); i++) {
        if (char_to_digit(x[i]) >= s) {
            printf("The number does not correspond to source number system.\n");
            return 0;
        }
    }

    printf("Please type number system to convert in:\n");
    int t;
    scanf("%d", &t);

    if (t < 2 || t > 10) {
        printf("Wrong number system is given\n");
        return t;
    }

    char* result = convert(x, s, t);
    printf("The result:\n%s\n", result);

    free(result);
    return 0;
}

char* convert(const char* x, int s, int t) {
    if (s == t) {
        char* result = malloc(sizeof(char) * strlen(x));
        strcpy(result, x);
        result[strlen(x) - 1] = '\0';
        return result;
    }
    long long x_decimal = 0;
    long long len = strlen(x) - 1;
    if (s != 10) {
        for (long long i = 0; i < len; i++) {
            x_decimal += char_to_digit(x[len - i - 1]) * powl(s, i);
        }
    } else {
        for (long long i = 0; i < len; i++) {
            x_decimal = x_decimal * 10 + char_to_digit(x[i]);
        }
    }
    long long result_len = 1;
    for (; pow(t, result_len) <= x_decimal; result_len++);
    char* result = malloc(sizeof(char) * result_len + 1);
    long long i = 0;
    while (x_decimal > 0) {
        result[result_len - i++ - 1] = digit_to_char(x_decimal % t);
        x_decimal = x_decimal / t;
    }
    result[result_len] = '\0';
    return result;
}

int char_to_digit(char ch) {
    return ch - 48;
}

char digit_to_char(int d) {
    return d + 48;
}