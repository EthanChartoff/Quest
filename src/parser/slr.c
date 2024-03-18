//===--= slr.h =------------------------------------------------------===
//
// In this file will be all functions relating to building the slr parser,
// including action and goto tables. 
//
//===-----------------------------------------------------------------===

#include "../include/parser/slr.h"
#include "../include/parser/lr_item.h"
#include "../utils/err/err.h"
#include <stdlib.h>

static char **init_goto_table();

static char*** init_action_table(slr_T *lr0) {
    int i, j;
    set_T *itemset;
    set_node_T *cur_itemset_node;
    lr_item_T *item;

    // go over collection
    for(i = 0; i < lr0->lr0_cc_size; ++i) {
        cur_itemset_node = lr0->lr0_cc[i]->head;
        itemset = cur_itemset_node->data;
        // go ovet items in set
        for(j = 0; j < cur_itemset_node.)
    }
    // If [A -> a.ab ] is in Ii and GOTO(Ii, a) = Ij , then set ACTION[i, a] to
    // shift j. Here a must be a terminal.


}

static set_T **lr0_set_to_arr(const set_T *lr0) {
    int i;
    set_T **lr0_arr = malloc(sizeof(set_T *) * lr0->size), *curr_item_set;
    if(!lr0_arr)
        thrw(ALLOC_ERR);
    set_node_T *cn = lr0->head;

    for(i = 0; i < lr0->size; ++i) {
        curr_item_set = cn->data;

        lr0_arr[lr0->size - i - 1] = malloc(sizeof(set_T));
        if(!lr0_arr[lr0->size - i - 1])
            thrw(ALLOC_ERR);
        lr0_arr[lr0->size - i - 1]->size = curr_item_set->size;
        lr0_arr[lr0->size - i - 1]->compare = curr_item_set->compare;
        lr0_arr[lr0->size - i - 1]->head = curr_item_set->head;

        cn = cn->next;
    }

    return lr0_arr;
}

int init_slr_tables(set_T *lr0) {
    slr_T *slr = malloc(sizeof(slr_T));
    if(!slr)
        thrw(ALLOC_ERR);
    
    slr->lr0_cc = lr0_set_to_arr(lr0);
    slr->lr0_cc_size = lr0->size;
    slr->action = init_action_table(slr);
    slr->go_to = init_goto_table(); 
}