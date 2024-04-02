#include "../include/semantic_analizer/definitions.h"
#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>


static ast_node_T **convert_stmt_list_to_ast_list(stack_T *astack) {
    // ast_node_T **children = NULL;
    // int nc = 1;
    // parse_tree_node_T *cur_node = pn;

    // // while node is not end node
    // while(cur_node->rule_index == 14) {
    //     nc++;
    //     children = realloc(children, sizeof(ast_node_T *) * nc);
    //     if(!children)
    //         thrw(ALLOC_ERR);
    //     children[nc - 2] = stack_pop(astack);

    //     cur_node = cur_node->children[1];
    // }
    // children[nc - 1] = stack_pop(astack);

    // return children;
}

void definition_program(stack_T *astack);

void definition_statement_list_statement(stack_T *astack) {

    ast_node_T *stmt_list = init_ast_leaf(
        init_symbol_non_terminal(
            init_non_terminal("statement_list", NON_TERM_statement_list)));
    ast_add_to_node(stmt_list, stack_pop(astack));

    stack_push(astack, stmt_list);
}

// TODO: may be problematic because function goes to all stmtlists a number of times
void definition_statement_list_statement_list(stack_T *astack) {
    printf("%zu\n", astack->size);

    ast_node_T *stmt_list = stack_pop(astack);
    ast_add_to_node(stmt_list, stack_pop(astack));
    stack_push(astack, stmt_list);
}

void definition_statement_assignment(stack_T *astack) {

}

void definition_statement_condition(stack_T *astack) {

}

void definition_statement_while(stack_T *astack) {
    
}

void definition_assignment(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *ass;

    children[0] = stack_pop(astack);
    ass = stack_pop(astack);
    children[1] = stack_pop(astack);
    
    stack_push(
        astack, 
        init_ast_node(
            ass->symbol, 
            children, 
            2
    ));
}

void definition_conditional(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 3);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *cond;
    
    cond = stack_pop(astack);           // if
    stack_pop(astack);                  // (
    children[0] = stack_pop(astack);    // exp

    stack_pop(astack);                  // )
    stack_pop(astack);                  // {
    children[1] = stack_pop(astack);    // stmt_list
    stack_pop(astack);                  // }
    stack_pop(astack);                  // else
    stack_pop(astack);                  // {                  
    children[2] = stack_pop(astack);    // stmt block
    stack_pop(astack);                  // }


    
    // char *val = ((ast_node_T *) stack_peek(astack))->symbol->sym_type == NON_TERMINAL
    //     ? ((ast_node_T *) stack_peek(astack))->symbol->symbol->non_terminal->value
    //     : ((ast_node_T *) stack_peek(astack))->symbol->symbol->terminal->value;
    // printf("%zd\n", astack->size); 


    
    stack_push(
        astack, 
        init_ast_node(
            cond->symbol,
            children,
            3
    ));
}

void definition_while(stack_T *astack);

void definition_semantic_block(stack_T *astack) {
    
}

void definition_expression(stack_T *astack);

// gets a math_expression node with an operation, and turn them into an ast node
void definition_math_expression_operation(stack_T *astack) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 2);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *op;

    children[0] = stack_pop(astack);
    op = stack_pop(astack);
    children[1] = stack_pop(astack);

    stack_push(
        astack, 
        init_ast_node(
        op->symbol, 
        children, 
        2
    ));
}

// gets a math_expression node with a single constant child, and turn it into a leaf for the ast
void definition_math_expression_constant(stack_T *astack) {
    stack_push(
        astack, 
        init_ast_leaf(stack_pop(astack)));
}

void definition_op_plus(stack_T *astack);
void definition_op_minus(stack_T *astack);