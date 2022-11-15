#include <stdio.h>

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
    int completing;
    int remaining;
} Process;

int main() {
    int num_processes;
    int quantum;
    
    printf("Please type the amount of processes:\n");
    if (scanf("%d", &num_processes) != 1 || num_processes < 1) {
        printf(ERROR_OUTPUT);
        exit(EXIT_FAILURE);
    }

    printf("Please type quantum:\n");
    if (scanf("%d", &quantum) != 1 || quantum < 0) {
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
        data[i].completing = 0;
        data[i].remaining = data[i].burst;
    }

    int time = 0;
    int done = 0;

    for (int i = 0; i < num_processes; i++)
        if (data[i].arrival == 0) {
            data[i].completing = 1;
            data[i].waiting = 0;
        }

    while (!done) {
        done = 1;
        for (int i = 0; i < num_processes; i++) {

            if (data[i].arrival <= time
                && data[i].burst == data[i].remaining
                && data[i].completing == 0) {
                done = 0;
                data[i].completing = 1;
                data[i].waiting = time - data[i].arrival;
            }

            if (data[i].completing) {
                done = 0;
                for (int j = 0; j < num_processes; j++) {
                    if (j != i && data[j].completing == 1 && data[i].completing == 1) {
                        if (data[i].remaining <= quantum)
                            data[j].waiting += data[i].remaining;
                        else
                            data[j].waiting += quantum;
                    }
                }
                if (data[i].remaining <= quantum) {
                    time += data[i].remaining;
                    data[i].remaining = 0;
                } else {
                    time += quantum;
                    data[i].remaining -= quantum;
                }
            }

            if (data[i].remaining <= 0 && data[i].completing) {
                data[i].completion = time;
                data[i].turn_around = time - data[i].arrival;
                data[i].completing = 0;
            }
        }
    }

    for (int i = 0; i < num_processes; i++) {
        printf("Process %d:\n", data[i].id + 1);
        printf("\tCompletion time: %d\n", data[i].completion);
        printf("\tTurn around time: %d\n", data[i].turn_around);
        printf("\tWaiting time: %d\n\n", data[i].waiting);
    }

    free(data);
}