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