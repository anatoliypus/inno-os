#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    int n;
    if (argc != 2 || (n = atoi(argv[1])) < 1) {
        printf("Wrong command line arguments given.\n");
        return EXIT_FAILURE;
    }

    pid_t main_pid = getpid();
    for (int i = 0; i < n; i++) {
        fork();
        sleep(5);
    }
}