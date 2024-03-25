#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdlib.h>

parse_tree_node_T *init_parse_tree_node(symbol_T *sym, parse_tree_node_T **children, size_t n_children) {
    parse_tree_node_T *pt = malloc(sizeof(parse_tree_node_T));
    if(!pt)
        thrw(ALLOC_ERR);

    pt->symbol = sym;
    pt->children = children;
    pt->n_children = n_children;

    return pt;
}