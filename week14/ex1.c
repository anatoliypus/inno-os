#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUTFILE "input.txt"
#define MAX_LEN 10

int is_digit(char ch);
int char_to_int(char ch);

int main() {
    FILE * fp = fopen(INPUTFILE, "r");

    if (fp == NULL) {
        printf("Error while trying to open %s.\n", INPUTFILE);
        exit(EXIT_FAILURE);
    }

    char str[MAX_LEN];
    int read_e = 1;
    int read_a = 0;
    int read_c = 0;
    int read_r = 0;
    int counter = 0;
    int error = 0;

    int e[MAX_LEN];
    int a[MAX_LEN];
    int c[MAX_LEN][MAX_LEN];
    int r[MAX_LEN][MAX_LEN];

    for (int i = 0; i < MAX_LEN; i++) {
        e[i] = -1;
        a[i] = -1;
        for (int j = 0; j < MAX_LEN; j++) {
            c[i][j] = -1;
            r[i][j] = -1;
        }
    }

    while (!feof(fp)) {

        if (feof(fp)) {
            break;
        }
        fgets(str, MAX_LEN, fp);

        if (strlen(str) == 1 || strlen(str) == 0 || feof(fp)) {
            counter = 0;
            if (read_e) {
                read_e = 0;
                read_a = 1;
            } else if (read_a) {
                read_a = 0;
                read_c = 1;
            } else if (read_c) {
                read_c = 0;
                read_r = 1;
            } else {
                break;
            }
            continue;
        }

        char ch;
        int waiting_space = 0;
        int success = 1;

        int el_counter = 0;
        for (int i = 0; i < strlen(str) - 1; i++) {
            ch = str[i];
            if (!waiting_space && (!is_digit(ch) || char_to_int(ch) < 0)) {
                success = 0;
                break;
            } else if (waiting_space && ch == ' ') {
                waiting_space = 0;
                continue;
            } else if (waiting_space && ch != ' ') {
                success = 0;
                break;
            }

            if (!waiting_space && is_digit(ch)) {
                waiting_space = 1;
                if (read_e) {
                    e[el_counter] = char_to_int(ch);
                }
                if (read_a) {
                    a[el_counter] = char_to_int(ch);
                }
                if (read_c) {
                    c[counter][el_counter] = char_to_int(ch);
                }
                if (read_r) {
                    r[counter][el_counter] = char_to_int(ch);
                }
                el_counter++;
            }
        }

        if (!success) {
            error = 1;
            break;
        }

        counter++;
    }

    if (error) {
        printf("Invalid input data.\n");
        exit(EXIT_FAILURE);
    }

    int e_len, a_len, c_rows, c_cols, r_rows, r_cols;

    for (int i = 0; i < MAX_LEN; i++) {
        if (e[i] == -1) {
            e_len = i;
            break;
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        if (a[i] == -1) {
            a_len = i;
            break;
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        if (c[i][0] == -1) {
            break;
        }
        for (int j = 0; j < MAX_LEN; j++) {
            if (c[i][j] == -1) {
                c_rows = i + 1;
                c_cols = j;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        if (r[i][0] == -1) {
            break;
        }
        for (int j = 0; j < MAX_LEN; j++) {
            if (r[i][j] == -1) {
                r_rows = i + 1;
                r_cols = j;
                break;
            }
        }
    }

    if (e_len != a_len || c_rows != r_rows) {
        printf("Invalid input data.\n");
        exit(EXIT_FAILURE);
    }
    
    error = 0;

    for (int i = 0; i < c_rows; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (j == 0 || (c[i][j] == -1 && j == e_len))
                break;
            if (c[i][j] == -1 && j != e_len) {
                error = 1;
                break;
            }
        }
        if (error) 
            break;
    }

    for (int i = 0; i < r_rows; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            if (j == 0 || (r[i][j] == -1 && j == e_len))
                break;
            if (r[i][j] == -1 && j != e_len) {
                error = 1;
                break;
            }
        }
        if (error) 
            break;
    }

    if (error) {
        printf("Invalid input data.\n");
        exit(EXIT_FAILURE);
    }

    int temp[MAX_LEN];

    for (int i = 0; i < MAX_LEN; i++) {
        temp[i] = 0;
    }

    for (int i = 0; i < c_rows; i++) {
        for (int j = 0; j < c_cols; j++) {
            temp[j] += c[i][j];
        }
    }

    for (int i = 0; i < e_len; i++) {
        if (temp[i] + a[i] != e[i]) {
            error = 1;
        }
    }

    if (error) {
        printf("Invalid input data.\n");
        exit(EXIT_FAILURE);
    }

    int finished = 0;
    int finished_arr[MAX_LEN];

    for (int i = 0; i < MAX_LEN; i++) {
        finished_arr[i] = 0;
    }

    int deadlock = 0;
    while (finished < r_rows) {
        int made_one = 0;
        for (int i = 0; i < r_rows; i++) {
            if (!finished_arr[i]) {
                for (int j = 0; j < c_cols; j++) {
                    if (c[i][j] + a[j] < r[i][j]) {
                        continue;
                    } else {
                        made_one = 1;
                        finished++;
                        finished_arr[i] = 1;
                        for (int k = 0; k < a_len; k++) {
                            a[k] += c[i][k];
                        }
                    }
                }
            }
        }
        if (!made_one) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock) {
        printf("Deadlock detected. Deadlocked processes:\n");
        for (int i = 0; i < c_rows; i++) {
            if (!finished_arr[i]) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");
    }

}

int is_digit(char ch) {
    return ch >= 48 && ch <= 57;
}

int char_to_int(char ch) {
    return ch - 48;
}