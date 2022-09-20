#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME_LENGTH 63
#define MAX_FILES_AMOUNT 256
#define MAX_SUB_DIRS_AMOUNT 8
#define MAX_PATH_LENGTH 2048
#define MAX_FILE_DATA_LENGTH 1024

typedef struct File {
    int id;
    char name[MAX_FILE_NAME_LENGTH];
    int size;
    char data[MAX_FILE_DATA_LENGTH];
} File;


typedef struct Directory Directory;
struct Directory {
    File files[MAX_FILES_AMOUNT];
    Directory * directories;
    int nf;
    int nd;
    char path[MAX_PATH_LENGTH];
};

// for File struct
void add_to_file(struct File* file, const char* str); // update file content
void append_to_file(struct File* file, const char* str); // append file content
void pwd_file(struct File* file); // prints the path of the file

// for Directory struct
void add_file(struct File* file, struct Directory* dir);
void add_directory(struct Directory* dir, struct Directory* subdir);

// "constructors"
Directory create_directory(char path[MAX_PATH_LENGTH]);
File create_file(char path[MAX_PATH_LENGTH]);

int main() {
    Directory root = create_directory("/");
    Directory bin = create_directory("/bin");
    Directory home = create_directory("/home");

    add_directory(&root, &bin);
    add_directory(&root, &home);

    File bash = create_file("bash");
    add_file(&bash, &bin);

    File f1 = create_file("ex3_1.c");
    File f2 = create_file("ex3_2.c");

    add_to_file(&f2, "/This is a comment in C language");
    add_to_file(&f1, "int printf(const char * format, ...);");

    add_file(&f1, &home);
    add_file(&f2, &home);

    add_to_file(&bash, "Bourne Again Shell!!");
    append_to_file(&f1, "int main(){printf(”Hello World!”)}");

    pwd_file(&bash);
    pwd_file(&f1);
    pwd_file(&f2);

    return 0;
}

void add_to_file(struct File* file, const char* str) {
    if (file == NULL || str == NULL || strlen(str) > MAX_FILE_DATA_LENGTH)
        return;
    strcpy(file->data, str);
}

void append_to_file(struct File* file, const char* str) {
    if (file == NULL ||
        str == NULL ||
        (strlen(str) + strlen(file->data)) > MAX_FILE_DATA_LENGTH)
        return;
    char * ch = file->data;
    for (; *ch != '\0'; ch++);
    strcpy(ch, str);
}

void pwd_file(struct File* file) {
    printf("The name of file: %s\n", file->name);
}

void add_file(struct File* file, struct Directory* dir) {
    dir->files[dir->nf] = *file;
    char fileName[MAX_PATH_LENGTH];
    strcpy(fileName, file->name);
    strcpy(file->name, dir->path);
    strcat(file->name, "/");
    strcat(file->name, fileName);
    (dir->nf)++;
}

void add_directory(struct Directory* dir, struct Directory* subdir) {
    dir->directories[dir->nd] = *subdir;
    (dir->nd)++;
}

Directory create_directory(char path[MAX_PATH_LENGTH]) {
    Directory d;
    d.nf = 0;
    d.nd = 0;
    strcpy(d.path, path);
    d.directories = malloc(sizeof(Directory) * MAX_SUB_DIRS_AMOUNT);
    return d;
}

File create_file(char name[MAX_PATH_LENGTH]) {
    static int id = 0;
    File f;
    strcpy(f.name, name);
    return f;
}
