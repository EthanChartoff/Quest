#include "../include/semantic_analizer/definitions.h"
#include "../include/parser/parse_tree.h"
#include <stdio.h>
#include <stdlib.h>

ast_node_T *definition_assignment(parse_tree_node_T *pn, ast_node_T **astns) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    children[0] = astns[0];
    children[1] = astns[2];
    
    return init_ast_node(
        pn->children[1]->symbol, 
        children, 
        2
    );
}

// gets a math_expression node with an operation, and turn them into an ast node
ast_node_T *definition_math_expression_operation(parse_tree_node_T *pn, ast_node_T **astns) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    children[0] = astns[0];
    children[1] = astns[2];

    return init_ast_node(
        astns[1]->symbol, 
        children, 
        2
    );
}

// gets a math_expression node with a single constant child, and turn it into a leaf for the ast
ast_node_T *definition_math_expression_constant(parse_tree_node_T *pn, ast_node_T **astns) {
    return init_ast_leaf(pn->children[0]->children[0]->symbol);
}

