#ifndef QUEST_PARSER_H
#define QUEST_PARSER_H

#include "action_table.h"
#include "goto_table.h"
#include "grammer.h"
#include "lr_stack.h"
#include "parse_tree.h"
#include "rule.h"
#include "slr.h"
#include "../../utils/DS/include/queue.h"
#include "symbol.h"

typedef enum PARSE_STATUS_TYPE_ENUM {
    ERR,
    ACCEPT,
    SHIFT,
    REDUCE
} parse_status_type_E;

typedef struct PARSE_STATUS_STRUCT {
    symbol_T *sym;  // symbol that came with the status
    int type;       // status type
} parse_status_T;

typedef struct PARSER_STRUCT {
    action_tbl_T *action;   // action table
    goto_tbl_T *go_to;      // goto table
    rule_T **rules;         // array of all rules. in array so getting of rule is theta(1);
    size_t n_rules;         // number of rules
    lr_stack_T *stack;      // lr stack of parser 
} parser_T;

parser_T *init_parser(slr_T *slr);
parse_status_T *init_parse_status(symbol_T *sym, int type);

parse_tree_node_T *parse(parser_T *prs, queue_T *queue_tok);
void parser_shift(parser_T *prs, int data);
symbol_T *parser_reduce(parser_T *prs, rule_T *rule);


#endif