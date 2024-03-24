#include "../include/parser/action_table.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

action_tbl_T *init_action_tbl(token_T **terminals, size_t n_terminals, size_t n_states) {
    int i;
    action_tbl_T *action = malloc(sizeof(action_tbl_T));
    if(!action)
        thrw(ALLOC_ERR);

    action->actions = malloc(sizeof(char **) * n_states);
    if(!action->actions)
        thrw(ALLOC_ERR);
    for(i = 0; i < n_states; ++i) {
        action->actions[i] = malloc(sizeof(char *) * n_terminals);
        if(!action->actions[i])
            thrw(ALLOC_ERR);
    }
    action->terminals = terminals;
    action->n_terminals = n_terminals;
    action->n_states = n_states;

    return action;
}

int action_tbl_find_terminal(action_tbl_T *tbl, token_T *term) {
    int i;

    for(i = 0; i < tbl->n_terminals; ++i) {
        if(tbl->terminals[i]->type == term->type)
            return i;
    }
    return -1;
}

void action_tbl_print_to_file(action_tbl_T *tbl, char *dest) {
    int i, j;
    FILE *fp = fopen(dest, "w");

    for(i = 0; i < tbl->n_states; ++i) {
        for(j = 0; j < tbl->n_terminals; ++j) {
            if(!tbl->actions[i][j])
                fprintf(fp, "    ");
            else
                fprintf(fp, "%3s ", tbl->actions[i][j]);
        } 
        fprintf(fp, "\n", tbl->actions[i][j]);
    }

    fclose(fp);
}

void action_tbl_pretty_print_to_file(action_tbl_T *tbl, char *dest) {
    int i, j;
    FILE *fp = fopen(dest, "w");

    // print header
    fprintf(fp, "   |");
    for(i = 0; i < tbl->n_terminals; ++i) {
        fprintf(fp, "%3s ", tbl->terminals[i]->value);
    }
    fprintf(fp, "\n");

    fprintf(fp, "   |");
    for(i = 0; i < tbl->n_terminals; ++i) {
        fprintf(fp, "____");
    }
    fprintf(fp, "\n");


    for(i = 0; i < tbl->n_states; ++i) {
        fprintf(fp, " %2d|", i);
        for(j = 0; j < tbl->n_terminals; ++j) {
            if(!tbl->actions[i][j])
                fprintf(fp, "    ");
            else
                fprintf(fp, "%3s ", tbl->actions[i][j]);
        } 
        fprintf(fp, "\n");
    }

    fclose(fp);
}