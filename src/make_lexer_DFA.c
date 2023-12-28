#define NUM_CHAR 128
#include <stdio.h>
#include <stdlib.h>


const char *filename = "lexer_DFA.txt";
const FILE *fp = fopen(filename, "w");

short **DFA;

// add a token to the lexer's DFA
static add_tok_to_DFA(char *tok) {
    static int rows = 1;
    int i;

    for(i = 0; tok[i] != '\0', ++i) {
        
    }
}

// initialize the lexer's Deterministic Finite Automata. 
int init_dfa() {
    int i, j;

    // handle file not opening 
    if(fp == NULL) {
        printf("Error in opening file %s", filename);
        return -1;
    }

    // init DFA with one row
    DFA = (short**)malloc(sizeof(short*));
    if(DFA == NULL) {
        printf("Error allocating memory for the DFA");
        return 1;
    }
    DFA[0] = short(short*)malloc(NUM_CHAR*sizeof(short));
    for(i = 0; i < NUM_CHAR; ++i) 
        DFA[0][i] = -1;

    // write the DFA into the file
    #include "../tokens.h"
    #define TOK(name, str, val, is_kw) add_tok_to_DFA(char *str),
    #undef TOK
}

int main() {
    return 0;
}