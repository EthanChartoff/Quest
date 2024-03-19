#include "../include/parser/non_terminal.h"
#include "../include/macros.h"
#include <stdlib.h>
#include <string.h>

non_terminal_T *init_non_terminal(char *value, non_terminal_E type) {
    non_terminal_T *nt = malloc(sizeof(non_terminal_T));

    nt->type = type;
    nt->value = value;
    return nt;
}

int non_terminal_cmp(const non_terminal_T *nt1, const non_terminal_T *nt2) {
    int delta;

    delta = nt1->type - nt2->type;
    IF_SIGN(delta);

    delta = strcmp(nt1->value, nt2->value);
    IF_SIGN(delta);

    return 0;
}