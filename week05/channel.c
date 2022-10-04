#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STRING_MAX_LEN 1024

int main() {
    int fd[2]; // fd[0] - read end, fd[1] - write end

    if(pipe(fd) == -1) { 
        printf("Error while creating a pipe.");
        return 1;
    };

    printf("Press Ctrl+C anytime to quit.\n");

    int id = fork();

    if (id == 0) {
        close(fd[0]);
    } else {
        close(fd[1]);
    }

    while (1) {
        if (id == 0) {
            printf("Type a message for publisher process:\n");
            char s[STRING_MAX_LEN];
            fgets(s, STRING_MAX_LEN, stdin);
            if (write(fd[1], s, STRING_MAX_LEN) == -1) {
                printf("Error while writing to pipe.\n");
                return 2;
            }
            sleep(1);
            
        } else {
            char s[STRING_MAX_LEN];
            if (read(fd[0], s, STRING_MAX_LEN) == -1) {
                printf("Error while reading from pipe.\n");
                return 2;
            }
            printf("Got from publisher in subscriber: %s\n", s);
            fflush(stdout);
        }
    }

    if (id == 0) {
        close(fd[1]);
    } else {
        close(fd[2]);
    }

    return 0;
}
