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
#include <threads.h>

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
    for (i = 0; i < lr0->lr0_cc_size && lr0->lr0_cc[i]; ++i) {
        itemset = lr0->lr0_cc[i];

        for(j = 0; j < gotos->n_non_terminals; ++j) {
            gti = find_goto_index(
                    lr0->grammer, 
                    itemset, 
                    init_symbol_non_terminal(gotos->non_terminals[j]), 
                    lr0->lr0_cc,
                    lr0->lr0_cc_size); 


            gotos->gotos[i][goto_tbl_find_non_terminal(gotos, gotos->non_terminals[j])] = gti;
            
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

    for(i = 0; i < actions->n_states; ++i) {
        for(j = 0; j < actions->n_terminals; ++j) {
            if(!actions->actions[i][j])
                actions->actions[i][j] = strdup("e");  
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

void slr_write_to_bin(slr_T *slr, char *dest) {
    FILE *fp = fopen(dest, "wb");
    if(!fp)
        thrw(OPEN_FILE_ERR);

    fwrite(slr, sizeof(slr_T), 1, fp);
}

slr_T *slr_read_from_bin(char *src) {
    slr_T *slr = malloc(sizeof(slr_T));
    if(!slr)
        thrw(ALLOC_ERR);
    FILE *fp = fopen(src, "rb");
    if(!fp)
        thrw(OPEN_FILE_ERR);

    fread(slr, sizeof(slr_T), 1, fp);
    return slr;
}

slr_T *init_default_slr() {
    // set_T *syms = set_init(symbol_cmp_generic);

    // symbol_T *constant = init_symbol_non_terminal(init_non_terminal("constant", NON_TERM_constant));
    // symbol_T *operator = init_symbol_non_terminal(init_non_terminal("operator", NON_TERM_operator));
    // symbol_T *math_expression = init_symbol_non_terminal(init_non_terminal("math_expression", NON_TERM_math_expression));
    // symbol_T *expression = init_symbol_non_terminal(init_non_terminal("expression", NON_TERM_expression));
    // symbol_T *statement_block = init_symbol_non_terminal(init_non_terminal("statement_block", NON_TERM_statement_block));
    // symbol_T *while_loop = init_symbol_non_terminal(init_non_terminal("while_loop", NON_TERM_while_loop));
    // symbol_T *conditional = init_symbol_non_terminal(init_non_terminal("conditional", NON_TERM_conditional));
    // symbol_T *assignment = init_symbol_non_terminal(init_non_terminal("assignment", NON_TERM_assignment));
    // symbol_T *statement = init_symbol_non_terminal(init_non_terminal("statement", NON_TERM_statement));
    // symbol_T *statement_list = init_symbol_non_terminal(init_non_terminal("statement_list", NON_TERM_statement_list));
    // symbol_T *program = init_symbol_non_terminal(init_non_terminal("program", NON_TERM_program));
    // symbol_T *start = init_symbol_non_terminal(init_non_terminal("S'", NON_TERM_start));

    // symbol_T *equal = init_symbol_terminal(init_token("=", TOK_EQUEL));
    // symbol_T *if_tok = init_symbol_terminal(init_token("if", TOK_IF));
    // symbol_T *lp = init_symbol_terminal(init_token("(", TOK_LPAREN));
    // symbol_T *rp = init_symbol_terminal(init_token(")", TOK_RPAREN));
    // symbol_T *else_tok = init_symbol_terminal(init_token("else", TOK_ELSE));
    // symbol_T *lb = init_symbol_terminal(init_token("{", TOK_LBRACE));
    // symbol_T *rb = init_symbol_terminal(init_token("}", TOK_RBRACE));
    // symbol_T *num = init_symbol_terminal(init_token("num", TOK_NUMBER_CONSTANT));
    // symbol_T *while_tok = init_symbol_terminal(init_token("while", TOK_WHILE));
    // symbol_T *id = init_symbol_terminal(init_token("id", TOK_IDENTIFIER));
    // symbol_T *p = init_symbol_terminal(init_token("+", TOK_PLUS));
    // symbol_T *m = init_symbol_terminal(init_token("-", TOK_MINUS));

    // set_add(syms, constant);
    // set_add(syms, operator);
    // set_add(syms, math_expression);
    // set_add(syms, expression);
    // set_add(syms, statement_block);
    // set_add(syms, while_loop);
    // set_add(syms, conditional);
    // set_add(syms, assignment);
    // set_add(syms, statement);
    // set_add(syms, statement_list);
    // set_add(syms, program);
    // set_add(syms, start);


    // set_add(syms, equal);
    // set_add(syms, if_tok);
    // set_add(syms, lp);
    // set_add(syms, rp);
    // set_add(syms, else_tok);
    // set_add(syms, lb);
    // set_add(syms, rb);
    // set_add(syms, num);
    // set_add(syms, while_tok);
    // set_add(syms, id);
    // set_add(syms, p);
    // set_add(syms, m);


    // symbol_T *stat_list[] = {statement_list, statement};
    // symbol_T *ass_list[] = {id, equal, expression};
    // symbol_T *cond_list[] = {if_tok, lp, expression, rp, statement_block, else_tok, statement_block};
    // symbol_T *while_loop_list[] = {while_tok, lp, expression, rp, statement_block};
    // symbol_T *statement_block_list[] = {lb, statement_list, rb};
    // symbol_T *me[] = {math_expression, operator, constant};


    // set_T *rules = set_init(rule_cmp_generic);

    // rule_T *start_r = init_rule(start->symbol->non_terminal, &program, 1);
    // rule_T *program_sl = init_rule(program->symbol->non_terminal, &statement_list, 1);
    // rule_T *sl_s = init_rule(statement_list->symbol->non_terminal, &statement, 1);
    // rule_T *sl_sl = init_rule(statement_list->symbol->non_terminal, stat_list, 2);
    // rule_T *s_ass = init_rule(statement->symbol->non_terminal, &assignment, 1);
    // rule_T *s_cond = init_rule(statement->symbol->non_terminal, &conditional, 1);
    // rule_T *s_while = init_rule(statement->symbol->non_terminal, &while_loop, 1);
    // rule_T *ass_e = init_rule(assignment->symbol->non_terminal, ass_list, 3);
    // rule_T *cond_e = init_rule(conditional->symbol->non_terminal, cond_list, 7);
    // rule_T *while_e = init_rule(while_loop->symbol->non_terminal, while_loop_list, 5);
    // rule_T *sb = init_rule(statement_block->symbol->non_terminal, statement_block_list, 3);
    // rule_T *e_math_e = init_rule(expression->symbol->non_terminal, &math_expression, 1);
    // rule_T *math_e = init_rule(math_expression->symbol->non_terminal, me, 3);
    // rule_T *math_c = init_rule(math_expression->symbol->non_terminal, &constant, 1);
    // rule_T *op_p = init_rule(operator->symbol->non_terminal, &p, 1);
    // rule_T *op_m = init_rule(operator->symbol->non_terminal, &m, 1);
    // rule_T *c_num = init_rule(constant->symbol->non_terminal, &num, 1);
    // rule_T *c_id = init_rule(constant->symbol->non_terminal, &id, 1);


    // set_add(rules, start_r);
    // set_add(rules, program_sl);
    // set_add(rules, sl_s);
    // set_add(rules, sl_sl);
    // set_add(rules, s_ass);
    // set_add(rules, s_cond);
    // set_add(rules, s_while);
    // set_add(rules, ass_e);
    // set_add(rules, cond_e);
    // set_add(rules, while_e);
    // set_add(rules, sb);
    // set_add(rules, e_math_e);
    // set_add(rules, math_e);
    // set_add(rules, math_c);
    // set_add(rules, op_p);
    // set_add(rules, op_m);
    // set_add(rules, c_num);
    // set_add(rules, c_id);


    // grammer_T *gram = init_grammer(rules, syms);


    // set_T *itms = lr0_items(gram, init_lr_item(start_r, 0, NULL));
    // slr_T *slr = init_slr(itms, gram);
    // slr_write_to_bin(slr, PARSER_SLR_BIN);

    // slr_T *slr = slr_read_from_bin(PARSER_SLR_BIN);

    // printf("%zu\n", slr->lr0_cc_size);

    // action_tbl_print_to_file(slr->action, PARSER_ACTION_PATH);
    // action_tbl_pretty_print_to_file(slr->action, PARSER_ACTION_PRETTY_PATH);
    // goto_tbl_print_to_file(slr->go_to, PARSER_GOTO_PATH);
    // goto_tbl_pretty_print_to_file(slr->go_to, PARSER_GOTO_PRETTY_PATH);

    // bnf_make_non_terminals(PARSER_BNF, PARSER_BNF_NON_TERMINALS);

    return NULL;
}