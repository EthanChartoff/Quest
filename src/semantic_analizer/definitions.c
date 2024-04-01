#include "../include/semantic_analizer/definitions.h"
#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>


static ast_node_T **convert_stmt_list_to_ast_list(parse_tree_node_T *pn, stack_T *astack) {
    ast_node_T **children = NULL;
    int nc = 1;
    parse_tree_node_T *cur_node = pn;

    // while node is not end node
    while(cur_node->rule_index == 14) {
        nc++;
        children = realloc(children, sizeof(ast_node_T *) * nc);
        if(!children)
            thrw(ALLOC_ERR);
        children[nc - 2] = stack_pop(astack);

        cur_node = cur_node->children[1];
        printf("\nlol\n");

    }
    children[nc - 1] = stack_pop(astack);

    return children;
}

ast_node_T *definition_program(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_statement_list_statement(parse_tree_node_T *pn, stack_T *astack);

// TODO: may be problematic because function goes to all stmtlists a number of times
ast_node_T *definition_statement_list_statement_list(parse_tree_node_T *pn, stack_T *astack) {
    int prev_size = astack->size;
    ast_node_T **children = convert_stmt_list_to_ast_list(pn, astack);

    return init_ast_node(pn->symbol, children, prev_size - astack->size);
}

ast_node_T *definition_statement_assignment(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_statement_condition(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_statement_while(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_assignment(parse_tree_node_T *pn, stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *ass;

    children[0] = stack_pop(astack);
    ass = stack_pop(astack);
    children[1] = stack_pop(astack);
    
    return init_ast_node(
        ass->symbol, 
        children, 
        2
    );
}

ast_node_T *definition_conditional(parse_tree_node_T *pn, stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    ast_node_T *cond;

    cond = stack_pop(astack);           // if
    stack_pop(astack);                  // (
    children[0] = stack_pop(astack);    // exp
    stack_pop(astack);                  // )
    children[1] = stack_pop(astack);    // stmt block
    stack_pop(astack);                  // else
    children[2] = stack_pop(astack);    // stmt block
    
    return init_ast_node(
        cond->symbol,
        children,
        3
    );
}

ast_node_T *definition_while(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_semantic_block(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_expression(parse_tree_node_T *pn, stack_T *astack);

// gets a math_expression node with an operation, and turn them into an ast node
ast_node_T *definition_math_expression_operation(parse_tree_node_T *pn, stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *op;

    children[0] = stack_pop(astack);
    op = stack_pop(astack);
    children[1] = stack_pop(astack);

    return init_ast_node(
        op->symbol, 
        children, 
        2
    );
}

// gets a math_expression node with a single constant child, and turn it into a leaf for the ast
ast_node_T *definition_math_expression_constant(parse_tree_node_T *pn, stack_T *astack) {
    return init_ast_leaf(pn->children[0]->children[0]->symbol);
}

ast_node_T *definition_op_plus(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_op_minus(parse_tree_node_T *pn, stack_T *astack);