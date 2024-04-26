#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// reads the contents of a file
char* read_file(const char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char* buffer;

    fp = fopen(filename, "rb");
    if(fp == NULL) {
        printf("Couldn't read file %s\n", filename);
        exit(1);
    }

    buffer = malloc(sizeof(char));
    buffer[0] = '\0';

    while((read = getline(&line, &len, fp) != -1)) {
        buffer = realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if(line)
        free(line);

    return buffer;
}

// writes to a file
void write_file(const char *filename, const char *content) {
    FILE *fp;
    fp = fopen(filename, "w");
    if(fp == NULL) {
        perror("Couldn't write to file");
        exit(1);
    }

    if(fputs(content, fp) == EOF) {
        perror("Error writing to file");
        exit(1);
    }
    fclose(fp);
}

// append to a file
void write_file_append(const char *filename, char *content) {
    FILE *fp;
    fp = fopen(filename, "a");
    if(fp == NULL) {
        printf("Couldn't write to file %s\n", filename);
        exit(1);
    }
    fprintf(fp, "%s", content);
    fclose(fp);
}

// prints to stdout
void print_to_stdout(char *content) {
    printf("%s", content);
}

// prints to stderr
void print_to_stderr(char *content) {
    fprintf(stderr, "%s", content);
}

// get filename and a new name, create new file to be in the same folder as filename and the name of the file is provided, unless the name is NULL then its .out
char *get_new_filename(const char *filename, const char *new_name) {
    char *new_filename;
    size_t len = strlen(filename);
    const char *last_slash = strrchr(filename, '/');

    if(last_slash)
        len = last_slash - filename + 1;

    new_filename = malloc(len + (new_name ? strlen(new_name) : 5) + 1); // +1 for null terminator

    strncpy(new_filename, filename, len);
    new_filename[len] = '\0';

    if(new_name)
        strcat(new_filename, new_name);
    else
        strcat(new_filename, ".out");

    return new_filename;
}

