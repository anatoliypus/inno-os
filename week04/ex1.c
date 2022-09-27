#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    pid_t first_child_pid = fork();
    pid_t second_child_pid;

    if (first_child_pid > 0)
        second_child_pid = fork();
    
    clock_t start, stop;
    start = clock();
    
    if (first_child_pid > 0 && second_child_pid > 0) { // main process
        printf("The pid of main process = %d; ppid = %d\n", getpid(), getppid());
        while (wait(0) > 0);
    }

    if (first_child_pid == 0) { // first child
        printf("The pid of first child process = %d; ppid = %d\n", getpid(), getppid());
    }

    if (second_child_pid == 0 && first_child_pid > 0) { // second child
        printf("The pid of second child process = %d; ppid = %d\n", getpid(), getppid());
    }

    stop = clock();
    printf("\tExecution time of process with pid %d: %f\n", getpid(), (double)(stop - start) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}