#ifndef QUEST_AST_H
#define QUEST_AST_H
#include "list.h"

typedef enum {
    AST_COMPOUND,
    AST_TYPE_DEF,
    AST_FUNCTION,
    AST_VARIABLE,
    AST_STATEMENT,
    AST_NOP   
} AST_type;

typedef struct AST_STRUCT {
    AST_type type;
    list_T* children;
    char* name;
} AST_T;

AST_T* init_ast(int type);

#endif