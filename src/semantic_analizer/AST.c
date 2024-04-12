#include "../include/semantic_analizer/AST.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Initialize a new AST node
 * 
 * @param symbol     The symbol that represents the node
 * @param children   Array of children nodes
 * @param n_children Number of children nodes
 * @return ast_node_T* The new AST node
 */
ast_node_T *init_ast_node(symbol_T *symbol, ast_node_T **children, size_t n_children) {
    ast_node_T *astn = malloc(sizeof(ast_node_T));
    if(!astn)
        thrw(ALLOC_ERR);


    astn->symbol = symbol;
    astn->children = children;
    astn->n_children = n_children;
    astn->st_entry = NULL;

    return astn;
}

/**
 * @brief Initialize a new AST leaf node
 * 
 * @param symbol The symbol that represents the leaf
 * @return ast_node_T* The new AST leaf node
 */
ast_node_T *init_ast_leaf(symbol_T *symbol) {
    ast_node_T *astn = malloc(sizeof(ast_node_T));
    if(!astn)
        thrw(ALLOC_ERR);

    astn->symbol = symbol;
    astn->children = NULL;
    astn->n_children = 0;
    astn->st_entry = NULL;

    return astn;
}

/**
 * @brief Add a node to another node
 * 
 * @param ast       The node to add the child to
 * @param child     The node to be added
 */
void ast_add_to_node(ast_node_T *ast, ast_node_T *child) {
    ast->n_children++;
    ast->children = realloc(ast->children, sizeof(ast_node_T *) * ast->n_children);
    ast->children[ast->n_children - 1] = child;
}

/**
 * @brief Traverse the AST and print it
 * 
 * @param ast     The root node of the AST
 * @param layer   The level of the node (0 being the root)
 */
void traverse_ast(ast_node_T *ast, int layer) {
    if(ast == NULL)
        return;
    
    int i;
    char *val = ast->symbol->sym_type == TERMINAL
        ? ast->symbol->symbol->terminal->value  
        : ast->symbol->symbol->non_terminal->value; 

    // printf("%c\n", val[0]);
    for(i = 0; i < layer; ++i) {
        printf("  ");
    }

    printf("%s\n", val);

    for(i = 0; i < ast->n_children; ++i) {
        traverse_ast(ast->children[i], layer + 1);
    }
}
