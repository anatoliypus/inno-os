#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

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

    while (1) {
        if (read(file, &event, sizeof(event)) == -1) {
            printf("Error while reading an event. Exiting...\n");
            exit(EXIT_FAILURE);
        }
        // printf("Type %d   Code %d   Value %d\n", event.type, event.code, event.value);
        if (event.type == 1 && event.value == 1) {
            printf("PRESSED %#06x %d\n", event.code, event.code);
        } else if (event.type == 1 && event.value == 0) {
            printf("RELEASED %#06x %d\n", event.code, event.code);
        }
    }
}
