//===--- The Quest Language: lexer_DFA.h ------------===
//
// The DFA header. defines the main DFA's struct, 
// the states struct and its type, and macros relating to the dfa. 
//
//
// WORK IN PROGRESS
//
//===------------------------------------------------===

#ifndef QUEST_LEXER_DFA_H
#define QUEST_LEXER_DFA_H

#include "../../../include/token.h"
#include <stddef.h>

#define ASCII_SIZE 128

// flags for the dfa, mask to check if needed. 
#define ADD_IDENTIFIER_STATE_FLAG 1
#define ADD_NUMBER_STATE_FLAG 2
#define ADD_CHAR_STATES_FLAG 4
#define ADD_STRING_STATES_FLAG 8

#define is_id(c) (isalpha(c) || (c) == '_')
#define is_single_quotes(c) ((c) == 39)
#define is_quotes(c) ((c) == 34)

typedef struct LEXER_DFA_STATE_STRUCT {
    unsigned int index;   // index of state                
    char *lexeme;         // lexeme of state, if the state does not accept this will be NULL
    token_type_t type;    // states type
} lexer_dfa_state_T;

typedef struct LEXER_DFA_STRUCT {
    short **DFA;                        // matrix defining the DFA
    token_T **toks;                     // tokens in the DFA
    unsigned int n_toks;                // number of tokens
    lexer_dfa_state_T **states;         // states in the DFA
    lexer_dfa_state_T **last_states;    // saved last instance of each type of state
    unsigned int n_states;              // number of states
    char *filename;                     // where to contain the DFA
    unsigned short flags;               // flags, represented as bits 
    unsigned char n_flag_states;        // number of states defined by the flags
} lexer_dfa_T;


int init_dfa(token_T **toks, const size_t n_toks, const char *DFA_filename, char *DFA_states_filename, unsigned short flags);
int init_default_dfa();

#endif