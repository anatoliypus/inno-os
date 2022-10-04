#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define STRING_MAX_LEN 1024

int main(int argc, char* argv[]) {
    int n;

    if (argc != 2 || sscanf(argv[1], "%d", &n) == 0 || n < 0 || n > 4) {
        printf("Incorrect command line arguments\n");
        return 1;
    }

    mkfifo("/tmp/ex1", 0777);

    int fd = open("/tmp/ex1", O_RDWR);
    if (fd == -1) {
        printf("Error while openening pipe.\n");
        return 3;
    }

    printf("Press Ctrl+C anytime to exit.\n");

    while (1) {
        printf("Type a message to publish it:\n");
        char s[STRING_MAX_LEN];
        fgets(s, STRING_MAX_LEN, stdin);
        for (int i = 0; i < n; i++) {
            if (write(fd, s, STRING_MAX_LEN) == -1) {
                printf("Error while writing to pipe.\n");
                return 2;
            }
        }
        sleep(1);
    }

    close(fd);
    return 0;
}