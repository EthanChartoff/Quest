#ifndef QUEST_LR_ITEM_H
#define QUEST_LR_ITEM_H

#include "grammer.h"
#include "rule.h"

typedef struct LR_ITEM_STRUCT {
    rule_T *rule;
    size_t dot_index;
    token_T *lookahead;
} lr_item_T;

lr_item_T *init_lr_item(rule_T *rule, size_t dot_index);
int lr_item_compare(const lr_item_T *item1, const lr_item_T *item2);
lr_item_T **closure(grammer_T *grammer, lr_item_T *item);


#endif