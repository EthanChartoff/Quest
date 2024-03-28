#include "../include/parser/parser.h"
#include "../utils/err/err.h"
#include <stddef.h>
#include <stdlib.h>
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

parse_status_T *init_parse_status(symbol_T *sym, int type) {
    parse_status_T *s = malloc(sizeof(parse_status_T));

    s->sym = sym;
    s->type = type;

    return s;
}

parse_status_T *parse_tok(parser_T *prs, token_T *tok) {
    int terminal_col = action_tbl_find_terminal(prs->action, tok);
    int top = lr_stack_peek(prs->stack);
    char action = prs->action->actions[top][terminal_col][0];
    rule_T *cur_rule;

    switch (action) {
        case 's': /* shift action */ 
            parser_shift(prs, atoi(prs->action->actions[top][terminal_col] + 1));
            return init_parse_status(init_symbol_terminal(tok), SHIFT);

        case 'r': /* reduce action */
            cur_rule = prs->rules[atoi(prs->action->actions[top][terminal_col] + 1)];
            return init_parse_status(parser_reduce(prs, cur_rule), REDUCE);

        case 'a': /* accept */
            return init_parse_status(NULL, ACCEPT);

        default:  /* error */
            thrw(PARSER_ACTION_ERROR);
            return init_parse_status(NULL, ERR);
    }
}


parse_tree_node_T *parse(parser_T *prs, queue_T *queue_tok) {
    parse_status_T *parse_status = init_parse_status(NULL, ACCEPT);
    int n_children = 0, children_capacity = 0, i;
    token_T *tok = queue_dequeue(queue_tok);
    parse_tree_node_T **children = NULL, **tmp = NULL, *root;
    
    do {
        if(parse_status->type == SHIFT) {
            n_children++;

            // if number of children is above child arr capacity, alloc more space
            if(n_children > children_capacity) {
                children_capacity++;
                children = realloc(children, children_capacity * sizeof(parse_tree_node_T *));
            }
            
            children[n_children - 1] = init_parse_tree_node(init_symbol_terminal(tok), NULL, 0);

            tok = queue_dequeue(queue_tok);
        }
        else if(parse_status->type == REDUCE) {
            tmp = malloc(n_children * sizeof(parse_tree_node_T *));
            for(i = 0; i < n_children; ++i) 
                tmp[i] = children[i];
            

            root = init_parse_tree_node(
                parse_status->sym, 
                tmp, 
                n_children);         

            children[0] = root;
            n_children = 1;
        }

        parse_status = parse_tok(prs, tok);
    } while(parse_status->type != ACCEPT);

    // free vars
    for(i = 1; i < children_capacity; ++i) {
        free(children[i]);
    }

    free(children);
    free(tok);

    return root;
}

void parser_shift(parser_T *prs, int data) {
    lr_stack_push(prs->stack, data);

}

symbol_T *parser_reduce(parser_T *prs, rule_T *rule) {
    int i;

    for(i = 0; i < rule->right_size; ++i) {
        lr_stack_pop(prs->stack);
    }

    i = prs->go_to->gotos[lr_stack_peek(prs->stack)][goto_tbl_find_non_terminal(prs->go_to, rule->left)];
    lr_stack_push(prs->stack,  i);
    return init_symbol_non_terminal(rule->left);
}