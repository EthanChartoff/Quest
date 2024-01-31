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

#include "../include/token.h"
#include <stddef.h>
#include <ctype.h>

#define ASCII_SIZE 128

// flags for the dfa, mask to check if needed. 
#define ADD_IDENTIFIER_STATE_FLAG 1
#define ADD_NUMBER_STATE_FLAG 2

#define IS_CHAR_ID(a) isalpha((char) a) || a == '_' 
#define IS_CHAR_NUM(a) isdigit(a)

typedef enum LEXER_DFA_STATE_TYPE {
    DENY,
    ACCEPT,
    IDENTIFIER,
    NUMBER
} lexer_dfa_state_type_T;

typedef struct LEXER_DFA_STATE_STRUCT {
    unsigned int index;             // index of state                
    char *lexeme;                   // lexeme of state, if the state does not accept this will be NULL
    lexer_dfa_state_type_T type;    // states type
} lexer_dfa_state_T;

typedef struct LEXER_DFA_STRUCT {
    short **DFA;                    // matrix defining the DFA
    token_T **toks;                 // tokens in the DFA
    unsigned int n_toks;            // number of tokens
    lexer_dfa_state_T **states;     // states in the DFA
    unsigned int n_states;          // number of states
    char *filename;                 // where to contain the DFA
    unsigned short flags;           // flags, represented as bits 
    unsigned char n_flag_states;    // number of states defined by the flags
} lexer_dfa_T;


int init_dfa(token_T **toks, const size_t n_toks, const char *filename, unsigned short flags);
int init_default_dfa();

#endif