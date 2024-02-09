#include "lexer_DFA.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// modify lexeme because its first and last chars are ""
// TODO: fix, this is not a good method for doing this. doesnt need to exist because lexeme is a string. 
// TODO: add a file that indicates the end state for each token.
static char* remove_first_last_char(char *str) {
    char* cpy = malloc(strlen(str));
    if(cpy == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    strcpy(cpy, str);
    cpy[strlen(cpy)-1] = '\0';
    cpy++;
    return cpy;
}

static void init_special_states(lexer_dfa_T *dfa) {
    int i;
    
    // check flags for adding states
    if(dfa->flags & ADD_IDENTIFIER_STATE_FLAG) {
        // inc flag states
        dfa->n_flag_states++;
        
        // add id state
        dfa->states = (lexer_dfa_state_T**)realloc(dfa->states, ++dfa->n_states * sizeof(lexer_dfa_state_T*));
        if(dfa->states == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }

        dfa->states[dfa->n_states - 1] = (lexer_dfa_state_T*)malloc(sizeof(lexer_dfa_state_T));
        
        dfa->states[dfa->n_states - 1]->index = dfa->n_states - 1;
        dfa->states[dfa->n_states - 1]->type = IDENTIFIER;

        // add row to dfa
        dfa->DFA = (short**)realloc(dfa->DFA, dfa->n_states * sizeof(short*));
        if(dfa->DFA == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }

        dfa->DFA[(dfa->n_states) - 1] = (short*)malloc(ASCII_SIZE * sizeof(short));
        if(dfa->DFA[(dfa->n_states) - 1] == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }
        
        // add transition for special state and first state
        for(i = 0; i < ASCII_SIZE; ++i) {
            if(IS_CHAR_ID(i)) {
                dfa->DFA[dfa->n_states - 1][i] = dfa->n_states - 1;
                dfa->DFA[0][i] = dfa->n_states - 1;
            } else {
                dfa->DFA[dfa->n_states - 1][i] = -1;
            }
        }
    }
    
    if(dfa->flags & ADD_NUMBER_STATE_FLAG) {
        // inc flag states
        dfa->n_flag_states++;

        // add num state
        dfa->states = (lexer_dfa_state_T**)realloc(dfa->states, ++dfa->n_states * sizeof(lexer_dfa_state_T*));
        if(dfa->states == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }

        dfa->states[dfa->n_states - 1] = (lexer_dfa_state_T*)malloc(sizeof(lexer_dfa_state_T));

        dfa->states[dfa->n_states - 1]->index = dfa->n_states - 1;
        dfa->states[dfa->n_states - 1]->type = NUMBER;

        // add row to dfa
        dfa->DFA = (short**)realloc(dfa->DFA, dfa->n_states * sizeof(short*));
        if(dfa->DFA == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }

        dfa->DFA[(dfa->n_states) - 1] = (short*)malloc(ASCII_SIZE * sizeof(short));
        if(dfa->DFA[(dfa->n_states) - 1] == NULL) {
            perror("Error allocating memory for the DFA");
            exit(EXIT_FAILURE);
        }

        // add transition for special state and first state
        for(i = 0; i < ASCII_SIZE; ++i) {
            if(IS_CHAR_NUM(i)) {
                dfa->DFA[dfa->n_states - 1][i] = dfa->n_states - 1;
                dfa->DFA[0][i] = dfa->n_states - 1;
            } else {
                dfa->DFA[dfa->n_states - 1][i] = -1;
            }
        }
    }
}

static int add_state_to_DFA(lexer_dfa_T *dfa) {
    int i, j;
    static int id_state = -1, num_state = -1;

    // add row 
    dfa->DFA = (short**)realloc(dfa->DFA, ++dfa->n_states * sizeof(short*));
    if(dfa->DFA == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }
    dfa->DFA[(dfa->n_states) - 1] = (short*)malloc(ASCII_SIZE * sizeof(short));
    
    if(dfa->DFA[(dfa->n_states) - 1] == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < ASCII_SIZE; ++i) {
        // TODO: maybe make this a func?
        // if id flag is on add a transition function for identification states
        if(IS_CHAR_ID(i) && (dfa->flags & ADD_IDENTIFIER_STATE_FLAG)) {
            // if id_state is not initilized to its correct state, change it.
            // this causes an error if there's more then 1 ID state, so the program checks for ID state -
            // and if theres more then 1, the DFA is not valid and will be terminated.
            if(id_state == -1) {
                for(j = 0; j < dfa->n_states; ++j) {
                    if(dfa->states[j]->type == IDENTIFIER) {
                        id_state = j;
                        break;
                    }
                }
            }
            dfa->DFA[dfa->n_states - 1][i] = id_state;   
        } 
        // if number flag is on add a transition function for number states
        else if (IS_CHAR_NUM(i) && (dfa->flags & ADD_NUMBER_STATE_FLAG)) {
            // same case as id_state
            if(num_state == -1) {
                for(j = 0; j < dfa->n_states; ++j) {
                    if(dfa->states[j]->type == NUMBER) {
                        num_state = j;
                        break;
                    }
                }
            }
            dfa->DFA[dfa->n_states - 1][i] = num_state;
        } else {
            dfa->DFA[dfa->n_states - 1][i] = -1;
        }
    }

    // state settings
    dfa->states[dfa->n_states - 1]->type = DENY;
    dfa->states[dfa->n_states - 1]->index = dfa->n_states - 1; 
        
    return 0;
}

// add a token to the lexer's DFA
static int add_tok_to_DFA(lexer_dfa_T *dfa, token_T *tok) {
    unsigned int i, curr_state = 0;

    for(i = 0; tok->value[i] != '\0'; ++i) {
        // check if char at state has a response
        if(
            dfa->DFA[curr_state][tok->value[i]] == -1
            || (dfa->DFA[curr_state][tok->value[i]] > 0 && dfa->DFA[curr_state][tok->value[i]] < dfa->n_flag_states) 
        ) {
            add_state_to_DFA(dfa);
            printf("%c - %d\n", tok->value[i], curr_state);
            dfa->DFA[curr_state][tok->value[i]] = dfa->n_states - 1;
        }

        curr_state = dfa->DFA[curr_state][tok->value[i]];
    }

    // state settings
    dfa->states[curr_state]->type = ACCEPT;
    strcpy(dfa->states[curr_state]->lexeme, tok->value);
    
    return 0;
}

// initialize the lexer's Deterministic Finite Automata 
// according to a set of tokens that set the rules. 
int init_dfa(token_T **toks, const size_t n_toks, const char *filename, unsigned short flags) {
    lexer_dfa_T *dfa = malloc(sizeof(lexer_dfa_T));
    FILE *fp = fopen(filename, "w");
    int i, j;

    // handle file not opening 
    if(fp == NULL) {
        perror("Error in opening DFA file");
        exit(EXIT_FAILURE);
    }

    // -- init dfa variables --

    // init DFA with one row
    dfa->DFA = (short**)malloc(sizeof(short*));
    if(dfa->DFA == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    dfa->DFA[0] = (short*)malloc(ASCII_SIZE * sizeof(short));
    if(dfa->DFA[0] == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < ASCII_SIZE; ++i) 
        dfa->DFA[0][i] = -1;
    
    // init tokens
    dfa->n_toks = n_toks;
    dfa->toks = (token_T**)malloc(dfa->n_toks * sizeof(token_T*));
    if(dfa->toks == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    // init states
    dfa->n_states = 1;
    dfa->states = (lexer_dfa_state_T**)malloc(dfa->n_states * sizeof(lexer_dfa_state_T*));

    if(dfa->states == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    dfa->states[0] = (lexer_dfa_state_T*)malloc(sizeof(lexer_dfa_state_T));

    dfa->states[0]->index = 0;
    dfa->states[0]->type = DENY; // TODO: should this be ACCEPT?

    // init filename
    dfa->filename = (char*)malloc(sizeof(char) * (strlen(filename) + 1));

    // init flags
    dfa->flags = flags;
    dfa->n_flag_states = 0;

    // init special states of dfa
    init_special_states(dfa);

    // add all of the tokens to the DFA
    for(i = 0; i < dfa->n_toks; ++i)
        add_tok_to_DFA(dfa, toks[i]);

    // print DFA into file to save it and print state lexme/ 
    for(i = 0; i < dfa->n_states; ++i) {
        if(dfa->states[i]->type == ACCEPT)  
            fprintf(fp, "%d ", dfa->DFA[i][j]);
        

        for(j = 0; j < ASCII_SIZE; ++j) {
            fprintf(fp, "%d ", dfa->DFA[i][j]);
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

    #define TOK(name, lexeme, val, is_kw) toks[i++] = init_token(remove_first_last_char(#lexeme), TOK_##name);
    #include "../include/tokens.h"
    #undef TOK

    init_dfa(toks, 
            NUM_TOK, 
            "src/config/lexer_dfa.txt", 
            ADD_IDENTIFIER_STATE_FLAG + ADD_NUMBER_STATE_FLAG);

    for(i = 0; i < NUM_TOK; ++i)
        free(toks[i]);
    
    return EXIT_SUCCESS;
}