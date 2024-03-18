#include "../include/parser/action_table.h"
#include "../utils/err/err.h"
#include <stdlib.h>

action_tbl_T *init_action_tbl(token_T **terminals, size_t n_terminals, size_t n_states) {
    int i;
    action_tbl_T *action = malloc(sizeof(action_tbl_T));
    if(!action)
        thrw(ALLOC_ERR);

    action->actions = malloc(sizeof(char **) * n_terminals);
    if(!action->actions)
        thrw(ALLOC_ERR);
    for(i = 0; i < n_terminals; ++i) {
        action->actions[i] = malloc(sizeof(char *) * n_states);
        if(!action->actions[i])
            thrw(ALLOC_ERR);
    }
    action->terminals = terminals;
    action->n_terminals = n_terminals;
    action->n_states = n_states;

    return action;
}

size_t action_tbl_find_terminal(action_tbl_T *tbl, token_T *term) {
    int i;

    for(i = 0; i < tbl->n_terminals; ++i) {
        if(!token_cmp(tbl->terminals[i], term))
            return i;
    }
    return -1;
}