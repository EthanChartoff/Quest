#ifndef QUEST_PARSE_TREE_NODE_H
#define QUEST_PARSE_TREE_NODE_H

#include "symbol.h"
#include <stddef.h>

typedef struct PARSE_TREE_NODE_STRUCT {
    symbol_T *symbol;                           // symbol in curr node on parse tree
    struct PARSE_TREE_NODE_STRUCT **children;   // arr of children of parse tree node 
    size_t n_children;                          // number of children the node has
} parse_tree_node_T;

parse_tree_node_T *init_parse_tree_node(symbol_T *sym, parse_tree_node_T **children, size_t n_children);



#endif /* QUEST_PARSE_TREE_NODE_H */