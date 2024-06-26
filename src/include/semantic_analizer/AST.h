#ifndef QUEST_AST_H
#define QUEST_AST_H

#include "../parser/symbol.h"
#include "../../utils/symbol_table//include/symbol_table.h"
#include <stddef.h>

typedef struct ABSTRACT_SYNTAX_TREE_NODE_STRUCT {
    symbol_T *symbol;
    struct ABSTRACT_SYNTAX_TREE_NODE_STRUCT **children;
    size_t n_children;
    symbol_table_entry_T *st_entry;
} ast_node_T;

ast_node_T *init_ast_node(symbol_T *symbol, ast_node_T **children, size_t n_children);
ast_node_T *init_ast_leaf(symbol_T *symbol);

void ast_add_to_node(ast_node_T *ast, ast_node_T *child);

void traverse_ast(ast_node_T *ast, int layer);

#endif /* QUEST_AST_H */