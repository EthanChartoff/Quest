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

void parse_tree_free(parse_tree_node_T *tree) {
    if(tree == NULL)
        return;

    if(tree->children) {
        size_t i;
        for(i = 0; i < tree->n_children; ++i) {
            parse_tree_free(tree->children[i]);
        }

        free(tree->children);
    }

    free(tree);
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


void parse_tree_traverse_preorder(parse_tree_node_T *tree, int layer) {
    if(tree == NULL)
        return;

    int i;
    char *val = tree->symbol->sym_type == NON_TERMINAL 
        ? tree->symbol->symbol->non_terminal->value  
        : tree->symbol->symbol->terminal->value;

    int type = tree->symbol->sym_type == NON_TERMINAL 
        ? tree->symbol->symbol->non_terminal->type  
        : tree->symbol->symbol->terminal->type;

    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s, %zd\n", val, tree->rule_index);

    for(i = 0; i < tree->n_children; ++i) {
        parse_tree_traverse_preorder(tree->children[i], layer + 1);
    }
}

void parse_tree_traverse_postorder(parse_tree_node_T *tree, int layer) {
    if(tree == NULL)
        return;

    int i;
    char *val = tree->symbol->sym_type == NON_TERMINAL
        ? tree->symbol->symbol->non_terminal->value
        : tree->symbol->symbol->terminal->value;

    int type = tree->symbol->sym_type == NON_TERMINAL
        ? tree->symbol->symbol->non_terminal->type
        : tree->symbol->symbol->terminal->type;

    for(i = 0; i < tree->n_children; ++i) {
        parse_tree_traverse_postorder(tree->children[i], layer + 1);
    }

    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s\n", val);
}
