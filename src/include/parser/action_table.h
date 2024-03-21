#ifndef QUEST_ACTION_TABLE_H
#define QUEST_ACTION_TABLE_H

#include "non_terminal.h"
#include "../lexer/token.h"
#include <stddef.h>

typedef struct ACTION_TABLE_STRUCT {
    char ***actions;        // a matrix of string describing the actions the parser should do 
    token_T **terminals;    // an array of terminals, a terminals index is its index in the action table
    size_t n_terminals;     // number of terminals 
    size_t n_states;        // number of states in the action table
} action_tbl_T;          

action_tbl_T *init_action_tbl(token_T **terminals, size_t n_terminals, size_t n_states);

int action_tbl_find_terminal(action_tbl_T *tbl, token_T *term);
void action_tbl_print_to_file(action_tbl_T *tbl, char *dest);

#endif