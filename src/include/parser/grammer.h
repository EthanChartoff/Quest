#ifndef QUEST_GRAMMER_H
#define QUEST_GRAMMER_H

#include "non_terminal.h"
#include "rule.h"
#include "symbol.h"
#include "../lexer/token.h"
#include "../../utils/DS/include/generic_set.h"
#include <stddef.h>

typedef struct GRAMMER_STRUCT {
    set_T *rules;
    set_T *symbols;
} grammer_T;

grammer_T *init_grammer(set_T *rules, set_T *symbols);

token_T **terminals_in_symbol_set(set_T *symbols);
token_T **terminals_in_symbol_set_and_dollar(set_T *symbols);
size_t n_terminals_in_symbol_set(set_T *symbols);
non_terminal_T **non_terminals_in_symbol_set(set_T *symbols);
size_t n_non_terminals_in_symbol_set(set_T *symbols);

size_t find_right_grammer_index(const grammer_T *gram, symbol_T **right, size_t right_size);

#endif