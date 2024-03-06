#include "../include/parser/lr_item.h"
#include <stdio.h>
#include <stdlib.h>


lr_item_T *init_lr_item(rule_T *rule, size_t dot_index) {
    lr_item_T *item = malloc(sizeof(lr_item_T));
    
    item->rule = rule;
    item->dot_index = dot_index;

    return  item;
}

int lr_item_compare(const lr_item_T *item1, const lr_item_T *item2) {
    return rule_compare(item1->rule, item2->rule) && item1->dot_index == item2->dot_index;
}

// Closure of Item Sets
//
// If I is a set of items for a grammar G, then CLOSURE(I) is the set of items
// constructed from I by the two rules:
// 1. Initially, add every item in I to CLOSURE(I).
// 2. If A -> a.Bb is in CLOSURE(I) and B ! is a production, then add the
// item B -> .y to CLOSURE(I), if it is not already there.
lr_item_T **closure(grammer_T *grammer, lr_item_T *item) {
    int changed, found, closure_items_size = 1, i, j, k;
    lr_item_T **closure_items = malloc(sizeof(lr_item_T *)), *tmp;

    closure_items[0] = malloc(sizeof(lr_item_T));
    closure_items[0] = item;

    do {
        changed = 0;
        
        // go over all closure items 
        for(i = 0; i < closure_items_size && closure_items_size < 5; ++i) {
            for(j = 0; j < grammer->size; ++j) {
                // if the grammer 
                if(grammer->rules[j]->left->type == item->rule->right[item->dot_index]->type) {
                    
                    found = 0;
                    tmp = init_lr_item(grammer->rules[j], 0);

                    for(k = 0; k < closure_items_size; ++k) {
                        if((found = lr_item_compare(closure_items[k], tmp))) {
                            break;
                        }
                    }

                    if(!found) {
                            closure_items = realloc(closure_items, sizeof(lr_item_T *) * (closure_items_size + 1));

                            closure_items[closure_items_size++] = tmp;
                            changed = 1;
                        }
                }
            }
        }   
    } while(changed);

    return closure_items;
}