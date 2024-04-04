#ifndef QUEST_QUEST_H
#define QUEST_QUEST_H

#include "lexer/lexer.h"
#include "parser/parser.h"

typedef struct QUEST_STRUCT {
    char* src;
    lexer_T* lexer;
    parser_T* parser;
} quest_T;

void compile(char *src);

void compile_file(const char *filename);

#endif /* QUEST_QUEST_H */


