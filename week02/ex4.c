#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256

int count(char* str, char ch);
void countAll(char* str);
char char_to_lowercase(char ch);

int main() {
    printf("Print a string to count occurrences of all characters:\n");
    char s[MAX_LENGTH];
    fgets(s, MAX_LENGTH, stdin);
    countAll(s);
    return 0;
}

int count(char* str, char symbolToFind) {
    int counter = 0;
    for (char* ch = str; *ch != '\0'; ch++) {
        if (*ch == symbolToFind)
            counter++;
    }
    return counter;
}

void countAll(char* str) {
    char characters[MAX_LENGTH + 1];
    *characters = '\0';
    for (char* ch = str; *ch != '\0'; ch++) {
        *ch = char_to_lowercase(*ch);
        int found = 0;
        char* c = characters;
        for (; *c != '\0'; c++) {
            if (*c == *ch) {
                found = 1;
            }
        }
        if (!found) {
            *c = *ch;
            *(c + 1) = '\0';
        }
    }
    int first = 1;
    for (char* ch = characters; *ch != '\0' && *ch != '\n'; ch++) {
        if (!first)
            printf(", ");
        else
            first = 0;
        printf("%c:%d", *ch, count(str, *ch));
    }
    printf("\n");
}

int char_to_digit(char ch) {
    return ch - 48;
}

char digit_to_char(int d) {
    return d + 48;
}

char char_to_lowercase(char ch) {
    if (ch >= 65 && ch <= 90) {
        return ch + 32;
    }
    return ch;
}
