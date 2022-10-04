#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define MESSAGE_MAX_LEN 256

typedef struct Thread {
    pthread_t id;
    int i;
    char message[MESSAGE_MAX_LEN];
} Thread;

void * func(void * t) {
    Thread * thread = (Thread *)t;
    printf("Id: %d, message: %s\n", thread->id, thread->message);
    return NULL;
}

int main() {
    printf("Type number of threads to create:\n");
    int threads_amount;
    scanf("%d", &threads_amount);

    if (threads_amount < 1) {
        printf("Incorrect input data.\n");
        return 1;
    }

    Thread * threads = malloc(sizeof(Thread) * threads_amount);
    for (int i = 0; i < threads_amount; i++) {
        threads[i].i = i;
        char message[MESSAGE_MAX_LEN];
        sprintf(message, "Hello from thread %d", i);
        strcpy(threads[i].message, message);
        pthread_t thread;
        if (pthread_create(&thread, NULL, &func, threads + i) != 0) {
            printf("Error while creating a new thread.\n");
            return 1;
        } else {
            printf("Thread %d created.\n", i);
        }
        threads[i].id = thread;
        pthread_join(thread, NULL);
    }
    return 0;
}