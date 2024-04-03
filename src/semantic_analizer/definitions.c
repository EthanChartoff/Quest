// TODO: BUG FOUND, listing stmts doesnt work with certien trees
#include "../include/semantic_analizer/definitions.h"
#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

void definition_program(stack_T *astack);

void definition_statement_list_statement(stack_T *astack) {
    ast_node_T *stmt_list = init_ast_leaf(
        init_symbol_non_terminal(
            init_non_terminal("statement_list", NON_TERM_statement_list)));
    ast_add_to_node(stmt_list, stack_pop(astack));
    stack_push(astack, stmt_list);
}

void definition_statement_list_statement_list(stack_T *astack) {
    ast_node_T *stmt_list = stack_pop(astack);
    ast_add_to_node(stmt_list, stack_pop(astack));
    
    stack_push(astack, stmt_list);
}

void definition_statement_assignment(stack_T *astack) {
    // Implement assignment statement logic here
}

void definition_statement_condition(stack_T *astack) {
    // Implement condition statement logic here
}

void definition_statement_while(stack_T *astack) {
    // Implement while statement logic here
}

void definition_assignment(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(children == NULL) {
        // Handle memory allocation error
        thrw(ALLOC_ERR);
        return;
    }

    children[0] = stack_pop(astack);
    ast_node_T *ass = stack_pop(astack);
    children[1] = stack_pop(astack);

    stack_push(astack, 
        init_ast_node(ass->symbol, children, 2));
}

void definition_conditional(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 3);
    if(children == NULL) {
        // Handle memory allocation error
        thrw(ALLOC_ERR);
        return;
    }

    ast_node_T *cond = stack_pop(astack); // if
    stack_pop(astack); // (
    children[0] = stack_pop(astack); // exp
    stack_pop(astack); // )
    stack_pop(astack); // {
    children[1] = stack_pop(astack); // stmt_list
    stack_pop(astack); // }
    stack_pop(astack); // else
    stack_pop(astack); // {
    children[2] = stack_pop(astack); // stmt block
    stack_pop(astack); // }

    stack_push(astack, init_ast_node(cond->symbol, children, 3));
}

void definition_while(stack_T *astack) {
    // Implement while statement logic here
}

void definition_semantic_block(stack_T *astack) {
    // Implement semantic block logic here
}

void definition_expression(stack_T *astack) {
    // Implement expression logic here
}

void definition_math_expression_operation(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(children == NULL) {
        // Handle memory allocation error
        thrw(ALLOC_ERR);
        return;
    }

    children[0] = stack_pop(astack);
    ast_node_T *op = stack_pop(astack);
    children[1] = stack_pop(astack);

    stack_push(astack, init_ast_node(op->symbol, children, 2));
}

void definition_math_expression_constant(stack_T *astack) {
    stack_push(astack, init_ast_leaf(stack_pop(astack)));
}

void definition_op_plus(stack_T *astack) {
    // Implement addition operation logic here
}

void definition_op_minus(stack_T *astack) {
}

void definition_op_plus(stack_T *astack);
void definition_op_minus(stack_T *astack);


