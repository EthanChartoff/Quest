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

symbol_table_tree_node_T *init_symbol_table_tree_leaf(symbol_table_T *table) {
    symbol_table_tree_node_T *sttn = malloc(sizeof(symbol_table_tree_node_T));

    sttn->table = table;
    sttn->children = NULL;
    sttn->n_children = 0;

    return sttn;
}

void symbol_table_tree_node_add(symbol_table_tree_node_T *sttn, symbol_table_tree_node_T *sttn_child) {
    sttn->children = realloc(sttn->children, sizeof(symbol_table_tree_node_T *) * (sttn->n_children + 1));

    sttn->children[sttn->n_children] = sttn_child;
    sttn->n_children++;
}

void symbol_table_tree_print(symbol_table_tree_T *stt);


