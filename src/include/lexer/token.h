#ifndef QUEST_TOKEN_H
#define QUEST_TOKEN_H

typedef enum TOKEN_ENUM {
    #define TOK(name, lexeme, val, is_kw) TOK_##name val,
    #include "tokens.h"
    #undef TOK
    NUM_TOK = 80
} token_type_E;


typedef struct TOKEN_STRUCT {
    char *value;
    token_type_E type;
} token_T;


token_T *init_token(char *value, int type);
int token_cmp(const token_T *tok1, const token_T *tok2);
int token_cmp_generic(const void *tok1, const void *tok2);

#endif