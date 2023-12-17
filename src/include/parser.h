#ifndef QUEST_PARSER_H
#define QUEST_PARSER_H
#include "lexer.h"
#include "token_type.h"
#include "AST.h"

typedef struct PARSER_STRUCT {
    lexer_T* lexer;
    token_T* token;
} parser_T;

parser_T* init_parser(lexer_T* lex);

AST_T* parser_parse(parser_T* par);

#endif
