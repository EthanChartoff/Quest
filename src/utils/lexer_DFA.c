#define NUM_CHAR 128
#include "lexer_DFA.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>

short **DFA;
int rows = 1;

static int add_state_to_DFA() {
    int i;

    DFA = (short**)realloc(DFA, ++rows * sizeof(short*));
    if(DFA == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    DFA[(rows) - 1] = (short*)malloc(NUM_CHAR*sizeof(short));
    if(DFA[(rows) - 1] == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < NUM_CHAR; ++i) 
        DFA[rows - 1][i] = -1;

    return 0;
}

// add a token to the lexer's DFA
static int add_tok_to_DFA(const token_T* tok) {
    unsigned int i, state = 0;

    for(i = 0; tok->value[i] != '\0'; ++i) {
        if(tok->value[i] == '"')
            continue;
        // check if char at state has a response
        if(DFA[state][tok->value[i]] == -1) {
            add_state_to_DFA();
            DFA[state][tok->value[i]] = rows - 1;
        }
        state = DFA[state][tok->value[i]];
    }
    
    return 0;
}

// initialize the lexer's Deterministic Finite Automata 
// according to a set of tokens that set the rules. 
int init_dfa(token_T **toks, const size_t n_toks, const char *filename) {
    FILE *fp = fopen(filename, "w");
    int i, j;

    // handle file not opening 
    if(fp == NULL) {
        perror("Error in opening DFA file");
        exit(EXIT_FAILURE);
    }

    // init DFA with one row
    DFA = (short**)malloc(sizeof(short*));
    if(DFA == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }
    DFA[rows - 1] = (short*)malloc(NUM_CHAR*sizeof(short));
    for(i = 0; i < NUM_CHAR; ++i) 
        DFA[rows - 1][i] = -1;
    
    // add all of the tokens to the DFA
    for(i = 0; i < n_toks; ++i)
        add_tok_to_DFA(toks[i]);

    // print DFA into file to save it 
    for(i = 0; i < rows; ++i) {
        for(j = 0; j < NUM_CHAR; ++j) {
            fprintf(fp, "%d ", DFA[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
}

// default configuration for the DFA 
int init_default_dfa() {
    token_T *toks[NUM_TOK];
    int i = 0;
    #define TOK(name, lexeme, val, is_kw) toks[i++] = init_token(#str, TOK_##name);
    #include "../include/tokens.h"
    #undef TOK

    init_dfa(toks, NUM_TOK, "src/config/lexer_dfa.txt");
}