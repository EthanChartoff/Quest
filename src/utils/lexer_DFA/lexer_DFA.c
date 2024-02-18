#include "include/lexer_DFA.h"
#include "include/transitions.h"
#include "../../include/tokens.h"
#include "../../include/macros.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// modify lexeme because its first and last chars are ""
// TODO: fix, this is not a good method for doing this. doesnt need to exist because lexeme is a string. 
// TODO: make a free function for the structcha
static char * remove_first_last_char(char *str) {
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

// I would use a switch but you cant use break... 
static char * state_type_to_string(int type) {
    return type == DENY ? "DENY" :
    type == CHAR_DENY ? "CHAR_DENY" :
    type == STRING_DENY ? "STRING_DENY" :
    type == ACCEPT ? "ACCEPT" :
    type == IDENTIFIER ? "IDENTIFIER" :
    type == NUMBER ? "NUMBER" :
    type == CHAR ? "CHAR" : 
    type == STRING ? "STRING" :
    type == LEXER_DFA_STATE_TYPE_SIZE ? "LEXER_DFA_STATE_TYPE_SIZE" :
    "invalid type"; 
}

// add a state to the dfa
// if dest_state is NULL, dest_state will be equal to the source
// return state
static lexer_dfa_state_T * add_state_to_DFA(lexer_dfa_T *dfa, int type, char *lexeme, void (*add_transition)(lexer_dfa_T *, lexer_dfa_state_T *, int, int), int dest_state) {
    int i, j;

    // add state
    dfa->states = (lexer_dfa_state_T**)realloc(dfa->states, ++dfa->n_states * sizeof(lexer_dfa_state_T*));
    if(dfa->states == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }

    dfa->states[dfa->n_states - 1] = (lexer_dfa_state_T *)malloc(sizeof(lexer_dfa_state_T));
    dfa->states[dfa->n_states - 1]->index = dfa->n_states - 1;
    dfa->states[dfa->n_states - 1]->lexeme = lexeme;
    dfa->states[dfa->n_states - 1]->type = type;


    // change last state type to this state unless state is spacial state

    if((type == DENY) || (type == ACCEPT) || dfa->last_states[type] == NULL) {
        dfa->last_states[type] = dfa->states[dfa->n_states - 1];
    }
    
    // add row 
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

    // if dest_state is 0, dest_state will be equal to the source
    if(dest_state == 0) {
        dest_state = dfa->states[dfa->n_states - 1]->index;
    }
    for(i = 0; i < ASCII_SIZE; ++i) {
        (*add_transition)(dfa, dfa->states[dfa->n_states - 1], dest_state, i);
    }

    return dfa->states[dfa->n_states - 1];
}

// add a token to the lexer's DFA
static int add_tok_to_DFA(lexer_dfa_T *dfa, token_T *tok) {
    unsigned int i, curr_state = 0, str_tok_len = strlen(tok->value), state_type = dfa->flags & ADD_IDENTIFIER_STATE_FLAG ? IDENTIFIER : DENY;
    char *lexeme = malloc(sizeof(char)), *tmp_lex;

    // check if tok has lexeme
    if(str_tok_len == 0)
        return 0;    

    for(i = 0; i < str_tok_len; ++i) {
        // add to state lexeme
        lexeme = (char *)realloc(lexeme, (i + 2) * sizeof(char));
        lexeme[i + 1] = '\0';
        lexeme[i] = tok->value[i];
        

        // check if state type is valid to be an identifier
        if(!(is_id(tok->value[i])) && state_type == IDENTIFIER)
            state_type = DENY;

        // check if char at state has a response
        if(
            dfa->DFA[curr_state][tok->value[i]] == -1
            || (dfa->DFA[curr_state][tok->value[i]] > 0 && dfa->DFA[curr_state][tok->value[i]] < dfa->n_flag_states) 
        ) {
            add_state_to_DFA(dfa, state_type, strdup(lexeme), add_transition, 0);
            dfa->DFA[curr_state][tok->value[i]] = dfa->n_states - 1;
        }
        curr_state = dfa->DFA[curr_state][tok->value[i]];
    }
    

    // state settings
    dfa->states[curr_state]->type = ACCEPT;

    dfa->states[curr_state]->lexeme = (char *) malloc(str_tok_len * sizeof(char));
    strcpy(dfa->states[curr_state]->lexeme, tok->value);
    
    return 0;
}

static void init_special_states(lexer_dfa_T *dfa) {
    if(dfa->flags & ADD_IDENTIFIER_STATE_FLAG) {
        dfa->n_flag_states++;
        add_state_to_DFA(dfa, IDENTIFIER, "(IDENTIFIER)", add_id_transition, 0);
    }
    if(dfa->flags & ADD_NUMBER_STATE_FLAG) {
        dfa->n_flag_states++;
        add_state_to_DFA(dfa, NUMBER, "(NUMBER)", add_num_transition, 0);
    }
    if(dfa->flags & ADD_CHAR_STATES_FLAG) {
        dfa->n_flag_states += 2;
        add_state_to_DFA(dfa, CHAR_DENY, "(CHAR_DENY)", add_first_char_transition, add_state_to_DFA(dfa, CHAR, "(CHAR)", add_second_char_transition, 0)->index);
    }
    if(dfa->flags & ADD_STRING_STATES_FLAG) {
        dfa->n_flag_states += 2;
        add_state_to_DFA(dfa, STRING_DENY, "(STRING_DENY)", add_first_string_transition, add_state_to_DFA(dfa, STRING, "(STRING)", add_second_string_transition, 0)->index);
    }

}

// initialize the lexer's Deterministic Finite Automata 
// according to a set of tokens that set the rules. 
int init_dfa(token_T **toks, const size_t n_toks, const char *DFA_filename, char *DFA_states_filename, unsigned short flags) {
    lexer_dfa_T *dfa = malloc(sizeof(lexer_dfa_T));
    FILE *DFA_fp = fopen(DFA_filename, "w"), *DFA_states_fp = fopen(DFA_states_filename, "w");
    int i, j;

    // handle file not opening 
    if(DFA_fp == NULL || DFA_states_fp == NULL) {
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
    dfa->states[0]->type = DENY; 

    dfa->last_states = (lexer_dfa_state_T**)malloc(LEXER_DFA_STATE_TYPE_SIZE * sizeof(lexer_dfa_state_T*));
    if(dfa->last_states == NULL) {
        perror("Error allocating memory for the DFA");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < LEXER_DFA_STATE_TYPE_SIZE; ++i) {
        dfa->last_states[i] = (lexer_dfa_state_T*)malloc(sizeof(lexer_dfa_state_T));
        dfa->last_states[i] = NULL;
    }
    dfa->last_states[DENY] = dfa->states[0];

    // init filename
    dfa->filename = (char*)malloc(sizeof(char) * (strlen(DFA_filename) + 1));

    // init flags
    dfa->flags = flags;
    dfa->n_flag_states = 0;

    // init special states of dfa
    init_special_states(dfa);

    // add all of the tokens to the DFA
    for(i = 0; i < dfa->n_toks; ++i)
        add_tok_to_DFA(dfa, toks[i]);


    // print DFA into file to save it and print state lexme
    fprintf(DFA_fp, "%d\n%d\n", dfa->n_states, ASCII_SIZE);
    
    for(i = 0; i < dfa->n_states; ++i) {    
        // check invalid state type
        if(dfa->states[i]->type >= LEXER_DFA_STATE_TYPE_SIZE) {
            perror("Error defining states, invalid state type");
            exit(EXIT_FAILURE);
        }

        fprintf(DFA_states_fp, "%d %d\n",  
                dfa->states[i]->index,
                dfa->states[i]->type
        );
        
        for(j = 0; j < ASCII_SIZE; ++j) {
            fprintf(DFA_fp, "%d ", dfa->DFA[i][j]);
        }
        fprintf(DFA_fp, "\n");
    }
    fclose(DFA_fp);

    return 0;
}

// default configuration for the DFA 
int init_default_dfa() {
    token_T *toks[NUM_TOK];
    int i = 0;

    #define TOK(name, lexeme, val, is_kw) toks[i++] = init_token(remove_first_last_char(#lexeme), TOK_##name);
    #include TOKS_PATH
    #undef TOK

    init_dfa(toks, 
            NUM_TOK, 
            LEXER_DFA_PATH, 
            LEXER_DFA_STATES_PATH,
            ADD_IDENTIFIER_STATE_FLAG + ADD_NUMBER_STATE_FLAG + ADD_CHAR_STATES_FLAG + ADD_STRING_STATES_FLAG);

    for(i = 0; i < NUM_TOK; ++i)
        free(toks[i]);
    
    return EXIT_SUCCESS;
}