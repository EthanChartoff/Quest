#include "../include/parser/grammer.h"
#include <stdlib.h>


grammer_T *init_grammer(set_T *rules, set_T *symbols) {
    grammer_T *gram = malloc(sizeof(grammer_T));

    gram->rules = rules;
    gram->symbols = symbols;

    return gram;
}