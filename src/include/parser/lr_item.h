#ifndef QUEST_LR_ITEM_H
#define QUEST_LR_ITEM_H

#include "grammer.h"
#include "rule.h"
#include "symbol_set.h"
#include "symbol.h"
#include "symbol_set.h"

typedef struct LR_ITEM_STRUCT {
    rule_T *rule;
    size_t dot_index;
    token_T *lookahead;
} lr_item_T;

lr_item_T *init_lr_item(rule_T *rule, size_t dot_index, token_T *lookahead);

int lr_item_equals(const lr_item_T *item1, const lr_item_T *item2);
symbol_set_T *first(const grammer_T *gram, const symbol_set_T *syms);

#endif