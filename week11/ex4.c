#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILES_TO_READ 32
#define MAX_PATH_LEN 1024
#define TEMP_DIR "./tmp/"

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

    printf("File - Hard Links\n");
    for (int i = 0; i < counter; i++) {
        if (s[i].st_nlink > 1) {
            printf("%s - ", dp[i]->d_name);
            int first = 1;
            for (int j = 0; j < counter; j++) {
                if (s[i].st_ino == s[j].st_ino) {
                    if (first) {
                        first = 0;
                    } else {
                        printf(", ");
                    }
                    printf("%s", dp[j]->d_name);
                }
            }
            printf("\n");
        }
    }

    closedir(dirp);
    free(s);
    exit(EXIT_SUCCESS);
}