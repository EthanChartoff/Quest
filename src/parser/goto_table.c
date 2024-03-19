#include "../include/parser/goto_table.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

goto_tbl_T *init_goto_tbl(non_terminal_T **non_terminals, size_t n_non_terminals, size_t n_states) {
    int i;
    goto_tbl_T *gotot = malloc(sizeof(goto_tbl_T));
    if(!gotot)
        thrw(ALLOC_ERR);

    gotot->gotos = malloc(sizeof(int *) * n_states);
    if(!gotot->gotos)
        thrw(ALLOC_ERR);

    for(i = 0; i < n_states; ++i) {
        gotot->gotos[i] = malloc(sizeof(int) * n_non_terminals);
        if(!gotot->gotos[i])
            thrw(ALLOC_ERR);
    }
    gotot->non_terminals = non_terminals;
    gotot->n_non_terminals = n_non_terminals;
    gotot->n_states = n_states; 

    return gotot;
}

size_t goto_tbl_find_non_terminal(goto_tbl_T *tbl, non_terminal_T *nterm) {
    int i;

    for(i = 0; i < tbl->n_non_terminals; ++i) {
        if(tbl->non_terminals[i]->type == nterm->type) {
            return i;
        }
    }
    return -1;
}