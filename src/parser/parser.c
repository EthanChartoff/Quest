#include "../include/parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

parser_T *init_parser(slr_T *slr) {
    parser_T *prs = malloc(sizeof(parser_T));

    prs->action = slr->action;
    prs->go_to = slr->go_to;

    return prs;
}

void parse_tok(token_T *tok) {
    printf("%s\n", tok->value);
}

void parse(queue_T *queue_tok) {
    while (!is_empty(queue_tok)) {
        parse_tok(queue_dequeue(queue_tok));
    }
}