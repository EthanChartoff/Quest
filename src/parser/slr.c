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

// finds items goto index inside cc arr.
static size_t find_goto_index(grammer_T *gram, set_T *items, symbol_T *symbol, set_T **cc, size_t cc_size) {
    size_t i;
    set_T *gt_set = go_to(gram, items, symbol);

    for(i = 0; i < cc_size; ++i) {
        if(!lr_item_set_cmp(cc[i], gt_set))
            return i;
    } 
}


static char **init_goto_table();

static char*** init_action_table(slr_T *lr0) {
    int i, j; 
    size_t gti;
    set_T *itemset;
    set_node_T *cur_itemset_node, *cn_item;
    lr_item_T *item;

    // go over collection
    for(i = 0; i < lr0->lr0_cc_size; ++i) {
        cur_itemset_node = lr0->lr0_cc[i]->head;
        itemset = cur_itemset_node->data;

        // go ovet items in set
        cn_item = itemset->head;
        for(j = 0; j < itemset->size; ++j) {
            item = cn_item->data;
            // If [A -> a.ab ] is in Ii and GOTO(Ii, a) = Ij , then set ACTION[i, a] to
            // shift j. Here a must be a terminal.
            if(item->dot_index < item->rule->right_size && item->dot_index > 0 
            && item->rule->right[item->dot_index - 1] == item->rule->right[item->dot_index]) {
                gti = find_goto_index(lr0->grammer, 
                                    itemset, 
                                    item->rule->right[item->dot_index - 1], 
                                    lr0->lr0_cc,
                                    lr0->lr0_cc_size);
                lr0->action[i, ]
            }

            cn_item = cn_item->next;
        }
    }
    


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

int init_slr_tables(set_T *lr0, grammer_T *gram) {
    slr_T *slr = malloc(sizeof(slr_T));
    if(!slr)
        thrw(ALLOC_ERR);
    
    slr->grammer = gram;
    slr->lr0_cc = lr0_set_to_arr(lr0);
    slr->lr0_cc_size = lr0->size;
    slr->action = init_action_table(slr);
    slr->go_to = init_goto_table(); 
}