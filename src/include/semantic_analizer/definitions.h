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

void definition_program(stack_T *astack);

void definition_statement_list_statement(stack_T *astack);
void definition_statement_list_statement_list(stack_T *astack);

void definition_statement_assignment(stack_T *astack);
void definition_statement_condition(stack_T *astack);
void definition_statement_while(stack_T *astack);

void definition_assignment(stack_T *astack);

void definition_conditional(stack_T *astack);

void definition_while(stack_T *astack);

void definition_semantic_block(stack_T *astack);

void definition_expression(stack_T *astack);

void definition_math_expression_operation(stack_T *astack);
void definition_math_expression_constant(stack_T *astack);

void definition_op_plus(stack_T *astack);
void definition_op_minus(stack_T *astack);

#endif