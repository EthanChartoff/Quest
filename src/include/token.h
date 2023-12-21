#ifndef QUEST_TOKEN_H
#define QUEST_TOKEN_H

// main file
typedef enum TOKEN_ENUM {
    #define TOK(name, str, str_name, val, is_kw) TOK_##name,
    #include "tokens.h"
    #undef TOK
    NUM_TOK
} token_type_t;

typedef enum TOKEN_ENUM2 {
    #define TOK(name, str, str_name, val, is_kw) TOK2_##name,
    #include "tokens.h"
    #undef TOK
    NUM_TOK2
} token_type_t2;



typedef struct TOKEN_STRUCT {
    char* value;
    token_type_t type;
} token_T;

token_T* init_token(char* value, int type);

#endif