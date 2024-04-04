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

void goto_tbl_print_to_file(goto_tbl_T *tbl, char *dest) {
    int i, j;
    FILE *fp = fopen(dest, "w");

    for(i = 0; i < tbl->n_states; ++i) {
        for(j = 0; j < tbl->n_non_terminals; ++j) {
            fprintf(fp, "%3d ", tbl->gotos[i][j]);
        } 
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void goto_tbl_pretty_print_to_file(goto_tbl_T *tbl, char *dest) {
    int i, j;
    FILE *fp = fopen(dest, "w");

    // print header
    fprintf(fp, "   |");
    for(i = 0; i < tbl->n_non_terminals; ++i) {
        fprintf(fp, "%20s ", tbl->non_terminals[i]->value);
    }
    fprintf(fp, "\n");

    fprintf(fp, "   |");
    for(i = 0; i < tbl->n_non_terminals; ++i) {
        fprintf(fp, "______________________");
    }
    fprintf(fp, "\n");

    for(i = 0; i < tbl->n_states; ++i) {
        fprintf(fp, " %2d|", i);
        for(j = 0; j < tbl->n_non_terminals; ++j) {
            fprintf(fp, "%20d ", tbl->gotos[i][j]);
        } 
        fprintf(fp, "\n");
    }

    fclose(fp);
}