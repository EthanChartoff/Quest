#include "../include/parser/grammer.h"
#include <stdlib.h>


grammer_T *init_grammer(rule_T **rules, size_t rules_size, symbol_T **symbols, size_t symbols_size) {
    grammer_T *gram = malloc(sizeof(grammer_T));

    gram->rules = rules;
    gram->rules_size = rules_size;
    gram->symbols = symbols;
    gram->symbols_size = symbols_size;

    return gram;
}