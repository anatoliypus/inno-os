#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILES_TO_READ 32
#define MAX_PATH_LEN 1024
#define TEMP_DIR "./tmp/"
#define OUTPUT_FILE_NAME "ex4.txt"

int main() {
    DIR * dirp = opendir(TEMP_DIR);
    if (dirp == NULL) { 
        exit(EXIT_FAILURE);
    } 

    struct dirent * dp[MAX_FILES_TO_READ];;
    struct stat * s = malloc(sizeof(struct stat) * MAX_FILES_TO_READ);
    int counter = 0;

    while ((dp[counter] = readdir(dirp)) != NULL) {
        if (!(strcmp(dp[counter]->d_name, ".") == 0) && !(strcmp(dp[counter]->d_name, "..") == 0)) {
            char path[MAX_PATH_LEN] = TEMP_DIR;
            strcat(path, dp[counter]->d_name);
            if (stat(path, s + counter) != 0) {
                exit(EXIT_FAILURE);
            }
            counter++;
        }
    }

    FILE * fp = fopen(OUTPUT_FILE_NAME, "w");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "File - Hard Links\n");
    for (int i = 0; i < counter; i++) {
        if (s[i].st_nlink > 1) {
            fprintf(fp, "%s - ", dp[i]->d_name);
            int first = 1;
            for (int j = 0; j < counter; j++) {
                if (s[i].st_ino == s[j].st_ino) {
                    if (first) {
                        first = 0;
                    } else {
                        fprintf(fp, ", ");
                    }
                    fprintf(fp, "%s", dp[j]->d_name);
                }
            }
            fprintf(fp, "\n");
        }
    }

    closedir(dirp);
    free(s);
    fclose(fp);
    exit(EXIT_SUCCESS);
}