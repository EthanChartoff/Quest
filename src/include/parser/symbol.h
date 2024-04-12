#ifndef QUEST_SYMBOLS
#define QUEST_SYMBOLS

#include "../lexer/token.h"
#include "non_terminal.h"


typedef enum SYMBOL_TYPES_ENUM {
    TERMINAL,
    NON_TERMINAL
} symbol_type_E;

typedef union SYMBOL_UNION {
    token_T *terminal;
    non_terminal_T *non_terminal;
} symbol_U;

typedef struct SYMBOL_STRUCT {
    symbol_type_E sym_type;
    symbol_U *symbol;
} symbol_T;

symbol_T *init_symbol(symbol_U *symbol, symbol_type_E type);
symbol_T *init_symbol_terminal(token_T *tok);
symbol_T *init_symbol_non_terminal(non_terminal_T *nt);

int symbol_equals(const symbol_T *sym1, const symbol_T *sym2);
int symbol_cmp(const symbol_T *sym1, const symbol_T *sym2);
int symbol_cmp_generic(const void *sym1, const void *sym2);


#endif