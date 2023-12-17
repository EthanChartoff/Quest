#ifndef QUEST_LEXER_H
#define QUEST_LEXER_H
#include "token_type.h"
#include <stddef.h>

typedef struct LEXER_STRUCT {
    char* src;
    size_t src_size;
    char c;             // curr character the lexer is on
    unsigned int i;     // curr index the lexer is on 
} lexer_T;

lexer_T* init_lexer(char *src);

token_T* lexer_next_token(lexer_T* lex);

#endif