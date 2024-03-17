#ifndef QUEST_ITEM_SET
#define QUEST_ITEM_SET

#include "lr_item.h"
#include "../../utils/DS/include/generic_set.h"


typedef struct LR_ITEM_SET_STRUCT {
    lr_item_T **set;
    size_t size;
} lr_item_set_T;

lr_item_set_T *init_lr_item_set();
lr_item_set_T *init_lr_item_set_with_item(lr_item_T *item);

int add_item(lr_item_set_T **set, lr_item_T *item);
int add_set(lr_item_set_T **set, lr_item_set_T *set_to_add);
int is_item_in_set(const lr_item_set_T *set, const lr_item_T *item);
int lr_item_set_equals(const lr_item_set_T *set1, const lr_item_set_T *set2);
int lr_item_set_equals_generic(const void *set1, const void *set2);





#endif