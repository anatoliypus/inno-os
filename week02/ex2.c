#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

int main() {
    char str[MAX_LENGTH];
    char str_reversed[MAX_LENGTH];
    printf("Please type a string.\n");
    fgets(str, MAX_LENGTH, stdin);
    size_t str_len = strlen(str);
    int reversed_start = -1;
    for (int counter = 0; counter < str_len; counter++) {
        if (str[counter] == '.' || str[counter] == '\n') {
            break;
        }
        str_reversed[str_len - counter - 1] = str[counter];
        reversed_start = str_len - counter - 1;
    }
    printf("Your string after reversing before dot:\n\"");
    for (int i = reversed_start; i < str_len; i++) {
        printf("%c", str_reversed[i]);
    }
    printf("\"\n");
    return 0;
}