#ifndef QUEST_AST_H
#define QUEST_AST_H

#include "../parser/symbol.h"
#include <stddef.h>

typedef struct ABSTRACT_SYNTAX_TREE_NODE_STRUCT {
    symbol_T *symbol;
    struct ABSTRACT_SYNTAX_TREE_NODE_STRUCT **children;
    size_t n_children;
} ast_node_T;

ast_node_T *init_ast_node(symbol_T *symbol, ast_node_T **children, size_t n_children);
ast_node_T *init_ast_leaf(symbol_T *symbol);

void traverse_ast(ast_node_T *ast, int layer);

#endif /* QUEST_AST_H */