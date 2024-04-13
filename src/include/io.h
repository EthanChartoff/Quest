#ifndef QUEST_IO_H
#define QUEST_IO_H

char* read_file(const char *filename);
void write_file(const char *filename, char *content);
void write_file_append(const char *filename, char *content);
void print_to_stdout(char *content);
void print_to_stderr(char *content);
char *get_new_filename(const char *filename, const char *new_name);


#endif