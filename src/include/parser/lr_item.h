#ifndef QUEST_LR_ITEM_H
#define QUEST_LR_ITEM_H

#include "grammer.h"
#include "rule.h"
#include "symbol_set.h"
#include "symbol.h"
#include "symbol_set.h"
#include "../../utils/DS/include/generic_set.h"

typedef struct LR_ITEM_STRUCT {
    rule_T *rule;
    size_t dot_index;
    set_T *lookaheads;
} lr_item_T;

lr_item_T *init_lr_item(rule_T *rule, size_t dot_index, set_T *lookaheads);

int lr_item_cmp(const lr_item_T *item1, const lr_item_T *item2);
int lr_item_cmp_generic(const void *item1, const void *item2);
int lr_item_set_cmp(const set_T *set1, const set_T *set2);  
int lr_item_set_cmp_generic(const void *item1, const void *item2);

set_T *first(const grammer_T *gram, const symbol_T **syms, const size_t size);

set_T *closure(grammer_T *grammer, set_T *items);
set_T *go_to(grammer_T *grammer, set_T *items, symbol_T *symbol);
set_T *closure_lookahead(grammer_T *grammer, set_T *items);
set_T *go_to_lookahead(grammer_T *grammer, set_T *items, symbol_T *symbol);

set_T *lr0_items(grammer_T *grammer, lr_item_T *starting_item);
set_T *lr1_items(grammer_T *grammer, lr_item_T *starting_item);
set_T *lalr_items(grammer_T *grammer, lr_item_T *starting_item);

#endif