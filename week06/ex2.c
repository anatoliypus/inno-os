#include <stdio.h>
#include <stdlib.h>

#define ERROR_OUTPUT "Incrorrect input data.\n"

typedef struct Process {
    int id;
    int completion;
    int turn_around;
    int waiting;
    int arrival;
    int burst;
} Process;

int cmpfunc (const void * _a, const void * _b) {
    Process * a = (Process *)_a;
    Process * b = (Process *)_b;
    return a->burst - b->burst;
}

int main() {
    int num_processes;
    printf("Please type the amount of processes:\n");
    if (scanf("%d", &num_processes) != 1 || num_processes < 1) {
        printf(ERROR_OUTPUT);
        exit(EXIT_FAILURE);
    }

    printf("Please type arrival and burst time in the following format:\n");
    printf("<arrival time> <burst time>\\n \n");
    Process * data = malloc(sizeof(Process) * num_processes);
    for (int i = 0; i < num_processes; i++) {
        if (scanf("%d %d", &data[i].arrival, &data[i].burst) != 2
            || data[i].arrival < 0 || data[i].burst < 0) {
            printf(ERROR_OUTPUT);
            exit(EXIT_FAILURE);
        }
        data[i].id = i;
    }

    qsort(data, num_processes, sizeof(Process), cmpfunc);

    int time = 0;

    for (int i = 0; i < num_processes; i++) {
        data[i].waiting = time - data[i].arrival;
        data[i].completion = time + data[i].burst;
        time += data[i].burst;
        data[i].turn_around = data[i].burst + data[i].waiting;
        printf("Process %d:\n", data[i].id + 1);
        printf("\tCompletion time: %d\n", data[i].completion);
        printf("\tTurn around time: %d\n", data[i].turn_around);
        printf("\tWaiting time: %d\n\n", data[i].waiting);
    }

    free(data);
}