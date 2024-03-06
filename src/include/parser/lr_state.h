#ifndef QUEST_LR_STATE_H
#define QUEST_LR_STATE_H

#include "lr_item.h"

typedef struct LR_STATE_STRUCT {
    lr_item_T **items;                   // set of items in the state
    struct LR_ITEM_STRUCT *transitions;  // transitions of the state, indicated by token
} lr_state_T;

lr_state_T *init_lr_state();

#endif