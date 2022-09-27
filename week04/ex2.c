#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 120

int main() {
    int num_processes;
    if (scanf("%d", &num_processes) > 1 ||
        num_processes < 1
        || ARRAY_SIZE % num_processes != 0
        || num_processes > ARRAY_SIZE) {
        printf("Wrong input given\n");
        return EXIT_FAILURE;
    }

    int u[ARRAY_SIZE], v[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        u[i] = rand() % 99;
        v[i] = rand() % 99;
    }

    pid_t main_pid = getpid();
    pid_t processes[ARRAY_SIZE];

    FILE * fp;

    if ((fp = fopen("temp.txt", "w")) == NULL) {
        printf("Error while working with file.\n");
        return EXIT_FAILURE;
    }

    int operations_for_process = ARRAY_SIZE / num_processes;

    for (int i = 0; i < num_processes; i++) {
        if (main_pid == getpid()) {
            processes[i] = fork();
            if (processes[i] == 0) { // in created process
                for (int j = i * operations_for_process; j < i * operations_for_process + operations_for_process; j++) {
                    fprintf(fp, "%d\n", v[j] * u[j]);
                } 
            }
        }
    }

    if (main_pid == getpid()) {
        while(wait(0) > 0);
        fclose(fp);

        if ((fp = fopen("temp.txt", "r")) == NULL) {
            printf("Error while working with file.\n");
            return EXIT_FAILURE;
        }

        long long sum = 0;

        for (int i = 0; i < ARRAY_SIZE; i++) {
            int n;
            fscanf(fp, "%d\n", &n);
            sum += n;
        }

        printf("The result: %lld\n", sum);
    }

    return EXIT_SUCCESS;
}