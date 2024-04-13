#ifndef QUEST_QUEST_H
#define QUEST_QUEST_H

#include "code_gen/code_generator.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "semantic_analizer/sdt.h"

typedef struct QUEST_STRUCT {
    char *srcfile;
    char *destfile;
    char *src;
    lexer_T *lexer;
    parser_T *parser;
    sdt_T *sdt;
    code_gen_T *code_gen;
} quest_T;

void compile(quest_T *q);

void compile_file(const char *filename);

#endif /* QUEST_QUEST_H */


