#ifndef QUEST_GOTO_TABLE_H
#define QUEST_GOTO_TABLE_H

#include "non_terminal.h"
#include <stddef.h>

typedef struct GOTO_TABLE_STRUCT {
    int **gotos;                    // a matrix of integers describing the goto the parser should do 
    non_terminal_T **non_terminals; // an array of terminals, a terminals index is its index in the action table
    size_t n_non_terminals;         // number of terminals 
    size_t n_states;                // number of states in the goto table
} goto_tbl_T;          

goto_tbl_T *init_goto_tbl(non_terminal_T **non_terminals, size_t n_non_terminals, size_t n_states);
size_t find_non_terminal(goto_tbl_T *tbl, non_terminal_T *nterm);


#endif