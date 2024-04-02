#include "../include/semantic_analizer/AST.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ast_node_T *init_ast_node(symbol_T *symbol, ast_node_T **children, size_t n_children) {
    ast_node_T *astn = malloc(sizeof(ast_node_T));
    if(!astn)
        thrw(ALLOC_ERR);


    astn->symbol = symbol;
    astn->children = children;
    astn->n_children = n_children;

    return astn;
}

ast_node_T *init_ast_leaf(symbol_T *symbol) {
    ast_node_T *astn = malloc(sizeof(ast_node_T));
    if(!astn)
        thrw(ALLOC_ERR);

    astn->symbol = symbol;
    astn->children = NULL;
    astn->n_children = 0;

    return astn;
}

void ast_add_to_node(ast_node_T *ast, ast_node_T *child) {
    ast->n_children++;
    ast->children = realloc(ast->children, sizeof(ast_node_T *) * ast->n_children);
    ast->children[ast->n_children - 1] = child;
}

void traverse_ast(ast_node_T *ast, int layer) {
    if(ast == NULL)
        return;
    

    int i;
    char *val = ast->symbol->sym_type 
        ? ast->symbol->symbol->non_terminal->value  
        : ast->symbol->symbol->terminal->value; 

    

    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s\n", val);

    for(i = 0; i < ast->n_children; ++i) {
        traverse_ast(ast->children[i], layer + 1);
    }
}