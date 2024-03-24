#ifndef QUEST_PARSER_H
#define QUEST_PARSER_H

#include "action_table.h"
#include "goto_table.h"
#include "grammer.h"
#include "lr_stack.h"
#include "rule.h"
#include "slr.h"
#include "../../utils/DS/include/queue.h"

typedef enum PARSE_ACTION_ENUM {
    ERR,
    ACCEPT,
    SHIFT,
    REDUCE
} parse_action_E;


typedef struct PARSER_STRUCT {
    action_tbl_T *action;   // action table
    goto_tbl_T *go_to;      // goto table
    rule_T **rules;         // array of all rules. in array so getting of rule is theta(1);
    size_t n_rules;         // number of rules
    lr_stack_T *stack;      // lr stack of parser 
} parser_T;

parser_T *init_parser(slr_T *slr);

int parse_tok(parser_T *prs, token_T *tok);
void parse(parser_T *prs, queue_T *queue_tok);

void parser_shift(parser_T *prs, int data);
void parser_reduce(parser_T *prs, rule_T *rule);


#endif