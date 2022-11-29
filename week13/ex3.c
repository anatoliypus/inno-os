#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define MAX_ELEMENTS 255

typedef struct set {
    int counter;
    int elements[MAX_ELEMENTS];
} set;

set * create_set() {
    set * s = (set *)malloc(sizeof(set));
    s->counter = 0;
    return s;
}

int exists_in_set(set * set, int el) {
    int exists = 0;
    for (int i = 0; i < set->counter; i++) {
        if (set->elements[i] == el) {
            exists = 1;
            break;
        }
    }
    return exists;
}

void add_to_set(set * set, int el) {
    if (exists_in_set(set, el) == 0) {
        set->elements[(set->counter)++] = el;
    }
}

void remove_from_set(set * set, int el) {
    for (int i = 0; i < set->counter; i++) {
        if (set->elements[i] == el) {
            (set->counter)--;
            for (int j = i; j < set->counter; j++) {
                set->elements[j] = set->elements[j+1];
            }
        }
    }
}

void delete_set(set * set) {
    if (set != NULL)
        free(set);
}

int get_number_of_elements_in_set(set * set) {
    return set->counter;
}

int main() {
    int file = open("/dev/input/by-path/pci-0000:00:04.0-usb-0:3:1.0-event-kbd", O_RDONLY);
    if (file < 0) {
        printf("Failed to open file to read events.\n");
        exit(EXIT_FAILURE);
    }

    struct input_event event;

   struct termios termios;
   tcgetattr(STDIN_FILENO, &termios);

   termios.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
   set * s = create_set();

   printf("Available shortcuts:\n");
   printf("\tP + E -> 'I passed the exam!'\n");
   printf("\tC + A + P -> 'Get some cappuccino!'\n");
   printf("\t1 + 3 -> 'Lab for week 13 is done!'\n");

   // 0 for initial state
   // 1 if P + E shortcut
   // 2 if C + A + P shortcut
   // 3 if 1 + 3 shortcut
   int last_action = 0;

    while (1) {
        if (read(file, &event, sizeof(event)) == -1) {
            printf("Error while reading an event. Exiting...\n");
            exit(EXIT_FAILURE);
        }
        if (event.type == 1 && (event.value == 1 || event.value == 2)) {
            if (event.value == 2) {
                last_action = 0;
            }
            add_to_set(s, event.code);

        } else if (event.type == 1 && event.value == 0) {
            last_action = 0;
            remove_from_set(s, event.code);
        }

        if (exists_in_set(s, 25) && exists_in_set(s, 18) && get_number_of_elements_in_set(s) == 2 && last_action != 1) {
            printf("I passed the exam!\n");
            last_action = 1;
        }
        if (exists_in_set(s, 46) && exists_in_set(s, 30) && exists_in_set(s, 25) && get_number_of_elements_in_set(s) == 3 && last_action != 2) {
            printf("Get some cappuccino!\n");
            last_action = 2;
        }
        if (exists_in_set(s, 2) && exists_in_set(s, 4) && get_number_of_elements_in_set(s) == 2 && last_action != 3) {
            printf("Lab for week 13 is done!\n");
            last_action = 3;
        }
    }

    delete_set(s);
}
