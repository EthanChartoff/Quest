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

ast_node_T *definition_assignment(parse_tree_node_T *pn, ast_node_T **astns);
ast_node_T *definition_math_expression_operation(parse_tree_node_T *pn, ast_node_T **astns);
ast_node_T *definition_math_expression_constant(parse_tree_node_T *pn, ast_node_T **astns);

#endif