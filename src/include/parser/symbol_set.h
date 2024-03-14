#ifndef QUEST_SYMBOL_SET
#define QUEST_SYMBOL_SET

#include "symbol.h"
#include <stddef.h>

// TODO: make a generic set, a hashset maybe

typedef struct SYMBOL_SET_STRUCT {
    symbol_T **set;
    size_t size;
} symbol_set_T;

symbol_set_T *init_symbol_set();
symbol_set_T *init_symbol_set_with_symbols(symbol_T **syms, const size_t size);
int add_symbol(symbol_set_T *set, symbol_T *item);
int remove_symbol(symbol_set_T *set, symbol_T *item);

#endif