//===--= definitions.h =----------------------------------------------===
//
// Here are all the prototypes for definition for each rule, written to build an AST
// using the parse tree.  
//
//===-----------------------------------------------------------------===

#ifndef QUEST_DEFINITIONS_H
#define QUEST_DEFINITIONS_H

#include "AST.h"
#include "../parser/parse_tree.h"
#include "../../utils/DS/include/stack.h"


/*
    each rule should have a corresponding definition
*/

ast_node_T *definition_program(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_statement_list_statement(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_statement_list_statement_list(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_statement_assignment(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_statement_condition(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_statement_while(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_assignment(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_conditional(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_while(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_semantic_block(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_expression(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_math_expression_operation(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_math_expression_constant(parse_tree_node_T *pn, stack_T *astack);

ast_node_T *definition_op_plus(parse_tree_node_T *pn, stack_T *astack);
ast_node_T *definition_op_minus(parse_tree_node_T *pn, stack_T *astack);

#endif