#include "../include/parser/non_terminal.h"
#include <stdlib.h>

non_terminal_T *init_non_terminal(char *value, non_terminal_E type) {
    non_terminal_T *nt = malloc(sizeof(non_terminal_T));

    nt->type = type;
    nt->value = value;
    return nt;
}