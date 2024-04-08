//===--= symbol_table_tree.h =----------------------------------------===
//
// a symbol table tree is used to traverse scopes. each symbol table 
// represents a scope, and children of a node in the tree represents a 
// nested scope. this means that the root of the tree is the global scope,
// the main program is a child of the global scope, and so on...
//
//===-----------------------------------------------------------------===

#ifndef QUEST_SYMBOL_TABLE_TREE_H
#define QUEST_SYMBOL_TABLE_TREE_H

#include "symbol_table.h"
#include <stddef.h>

typedef struct SYMBOL_TABLE_TREE_NODE_STRUCT {
    symbol_table_T *table;
    struct SYMBOL_TABLE_TREE_NODE_STRUCT **children;
    size_t n_children;
} symbol_table_tree_node_T;

typedef struct SYMBOL_TABLE_TREE_STRUCT {
    symbol_table_tree_node_T *root;
} symbol_table_tree_T;

symbol_table_tree_T *init_symbol_table_tree(symbol_table_tree_node_T *root);
symbol_table_tree_node_T *init_symbol_table_tree_node(symbol_table_T *table, symbol_table_tree_node_T **children, size_t n_children);
symbol_table_tree_node_T *init_symbol_table_tree_leaf(symbol_table_T *table);



#endif /* QUEST_SYMBOL_TABLE_TREE_H */