//===--= slr.h =------------------------------------------------------===
//
// In this file will be all functions relating to building the slr parser,
// including action and goto tables. 
//
//===-----------------------------------------------------------------===

#include "../include/parser/slr.h"
#include "../include/parser/lr_item.h"
#include "../include/parser/bnf.h"
#include "../include/macros.h"
#include "../utils/err/err.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// finds items goto index inside cc arr.
static size_t find_goto_index(grammer_T *gram, set_T *items, symbol_T *symbol, set_T **cc, size_t cc_size) {
    size_t i;
    set_T *gt_set = go_to(gram, items, symbol);

    for(i = 0; i < cc_size; ++i) {
        if(!lr_item_set_cmp(cc[i], gt_set))
            return i;
    } 

    return -1;
}


static goto_tbl_T *init_goto_table(slr_T *lr0) {
    int i, j, gti;
    set_T *itemset;
    set_node_T *cur_itemset_node, *cn_item;
    lr_item_T *item;
    goto_tbl_T *gotos = init_goto_tbl(
        non_terminals_in_symbol_set(lr0->grammer->symbols), 
        n_non_terminals_in_symbol_set(lr0->grammer->symbols), 
        lr0->lr0_cc_size);

    // go over collection
    for (i = 0; lr0->lr0_cc_size && lr0->lr0_cc[i]; ++i) {
        itemset = lr0->lr0_cc[i];

        for(j = 0; j < gotos->n_non_terminals; ++j) {
            gti = find_goto_index(
                    lr0->grammer, 
                    itemset, 
                    init_symbol_non_terminal(gotos->non_terminals[j]), 
                    lr0->lr0_cc,
                    lr0->lr0_cc_size); 

            if(gti != -1) {
                gotos->gotos[i][goto_tbl_find_non_terminal(gotos, gotos->non_terminals[j])] = gti;
            }
        }
    }

    return gotos;
}

static action_tbl_T *init_action_table(slr_T *lr0) {
    int i, j, k, tmp; 
    char action[5];
    action_tbl_T *actions;
    set_T *itemset, *followset;
    set_node_T *cur_itemset_node, *cn_item, *cn_term;
    lr_item_T *item;
    token_T *cur_term;

    actions = init_action_tbl(
        terminals_in_symbol_set_and_dollar(lr0->grammer->symbols), 
        n_terminals_in_symbol_set(lr0->grammer->symbols) + 1, 
        lr0->lr0_cc_size);

    // go over collection
    for(i = 0; i < lr0->lr0_cc_size; ++i) {
        itemset = lr0->lr0_cc[i];

        // go ovet items in set
        cn_item = itemset->head;

        for(j = 0; j < itemset->size; ++j) {
            item = cn_item->data;

            // If [A -> a.ab ] is in Ii and GOTO(Ii, a) = Ij , then set ACTION[i, a] to
            // shift j. Here a must be a terminal.
            if(item->dot_index < item->rule->right_size
            && item->rule->right[item->dot_index]->sym_type == TERMINAL) {            
                tmp = find_goto_index(
                    lr0->grammer, 
                    itemset, 
                    item->rule->right[item->dot_index], 
                    lr0->lr0_cc,
                    lr0->lr0_cc_size);

                if(tmp != -1) {
                    sprintf(action, "s%d", tmp);
                    actions->actions[i][action_tbl_find_terminal(actions, item->rule->right[item->dot_index]->symbol->terminal)] = strdup(action);
                }
            }
            // If [A -> a.] is in Ii , then set ACTION[i, a] to "reduce A -> a" for all
            // a in FOLLOW(A); here A may not be S'.
            else if(item->dot_index == item->rule->right_size && item->rule->left->type != NON_TERM_start) {

                followset = follow(lr0->grammer, item->rule->left);
                tmp = find_right_grammer_index(lr0->grammer, item->rule->right, item->rule->right_size);

                if(tmp != -1) {
                    sprintf(action, "r%d", tmp);

                    cn_term = followset->head;
                    for(k = 0; k < followset->size; ++k) {
                        cur_term = cn_term->data;

                        actions->actions[i][action_tbl_find_terminal(actions, cur_term)] = strdup(action);

                        cn_term = cn_term->next;
                    }
                }
            }
            // If [S -> S.] is in Ii , then set ACTION[i, $] to accept.
            else if(item->rule->left->type == NON_TERM_start && item->dot_index == item->rule->right_size) {
                sprintf(action, "acc");
                tmp = action_tbl_find_terminal(actions, init_token("$", TOK_eof));          
                actions->actions[i][tmp] = strdup(action);  
            }

            cn_item = cn_item->next;
        }
    }
    
    return actions;
}

static set_T **lr0_set_to_arr(const set_T *lr0) {
    int i;
    set_T **lr0_arr = malloc(sizeof(set_T *) * lr0->size), *curr_item_set;
    if(!lr0_arr)
        thrw(ALLOC_ERR);
    set_node_T *cn = lr0->head;

    for(i = 0; i < lr0->size; ++i) {
        curr_item_set = cn->data;

        lr0_arr[lr0->size - i - 1] = malloc(sizeof(set_T));
        if(!lr0_arr[lr0->size - i - 1])
            thrw(ALLOC_ERR);
        lr0_arr[lr0->size - i - 1]->size = curr_item_set->size;
        lr0_arr[lr0->size - i - 1]->compare = curr_item_set->compare;
        lr0_arr[lr0->size - i - 1]->head = curr_item_set->head;

        cn = cn->next;
    }

    return lr0_arr;
}

slr_T *init_slr(set_T *lr0, grammer_T *gram) {
    slr_T *slr = malloc(sizeof(slr_T));
    if(!slr)
        thrw(ALLOC_ERR);
    
    slr->grammer = gram;
    slr->lr0_cc = lr0_set_to_arr(lr0);

    slr->lr0_cc_size = lr0->size;
    slr->action = init_action_table(slr);
    slr->go_to = init_goto_table(slr);

    return slr; 
}

slr_T *init_default_slr() {
    // symbol_T *E = init_symbol_non_terminal(init_non_terminal("E", NON_TERM_E));
    // symbol_T *T = init_symbol_non_terminal(init_non_terminal("T" ,NON_TERM_T));
    // symbol_T *F = init_symbol_non_terminal(init_non_terminal("F" ,NON_TERM_F));

    // symbol_T *p = init_symbol_terminal(init_token("+", TOK_PLUS));
    // symbol_T *x = init_symbol_terminal(init_token("*", TOK_STAR));
    // symbol_T *id = init_symbol_terminal(init_token("id", TOK_IDENTIFIER));
    // symbol_T *lp = init_symbol_terminal(init_token("(", TOK_LPAREN));
    // symbol_T *rp = init_symbol_terminal(init_token(")", TOK_RPAREN));

    // symbol_T *EpT[] = {E, p, T};
    // symbol_T *TxF[] = {T, x, F};
    // symbol_T *lEr[] = {lp, E, rp};


    // rule_T *start = init_rule(E_s->symbol->non_terminal, &E, 1);
    // rule_T *EEpT = init_rule(E->symbol->non_terminal, EpT, 3);
    // rule_T *ET = init_rule(E->symbol->non_terminal, &T, 1);
    // rule_T *TTxF = init_rule(T->symbol->non_terminal, TxF, 3);
    // rule_T *TF = init_rule(T->symbol->non_terminal, &F, 1);
    // rule_T *FlEr = init_rule(F->symbol->non_terminal, lEr, 3);
    // rule_T *Fid = init_rule(F->symbol->non_terminal, &id, 1);

    // set_T *rules = set_init(rule_cmp_generic);
    // set_add(rules, start);
    // set_add(rules, EEpT);
    // set_add(rules, ET);
    // set_add(rules, TTxF);
    // set_add(rules, TF);
    // set_add(rules, FlEr);
    // set_add(rules, Fid);

    
    // set_T *syms = set_init(token_cmp_generic);
    // set_add(syms, p);
    // set_add(syms, x);
    // set_add(syms, id);
    // set_add(syms, lp);
    // set_add(syms, rp);
    // set_add(syms, E_s);
    // set_add(syms, E);
    // set_add(syms, T);
    // set_add(syms, F);

    
    // grammer_T *gram = init_grammer(rules, syms);

    // set_T *la = set_init(token_cmp_generic);
    // set_add(la, init_token("eof", TOK_eof));

    // set_T *tmp = set_init(lr_item_cmp_generic);
    // set_add(tmp, init_lr_item(start, 0, NULL));

    // set_T *itms = lr0_items(gram, init_lr_item(start, 0, NULL)), *itm_itm;
    // slr_T *slr = init_slr(itms, gram);

    set_T *rules = set_init(rule_cmp_generic);symbol_T *program =  init_symbol_non_terminal(init_non_terminal("program", NON_TERM_program));
    set_add(rules, program);
    symbol_T *statement =  init_symbol_non_terminal(init_non_terminal("statement", NON_TERM_statement));
    set_add(rules, statement);
    symbol_T *expression_statement =  init_symbol_non_terminal(init_non_terminal("expression_statement", NON_TERM_expression_statement));
    set_add(rules, expression_statement);
    symbol_T *expression =  init_symbol_non_terminal(init_non_terminal("expression", NON_TERM_expression));
    set_add(rules, expression);
    symbol_T *assignment_expression =  init_symbol_non_terminal(init_non_terminal("assignment_expression", NON_TERM_assignment_expression));
    set_add(rules, assignment_expression);
    symbol_T *assignment_operator =  init_symbol_non_terminal(init_non_terminal("assignment_operator", NON_TERM_assignment_operator));
    set_add(rules, assignment_operator);
    symbol_T *unary_operator =  init_symbol_non_terminal(init_non_terminal("unary_operator", NON_TERM_unary_operator));
    set_add(rules, unary_operator);
    symbol_T *conditional_expression =  init_symbol_non_terminal(init_non_terminal("conditional_expression", NON_TERM_conditional_expression));
    set_add(rules, conditional_expression);
    symbol_T *logical_or_expression =  init_symbol_non_terminal(init_non_terminal("logical_or_expression", NON_TERM_logical_or_expression));
    set_add(rules, logical_or_expression);
    symbol_T *logical_and_expression =  init_symbol_non_terminal(init_non_terminal("logical_and_expression", NON_TERM_logical_and_expression));
    set_add(rules, logical_and_expression);
    symbol_T *inclusive_or_expression =  init_symbol_non_terminal(init_non_terminal("inclusive_or_expression", NON_TERM_inclusive_or_expression));
    set_add(rules, inclusive_or_expression);
    symbol_T *exclusive_or_expression =  init_symbol_non_terminal(init_non_terminal("exclusive_or_expression", NON_TERM_exclusive_or_expression));
    set_add(rules, exclusive_or_expression);
    symbol_T *and_expression =  init_symbol_non_terminal(init_non_terminal("and_expression", NON_TERM_and_expression));
    set_add(rules, and_expression);
    symbol_T *equality_expression =  init_symbol_non_terminal(init_non_terminal("equality_expression", NON_TERM_equality_expression));
    set_add(rules, equality_expression);
    symbol_T *relational_expression =  init_symbol_non_terminal(init_non_terminal("relational_expression", NON_TERM_relational_expression));
    set_add(rules, relational_expression);
    symbol_T *shift_expression =  init_symbol_non_terminal(init_non_terminal("shift_expression", NON_TERM_shift_expression));
    set_add(rules, shift_expression);
    symbol_T *additive_expression =  init_symbol_non_terminal(init_non_terminal("additive_expression", NON_TERM_additive_expression));
    set_add(rules, additive_expression);
    symbol_T *multiplicative_expression =  init_symbol_non_terminal(init_non_terminal("multiplicative_expression", NON_TERM_multiplicative_expression));
    set_add(rules, multiplicative_expression);
    symbol_T *cast_expression =  init_symbol_non_terminal(init_non_terminal("cast_expression", NON_TERM_cast_expression));
    set_add(rules, cast_expression);
    symbol_T *unary_expression =  init_symbol_non_terminal(init_non_terminal("unary_expression", NON_TERM_unary_expression));
    set_add(rules, unary_expression);
    symbol_T *postfix_expression =  init_symbol_non_terminal(init_non_terminal("postfix_expression", NON_TERM_postfix_expression));
    set_add(rules, postfix_expression);
    symbol_T *primary_expression =  init_symbol_non_terminal(init_non_terminal("primary_expression", NON_TERM_primary_expression));
    set_add(rules, primary_expression);
    symbol_T *identifier =  init_symbol_non_terminal(init_non_terminal("identifier", NON_TERM_identifier));
    set_add(rules, identifier);
    symbol_T *constant =  init_symbol_non_terminal(init_non_terminal("constant", NON_TERM_constant));
    set_add(rules, constant);
    symbol_T *compound_statement =  init_symbol_non_terminal(init_non_terminal("compound_statement", NON_TERM_compound_statement));
    set_add(rules, compound_statement);
    symbol_T *declaration =  init_symbol_non_terminal(init_non_terminal("declaration", NON_TERM_declaration));
    set_add(rules, declaration);
    symbol_T *declaration_specifier =  init_symbol_non_terminal(init_non_terminal("declaration_specifier", NON_TERM_declaration_specifier));
    set_add(rules, declaration_specifier);
    symbol_T *type_specifier =  init_symbol_non_terminal(init_non_terminal("type_specifier", NON_TERM_type_specifier));
    set_add(rules, type_specifier);
    symbol_T *type_qualifier =  init_symbol_non_terminal(init_non_terminal("type_qualifier", NON_TERM_type_qualifier));
    set_add(rules, type_qualifier);
    symbol_T *init_declarator =  init_symbol_non_terminal(init_non_terminal("init_declarator", NON_TERM_init_declarator));
    set_add(rules, init_declarator);
    symbol_T *selection_statement =  init_symbol_non_terminal(init_non_terminal("selection_statement", NON_TERM_selection_statement));
    set_add(rules, selection_statement);
    symbol_T *iteration_statement =  init_symbol_non_terminal(init_non_terminal("iteration_statement", NON_TERM_iteration_statement));
    set_add(rules, iteration_statement);
    symbol_T *jump_statement =  init_symbol_non_terminal(init_non_terminal("jump_statement", NON_TERM_jump_statement));
    set_add(rules, jump_statement);
    symbol_T *labeled_statement =  init_symbol_non_terminal(init_non_terminal("labeled_statement", NON_TERM_labeled_statement));
    set_add(rules, labeled_statement);
    symbol_T *declarator =  init_symbol_non_terminal(init_non_terminal("declarator", NON_TERM_declarator));
    set_add(rules, declarator);
    symbol_T *init_declarator_list =  init_symbol_non_terminal(init_non_terminal("init_declarator_list", NON_TERM_init_declarator_list));
    set_add(rules, init_declarator_list);
    symbol_T *initializer =  init_symbol_non_terminal(init_non_terminal("initializer", NON_TERM_initializer));
    set_add(rules, initializer);
    symbol_T *initializer_list =  init_symbol_non_terminal(init_non_terminal("initializer_list", NON_TERM_initializer_list));
    set_add(rules, initializer_list);
    symbol_T *constant_expression =  init_symbol_non_terminal(init_non_terminal("constant_expression", NON_TERM_constant_expression));
    set_add(rules, constant_expression);

    
    bnf_make_non_terminals(PARSER_BNF, "/home/goodman/school/Quest/src/include/parser/non_terminals_bnf.h");

}