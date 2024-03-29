//===--= symbol_table_tree.c =----------------------------------------===
//
// 
//
//===-----------------------------------------------------------------===

#include "include/symbol_table_tree.h"
#include <stdlib.h>

symbol_table_tree_T *init_symbol_table_tree(symbol_table_tree_node_T *root) {
    symbol_table_tree_T *stt = malloc(sizeof(symbol_table_tree_T));

    stt->root = root;

    return stt;
}

symbol_table_tree_node_T *init_symbol_table_tree_node(symbol_table_T *table, symbol_table_tree_node_T **children, size_t n_children) {
    symbol_table_tree_node_T *sttn = malloc(sizeof(symbol_table_tree_node_T));

    sttn->table = table;
    sttn->children = children;
    sttn->n_children = n_children;

    return sttn;
}
