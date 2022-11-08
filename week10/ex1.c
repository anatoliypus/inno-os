#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILENAME_MAX_LEN 50
#define PAGES_MAX_AMOUNT 1000

typedef struct Page {
    int number;
    u_int8_t counter;
    int referenced;
    int empty;
} Page;

int main() {
    char filename[FILENAME_MAX_LEN];

    printf("Please type the name of input file: ");
    fgets(filename, FILENAME_MAX_LEN, stdin);
    char * p = filename;

    while (*p != '\n' && *p != '\0') p++;
    *p = '\0';

    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open this file.\n");
        exit(EXIT_FAILURE);
    }

    int sequence[PAGES_MAX_AMOUNT];
    int pageCounter = 0;

    while (fscanf(fp, "%d", sequence + pageCounter) == 1) {
        pageCounter++;
    }
    
    int page_frames[3] = {10, 50, 100};
    int hits[3] = {0, 0, 0};
    int misses[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
        int page_frame = page_frames[i];

        Page * memory = malloc(sizeof(Page) * page_frame);
        for (int j = 0; j < page_frame; j++) {
            memory[j].empty = 1;
            memory[j].counter = 0;
            memory[j].referenced = 0;
        }
        
        for (int j = 0; j < pageCounter; j++) {
            int coming = sequence[j];

            int found = 0;
            for (int k = 0; k < page_frame; k++) {
                if (memory[k].number == coming) {
                    memory[k].referenced = 1;
                    found = 1;
                }
            }
            if (found == 0) {
                int foundFreeSpace = 0;
                for (int k = 0; k < page_frame; k++) {
                    if (memory[k].empty == 1) {
                        memory[k].number = coming;
                        memory[k].empty = 0;
                        foundFreeSpace = 1;
                        break;
                    }
                }
                if (foundFreeSpace == 0) {
                    int min_value;
                    Page * min_ptr = NULL;
                    for (int k = 0; k < page_frame; k++) {
                        if (min_ptr == NULL || memory[k].counter < min_value) {
                            min_value = memory[k].counter;
                            min_ptr = memory + k;
                        }
                    }
                    min_ptr->counter = 0;
                    min_ptr->number = coming;
                    min_ptr->referenced = 0;
                    min_ptr->empty = 0;
                }
            }

            for (int k = 0; k < page_frame; k++) {
                if (memory[k].empty == 0) {
                    memory[k].counter = memory[k].counter >> 1;
                    if (memory[k].referenced == 1) {
                        memory[k].referenced = 0;
                        memory[k].counter |= 0b10000000;
                    }
                }
            }

            if (found == 1) {
                hits[i]++;
            } else {
                misses[i]++;
            }
        }
        free(memory);
    }

    for (int i = 0; i < 3; i++) {
        printf("For page frame = %d:\n\tHits = %d\n\tMisses = %d\n", page_frames[i], hits[i], misses[i]);
        double ratio = hits[i] * 1.0 / misses[i];
        printf("\tHit/Miss ratio = %f\n", ratio);
    }

    return 0;
}