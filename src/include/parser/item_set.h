#ifndef QUEST_ITEM_SET
#define QUEST_ITEM_SET

#include "lr_item.h"


// TODO: make a proper set, this is not good.

typedef struct LR_ITEM_SET_STRUCT {
    lr_item_T **set;
    size_t size;
} lr_item_set_T;

lr_item_set_T *init_lr_item_set();
lr_item_set_T *init_lr_item_set_with_item(lr_item_T *item);

int add_item(lr_item_set_T **set, lr_item_T *item);
int add_set(lr_item_set_T **set, lr_item_set_T *set_to_add);
int is_item_in_set(const lr_item_set_T *set, const lr_item_T *item);

lr_item_set_T *closure(grammer_T *grammer, lr_item_set_T *items);
lr_item_set_T *go_to(grammer_T *grammer, lr_item_set_T *items, symbol_T *symbol);

lr_item_set_T *closure_lookahead(grammer_T *grammer, lr_item_set_T *items);
lr_item_set_T *go_to_lookahead(grammer_T *grammer, lr_item_set_T *items, symbol_T *symbol);


lr_item_set_T *lr0_items(grammer_T *grammer, lr_item_T *starting_item);
lr_item_set_T *lr1_items(grammer_T *grammer, lr_item_T *starting_item);





#endif