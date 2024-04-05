#include "../include/parser/parser.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/stack.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

// this function is what the parser should do when encountering a shift action in the action table
static int shift_action(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s) {
    int terminal_col = action_tbl_find_terminal(prs->action, tok);
    int top = lr_stack_peek(prs->stack);

    stack_push(sym_s, init_parse_tree_leaf(init_symbol_terminal(tok)));
    
    parser_shift(prs, atoi(prs->action->actions[top][terminal_col] + 1));
    return SHIFT;
}

// this function is what the parser should do when encountering a reduce action in the action table
static int reduce_action(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s) {

    int terminal_col = action_tbl_find_terminal(prs->action, tok);
    int top = lr_stack_peek(prs->stack);
    int i;
    rule_T *cur_rule = prs->rules[atoi(prs->action->actions[top][terminal_col] + 1)];
    parse_tree_node_T **children = malloc(cur_rule->right_size * sizeof(parse_tree_node_T *)), *root = NULL;

    for(i = 0; i < cur_rule->right_size; ++i) {
        children[i] = stack_pop(sym_s);
    }
    
    root = init_parse_tree_node(init_symbol_non_terminal(cur_rule->left), atoi(prs->action->actions[top][terminal_col] + 1), children, cur_rule->right_size);
    stack_push(sym_s, root);
    parser_reduce(prs, cur_rule);
    return REDUCE;
}

// this function is what the parser should do when encountering an accept action in the action table
static int accept_action(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s) {
    return ACCEPT;
}

// this function is what the parser should do when encountering an error action in the action table
static int error_action(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s) {
    thrw(PARSER_ACTION_ERR);
    return ERR;
}

static int parse_tok(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s, int (*action_funcs[LETTERS_SIZE])(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s)) {    
    char action = prs->action->actions[lr_stack_peek(prs->stack)][action_tbl_find_terminal(prs->action, tok)][0];
    printf("%c, %s, %d\n", action, tok->value, lr_stack_peek(prs->stack));

    if(!islower(action))
        thrw(PARSER_ACTION_ERR);
    return action_funcs[action - 'a'](prs, tok, node, sym_s);
}

parser_T *init_parser(slr_T *slr) {
    parser_T *prs = malloc(sizeof(parser_T));
    set_node_T *cn = slr->grammer->rules->head;
    rule_T *rule;
    int i;

    prs->action = slr->action;
    prs->go_to = slr->go_to;
    prs->n_rules = slr->grammer->rules->size;
    prs->rules = malloc(sizeof(rule_T *) * prs->n_rules);
    for(i = 0; i < prs->n_rules; ++i) {
        rule = cn->data;

        prs->rules[i] = malloc(sizeof(rule_T));
        prs->rules[i]->left = rule->left;
        prs->rules[i]->right = rule->right;
        prs->rules[i]->right_size = rule->right_size;

        cn = cn->next;
    }
    prs->stack = init_lr_stack(10);
    lr_stack_push(prs->stack, 0);

    return prs;
}

parse_tree_T *parse(parser_T *prs, queue_T *queue_tok) {
    int parse_status = SHIFT;
    int n_children = 0, children_capacity = 0, i;
    token_T *tok;
    parse_tree_node_T **children = NULL, **tmp = NULL, *root;
    stack_T *sym_s = stack_init();
    int (*action_funcs[LETTERS_SIZE])(parser_T *prs, token_T *tok, parse_tree_node_T *node, stack_T *sym_s);

    action_funcs['s' - 'a'] = &shift_action;
    action_funcs['r' - 'a'] = &reduce_action;
    action_funcs['a' - 'a'] = &accept_action;

    for(i = 0; i < LETTERS_SIZE; ++i) {
        if((i + 'a') != 's' && (i + 'a') != 'r' && (i + 'a') != 'a') {
            action_funcs[i] = &error_action;
        }
    }

    do {
        if(parse_status == SHIFT) 
            tok = queue_dequeue(queue_tok);
        
        parse_status = parse_tok(prs, tok, root, sym_s, action_funcs);
    } while(parse_status != ACCEPT);

    return init_parse_tree(stack_pop(sym_s), prs->rules, prs->n_rules);
}

void parser_shift(parser_T *prs, int data) {
    lr_stack_push(prs->stack, data);
}

symbol_T *parser_reduce(parser_T *prs, rule_T *rule) {
    int i, state;

    for(i = 0; i < rule->right_size; ++i) {
        lr_stack_pop(prs->stack);
    }

    state = lr_stack_peek(prs->stack);

    i = prs->go_to->gotos[state][goto_tbl_find_non_terminal(prs->go_to, rule->left)];
    lr_stack_push(prs->stack,  i);
    return init_symbol_non_terminal(rule->left);
}