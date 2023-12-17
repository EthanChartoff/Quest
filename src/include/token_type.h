#ifndef QUEST_TOKEN_TYPE_H
#define QUEST_TOKEN_TYPE_H

typedef enum TOKEN_TYPE_ENUM {
    TOK_NULL,
#define T(name, str, val, is_keyword) TOK_##name val,
#include "tokens.h"
#undef T
	TOK_LAST_TOKEN
} token_type;


typedef struct TOKEN_STRUCT {
    char* value;
    token_type type;
} token_T;

token_T* init_token(char* value, int type);

char* token_type_to_str(const int type);

char* token_to_str(token_T *tk);
char* token_to_str_details(const token_T *tk); // TODO: implement (if needed).

#endif