#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

int main() {
    printf("This is my shell. Type `quit` command to exit.\n\n");
    const char quit_command[] = "quit\n";
    
    char input[MAX_LENGTH];
    while (1) {
        printf(">>> ");
        fgets(input, MAX_LENGTH, stdin);
        if (strcmp(quit_command, input) == 0)
            break;
        pid_t child = fork();
        if (child == 0) {
            system(input);
            printf(">>> ");
            exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}
