#ifndef QUEST_LEXER_AUTOMATA_H
#define QUEST_LEXER_AUTOMATA_H

#include "token.h"

typedef struct LEXER_AUTOMATA_STRUCT {
    short **automata;           // mat representing the automata 
    token_type_E *state_type;   // arr representing states types: deny, accept... 
    unsigned int n_state;       // number of states
    unsigned int n_symbols;     // number of symbols from the start of the 
} lexer_automata_T;

lexer_automata_T* init_lexer_automata(const char *auto_src, const char *states_src);

#endif