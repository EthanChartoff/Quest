#ifndef QUEST_LEXER_H
#define QUEST_LEXER_H
#include "lexer_automata.h"
#include "token.h"
#include <stddef.h>

typedef struct LEXER_STRUCT {
    char* src;                      // src code
    size_t src_size;                // size of src code
    char c;                         // curr character the lexer is on
    unsigned int i;                 // curr index the lexer is on 
    lexer_automata_T *automata;     // automata of the lexer
} lexer_T;

lexer_T* init_lexer(char *src);

void lexer_advance(lexer_T* lex);

token_T* lexer_advance_with(lexer_T* lex, token_T* tk);

token_T* lexer_advance_current(lexer_T* lex, int type);

char lexer_peek(lexer_T* lex, int offset);

void lexer_skip_whitespace(lexer_T* lex);

token_T* lexer_parse_id(lexer_T* lex);

token_T* lexer_parse_number(lexer_T* lex);

token_T* lexer_next_token(lexer_T* lex);

#endif