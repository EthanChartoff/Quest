//===--- The Quest Language: Lexer -------------------===
//
// The lexer of the compiler.
//
//
// WORK IN PROGRESS
//
//===------------------------------------------------===

#include "include/lexer.h"
#include "include/lexer_automata.h"
#include "include/macros.h"
#include "include/token.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


// advance lexer to the next character in its source.
void lexer_advance(lexer_T *lex) {
    if(lex->i < lex->src_size && lex->c != '\0') {
        lex->i++;
        lex->c = lex->src[lex->i];
    }
}

void lexer_skip_whitespace(lexer_T *lex) {
    while (lex->c == '\r'   // carriage return 
        || lex->c == '\n'   // newline 
        || lex->c == '\t'   // tab
        || lex->c == ' ') 
        lexer_advance(lex); // skip
}

void lexer_skip_bullshit(lexer_T *lex) {
    while(lex->c > lex->automata->n_symbols) {
        printf("Unexcepted symbol\n");
        lexer_advance(lex);
    }
}

static token_T* get_token(lexer_T *lex) {
    unsigned int curr_state = 0, buffer_len = 1;
    char *buffer = malloc(sizeof(char));

    if(lex->automata->automata[curr_state][lex->c] == -1) {
        buffer = (char *) realloc(buffer, (++buffer_len) * sizeof(char));
        buffer[buffer_len - 1] = '\0';
        buffer[buffer_len - 2] = lex->c;

        lexer_advance(lex);

        return init_token(buffer, lex->automata->state_type[curr_state]);
    }
    
    do {
        buffer = (char *) realloc(buffer, (++buffer_len) * sizeof(char));
        buffer[buffer_len - 1] = '\0';
        buffer[buffer_len - 2] = lex->c;

        curr_state = lex->automata->automata[curr_state][lex->c];        

        lexer_advance(lex);

    } while(lex->automata->automata[curr_state][lex->c] != -1 && lex->c != '\0');

    return init_token(buffer, lex->automata->state_type[curr_state]);
}

token_T* lexer_next_token(lexer_T *lex) {
    while (lex->c != '\0') {
        lexer_skip_whitespace(lex);
        lexer_skip_bullshit(lex);
        lexer_skip_whitespace(lex);

        return get_token(lex);
    }    
    return init_token(0, TOK_eof);
}


// initilize lexer with a source.
// TODO: dont need dfa src
lexer_T* init_lexer(char *src) {
    lexer_T *lex = malloc(sizeof(lexer_T));

    lex->src = src;
    lex->src_size = strlen(src);
    lex->i = 0;
    lex->c = src[lex->i];    
    lex->automata = init_lexer_automata(LEXER_DFA_PATH, LEXER_DFA_STATES_PATH);

    return lex;
}
