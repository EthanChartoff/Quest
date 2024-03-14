#include "../include/parser/symbol.h"
#include <stdlib.h>
#include <stdio.h>

symbol_T *init_symbol_tok(symbol_U *symbol, symbol_type_E type) {
    symbol_T *sym = malloc(sizeof(symbol_T));

    sym->symbol = symbol;
    sym->sym_type = type;

    return sym;
}

symbol_T *init_symbol_terminal(token_T *tok) {
    symbol_T *sym = malloc(sizeof(symbol_T));

    sym->symbol = malloc(sizeof(symbol_U));
    sym->symbol->terminal = tok;
    sym->sym_type = TERMINAL;

    return sym;
}

symbol_T *init_symbol_non_terminal(non_terminal_T *nt) {
    symbol_T *sym = malloc(sizeof(symbol_T));
    
    sym->symbol = malloc(sizeof(symbol_U));
    sym->symbol->non_terminal = nt;
    sym->sym_type = NON_TERMINAL;

    return sym;
}

int symbol_equals(const symbol_T *sym1, const symbol_T *sym2) {

    return sym1->sym_type == sym2->sym_type 
        ? sym1->sym_type == TERMINAL 
            ? sym1->symbol->terminal->type == sym2->symbol->terminal->type
            : sym1->symbol->non_terminal->type == sym2->symbol->non_terminal->type
        : 0;
}
