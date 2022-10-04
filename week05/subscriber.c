#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#define STRING_MAX_LEN 1024

int mssleep(long miliseconds)
{
   struct timespec rem;
   struct timespec req= {
       (int)(miliseconds / 1000),
       (miliseconds % 1000) * 1000000
   };

   return nanosleep(&req , &rem);
}

int main() {
    char s[STRING_MAX_LEN];

    int fd = open("/tmp/ex1", O_RDONLY);

    if (fd == -1) {
        printf("Error while openening pipe.\n");
        return 3;
    }

    while (1) {
        if (read(fd, s, STRING_MAX_LEN) == -1) {
            printf("Error while reading from pipe.\n");
            return 2;
        }
        printf("Got in subscriber: %s", s);
        mssleep(500);
    }

    close(fd);
    return 0;
}