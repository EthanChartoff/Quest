#include "../include/semantic_analizer/definitions.h"
#include "../include/parser/parse_tree.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

static ast_node_T *binop_node(ast_node_T *left, ast_node_T *node, ast_node_T *right) {
    ast_add_to_node(node, right);
    ast_add_to_node(node, left);

    return node;
}


void definition_start_r(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_program_sl(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_sl_s(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *stmt_list = init_ast_leaf(tree->symbol);
    ast_add_to_node(stmt_list, stack_pop(astack));
    stack_push(astack, stmt_list);
}
void definition_sl_sl(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *stmt_list = stack_pop(astack);
    ast_add_to_node(stmt_list, stack_pop(astack));
    
    stack_push(astack, stmt_list);
}
void definition_s_exp_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_s_compound_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_s_selection_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_s_iteration_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_s_labeled_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_s_decl(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_decl(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T **children = malloc(sizeof(ast_node_T *) * 3);
    if(!children)
        thrw(ALLOC_ERR);
    ast_node_T *node;

    children[0] = stack_pop(astack); // type
    children[1] = stack_pop(astack); // id
    stack_pop(astack);               // exp
    children[2] = stack_pop(astack); // value
    stack_pop(astack);               // ;

    node = init_ast_node(tree->symbol, children, 3);
    node->st_entry = init_symbol_table_entry(
        children[1]->symbol->symbol->terminal->value, 
        children[0]->symbol->symbol->terminal->type,
        NULL,
        GLOBAL);

    stack_push(astack, node);
    symbol_table_insert(sym_tbl, node->st_entry);
}
void definition_type_int(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_type_char(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_type_float(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_type_void(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}

void definition_exp_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *exp = stack_pop(astack);
    stack_pop(astack);

    stack_push(astack, exp);
}
void definition_cnstnt_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}

void definition_assignment_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_assignment_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_logical_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_logical_or_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_logical_and_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_logical_and_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_inclusive_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_inclusive_or_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_exclusive_or_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_exclusive_or_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_and_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_and_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_equality_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_equality_equal_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_equality_notequal_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_relational_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_relational_less_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_relational_less_equal_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_relational_greater_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_relational_greater_equal_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_shift_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_shift_lshift_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_shift_rshift_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_additive_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_additive_plus_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_additive_minus_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_multiplicative_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_multiplicative_multiply_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_multiplicative_divide_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_multiplicative_mod_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    stack_push(
        astack,
        binop_node(stack_pop(astack), stack_pop(astack), stack_pop(astack))
    );
}
void definition_primary_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *exp;
    
    stack_pop(astack); // (
    exp = stack_pop(astack);
    stack_pop(astack); // )

    stack_push(astack, exp);
}
void definition_primary_exp_id(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_primary_exp_constant(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_primary_exp_str(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_exp_exp_precedence(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}
void definition_exp_exp(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}

void definition_compount_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {}

void definition_selection_stmt_if(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *sec = init_ast_leaf(tree->symbol);

    stack_pop(astack);                          // if
    stack_pop(astack);                          // (
    ast_add_to_node(sec, stack_pop(astack));    // exp
    stack_pop(astack);                          // )
    stack_pop(astack);                          // {
    ast_add_to_node(sec, stack_pop(astack));    // stmts
    stack_pop(astack);                          // }

    stack_push(astack, sec);
}

void definition_selection_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *sec = init_ast_leaf(tree->symbol);

    stack_pop(astack);                          // if
    stack_pop(astack);                          // (
    ast_add_to_node(sec, stack_pop(astack));    // exp
    stack_pop(astack);                          // )
    stack_pop(astack);                          // {
    ast_add_to_node(sec, stack_pop(astack));    // stmts
    stack_pop(astack);                          // }
    stack_pop(astack);                          // else
    stack_pop(astack);                          // {
    ast_add_to_node(sec, stack_pop(astack));    // stmts
    stack_pop(astack);                          // }

    stack_push(astack, sec);
}

void definition_iteration_stmt(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl) {
    ast_node_T *it = init_ast_leaf(tree->symbol);

    stack_pop(astack);                      // while
    stack_pop(astack);                      // (
    ast_add_to_node(it, stack_pop(astack)); // exp
    stack_pop(astack);                      // )
    stack_pop(astack);                      // {
    ast_add_to_node(it, stack_pop(astack)); // stmts
    stack_pop(astack);                      // }

    stack_push(astack, it);
}
