#ifndef QUEST_PARSER_H
#define QUEST_PARSER_H

#include "action_table.h"
#include "goto_table.h"
#include "slr.h"

typedef struct PARSER_STRUCT {
    action_tbl_T *action;
    goto_tbl_T *go_to;
} parser_T;

parser_T *init_parser(slr_T *slr);

void parse_tok(token_T *tok);
void parse();

#endif