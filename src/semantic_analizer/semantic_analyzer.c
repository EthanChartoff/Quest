#include "../include/semantic_analizer/semantic_analyzer.h"
#include <stdio.h>

void traverse_parse_tree(parse_tree_node_T *tree, int layer) {
    if(tree == NULL)
        return;

    int i;
    char *val = tree->n_children > 0 
        ? tree->symbol->symbol->non_terminal->value  
        : tree->symbol->symbol->terminal->value;

    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s - %zu\n", val, tree->n_children);

    for(i = 0; i < tree->n_children; ++i) {
        traverse_parse_tree(tree->children[i], layer + 1);
    }
}   