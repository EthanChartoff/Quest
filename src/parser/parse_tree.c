#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

parse_tree_T *init_parse_tree(parse_tree_node_T *root, rule_T **rules, size_t n_rules) {
    parse_tree_T *t = malloc(sizeof(parse_tree_T));

    t->root = root;
    t->rules = rules;
    t->n_rules = n_rules;
}

parse_tree_node_T *init_parse_tree_node(symbol_T *sym, ssize_t rule_index, parse_tree_node_T **children, size_t n_children) {
    parse_tree_node_T *pt = malloc(sizeof(parse_tree_node_T));
    if(!pt)
        thrw(ALLOC_ERR);

    pt->symbol = sym;
    pt->rule_index = rule_index;
    pt->children = children;
    pt->n_children = n_children;

    return pt;
}

parse_tree_node_T *init_parse_tree_leaf(symbol_T *sym) {
    parse_tree_node_T *pt = malloc(sizeof(parse_tree_node_T));
    if(!pt)
        thrw(ALLOC_ERR);

    pt->symbol = sym;
    pt->rule_index = -1;
    pt->children = NULL;
    pt->n_children = 0;

    return pt;
}

void traverse_parse_tree(parse_tree_node_T *tree, int layer) {
    if(tree == NULL)
        return;

    int i;
    char *val = tree->n_children > 0 
        ? tree->symbol->symbol->non_terminal->value  
        : tree->symbol->symbol->terminal->value;

    for(i = 0; i < tree->n_children; ++i) {
        traverse_parse_tree(tree->children[i], layer + 1);
    }

    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s - %zu, %zd\n", val, tree->n_children, tree->rule_index);
}   
