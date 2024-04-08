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
#include "../../utils/symbol_table/include/symbol_table.h"


/*
    each rule should have a corresponding definition
*/
void definition_start_r(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_program_sl(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_sl_s(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_sl_sl(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_exp_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_compound_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_selection_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_iteration_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_labeled_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_s_decl(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_decl(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_type_int(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_type_char(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_type_float(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_type_void(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

void definition_exp_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_cnstnt_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

void definition_assignment_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_assignment_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_logical_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_logical_or_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_logical_and_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_logical_and_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_inclusive_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_inclusive_or_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_exclusive_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_exclusive_or_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_and_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_and_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_equality_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_equality_equal_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_equality_notequal_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_relational_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_relational_less_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_relational_less_equal_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_relational_greater_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_relational_greater_equal_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_shift_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_shift_lshift_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_shift_rshift_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_additive_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_additive_plus_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_additive_minus_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_multiplicative_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_multiplicative_multiply_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_multiplicative_divide_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_multiplicative_mod_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_primary_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_primary_exp_id(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_primary_exp_constant(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_primary_exp_str(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_exp_exp_precedence(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_exp_exp(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

void definition_compount_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

void definition_selection_stmt_if(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);
void definition_selection_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

void definition_iteration_stmt(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s);

static void (*def_fns[])(stack_T *astack, parse_tree_node_T *tree, stack_T *st_s) = {
    definition_start_r,
    definition_program_sl,
    definition_sl_s,
    definition_sl_sl,
    definition_s_exp_stmt,
    definition_s_compound_stmt,
    definition_s_selection_stmt,
    definition_s_iteration_stmt,
    definition_s_labeled_stmt,
    definition_s_decl,
    definition_decl,
    definition_type_int,
    definition_type_char,
    definition_type_float,
    definition_type_void,

    definition_exp_stmt,
    definition_cnstnt_exp,

    definition_assignment_exp_precedence,
    definition_assignment_exp,
    definition_logical_or_exp_precedence,
    definition_logical_or_exp,
    definition_logical_and_exp_precedence,
    definition_logical_and_exp,
    definition_inclusive_or_exp_precedence,
    definition_inclusive_or_exp,
    definition_exclusive_or_exp_precedence,
    definition_exclusive_or_exp,
    definition_and_exp_precedence,
    definition_and_exp,
    definition_equality_exp_precedence,
    definition_equality_equal_exp,
    definition_equality_notequal_exp,
    definition_relational_exp_precedence,
    definition_relational_less_exp,
    definition_relational_less_equal_exp,
    definition_relational_greater_exp,
    definition_relational_greater_equal_exp,
    definition_shift_exp_precedence,
    definition_shift_lshift_exp,
    definition_shift_rshift_exp,
    definition_additive_exp_precedence,
    definition_additive_plus_exp,
    definition_additive_minus_exp,
    definition_multiplicative_exp_precedence,
    definition_multiplicative_multiply_exp,
    definition_multiplicative_divide_exp,
    definition_multiplicative_mod_exp,
    definition_primary_exp_precedence,
    definition_primary_exp_id,
    definition_primary_exp_constant,
    definition_primary_exp_str,
    definition_exp_exp_precedence,
    definition_exp_exp,

    definition_compount_stmt,

    definition_selection_stmt_if,
    definition_selection_stmt,

    definition_iteration_stmt,
};


#endif