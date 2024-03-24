#include "../include/parser/parser.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

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

int parse_tok(parser_T *prs, token_T *tok) {
    int terminal_col = action_tbl_find_terminal(prs->action, tok);
    int top = lr_stack_peek(prs->stack);
    char action = prs->action->actions[top][terminal_col][0];
    rule_T *cur_rule;

    switch (action) {
        case 's': /* shift action */ 
            parser_shift(prs, atoi(prs->action->actions[top][terminal_col] + 1));
            return SHIFT;

        case 'r': /* reduce action */
            cur_rule = prs->rules[atoi(prs->action->actions[top][terminal_col] + 1)];
            parser_reduce(prs, cur_rule);
            return REDUCE;

        case 'a': /* accept */
            return ACCEPT;

        default:  /* error */
            thrw(PARSER_ACTION_ERROR);
            return ERR;
    }
}

void parse(parser_T *prs, queue_T *queue_tok) {
    int parse_status = ACCEPT;
    token_T *tok = queue_dequeue(queue_tok);

    do {
        if(parse_status == SHIFT) 
            tok = queue_dequeue(queue_tok);

        parse_status = parse_tok(prs, tok);
    } while(parse_status != ACCEPT);
}

void parser_shift(parser_T *prs, int data) {
    lr_stack_push(prs->stack, data);
}

void parser_reduce(parser_T *prs, rule_T *rule) {
    int i;

    for(i = 0; i < rule->right_size; ++i) {
        lr_stack_pop(prs->stack);
    }

    i = prs->go_to->gotos[lr_stack_peek(prs->stack)][goto_tbl_find_non_terminal(prs->go_to, rule->left)];
    lr_stack_push(prs->stack,  i);
}