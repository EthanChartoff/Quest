#include "include/lexer_automata.h"
#include <stdio.h>
#include <stdlib.h>


static void init_automata_state_type(lexer_automata_T *automata, const char *states_src) {
    FILE *fp = fopen(states_src, "r");
    size_t i, state_index;

    // handle file not opening
    if(fp == NULL) {
        perror("Error opening states file");
        exit(EXIT_FAILURE);
    }

    // TODO: need to handle file not opening
    automata->state_type = (lexer_dfa_state_type_T *)malloc(automata->n_state * sizeof(lexer_dfa_state_type_T));
    for(i = 0; i < automata->n_state; ++i) {
        fscanf(fp, "%zd ", &state_index);
        fscanf(fp, "%d", &automata->state_type[state_index]); 
    }

    return;
}

static void init_automata_mat(lexer_automata_T *automata, const char *auto_src) {
    FILE *fp = fopen(auto_src, "r");
    size_t rows, cols, i, j;

    // handle file not opening
    if(fp == NULL) {
        perror("Error opening automata file");
        exit(EXIT_FAILURE);
    }

    // get rows and columns of the dfa's 2d arr
    fscanf(fp, "%zd", &rows);
    fscanf(fp, "%zd", &cols);

    // init auto self
    automata->n_state = rows;
    automata->automata = (short **)malloc(automata->n_state * sizeof(short *));

    // handle malloc not working properly
    if(automata->automata == NULL) {
        perror("Error mallocing");
        exit(EXIT_FAILURE);
    }

    // malloc rows of automata mat
    for(i = 0; i < automata->n_state; ++i) {
        automata->automata[i] = (short *)malloc(cols * sizeof(short));
    }

    for(i = 0; i < automata->n_state; ++i) {
        for(j = 0; j < cols; ++j) {
            // if theres an error reading from the file, exit
            if(fscanf(fp, "%hd", &automata->automata[i][j]) != 1) {
                perror("Error reading from file");
                fclose(fp);

                for(i = 0; i < automata->n_state; ++i)
                    free(automata->automata[i]);
                free(automata->automata);

                exit(1);
                return;
            }   
        }
    }

    return;
}

lexer_automata_T* init_lexer_automata(const char *auto_src, const char *states_src) {
    lexer_automata_T *automata = malloc(sizeof(lexer_automata_T));
    
    init_automata_mat(automata, auto_src);
    init_automata_state_type(automata, states_src);

    return automata;
}
