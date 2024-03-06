#include "../include/parser/grammer.h"
#include <stdlib.h>


grammer_T *init_grammer(rule_T **rules, size_t size) {
    grammer_T *gram = malloc(sizeof(grammer_T));

    gram->rules = rules;
    gram->size = size;

    return gram;
}