#include "../include/parser/item_set.h"
#include <stdio.h>
#include <stdlib.h>

lr_item_set_T *init_lr_item_set() {
    lr_item_set_T *set = (lr_item_set_T*)malloc(sizeof(lr_item_set_T));
    set->set = NULL;
    set->size = 0;
    return set;
}

lr_item_set_T *init_lr_item_set_with_item(lr_item_T *item) {
	lr_item_set_T *set = init_lr_item_set();
	add_item(set, item);

    return set;
}

int add_item(lr_item_set_T *set, lr_item_T *item) {
	size_t i;

	for (i = 0; i < set->size; i++) {
		if (lr_item_equals(set->set[i], item)) {
			return 0; 
		}
  	}

  	set->set = (lr_item_T**)realloc(set->set, sizeof(lr_item_T*) * (set->size + 1));
  	set->set[set->size] = item;
 	set->size++;

	return 1;
}

int add_set(lr_item_set_T *set, lr_item_set_T *set_to_add) {
	int added_count = 0, found;
	size_t i, j;

	for (i = 0; i < set_to_add->size; ++i) {
		found = 0;

		for(j = 0; j < set->size; ++j) {
			if(lr_item_equals(set->set[j], set_to_add->set[i])) {
				found = 1;
				break;
			}
		}

		if(!found) {
			set->set = (lr_item_T**)realloc(set->set, sizeof(lr_item_T*) * (set->size + 1));
			set->set[set->size] = set_to_add->set[i];
			set->size++;
			added_count++;
		}
	}

	return added_count;
}

// Closure of Item Sets
//
// If I is a set of items for a grammar G, then CLOSURE(I) is the set of items
// constructed from I by the two rules:
// 1. Initially, add every item in I to CLOSURE(I).
// 2. If A -> a.Bb is in CLOSURE(I) and B ! is a production, then add the
// item B -> .y to CLOSURE(I), if it is not already there.
lr_item_set_T *closure(grammer_T *grammer, lr_item_set_T *items) {
    int changed, found, i, j, k;
    lr_item_set_T *closure_items = init_lr_item_set(); 
    lr_item_T *tmp;


    add_set(closure_items, items);

    do {
        changed = 0;

        // go over all closure items 
        for(i = 0; i < closure_items->size; ++i) {
            for(j = 0; j < grammer->symbols_size; ++j) {

                // if the grammer 
                if(
					closure_items->set[i]->dot_index < closure_items->set[i]->rule->right_size
					&& closure_items->set[i]->rule->right[closure_items->set[i]->dot_index]->sym_type == NON_TERMINAL
					&& grammer->rules[j]->left->type == closure_items->set[i]->rule->right[closure_items->set[i]->dot_index]->symbol->non_terminal->type) {
					
                    found = 0;
                    tmp = init_lr_item(grammer->rules[j], closure_items->set[i]->dot_index, init_token("", TOK_null));
                    for(k = 0; k < closure_items->size; ++k) {
                        if((found = lr_item_equals(closure_items->set[k], tmp))) {
                            break;
                        }
                    }

                    if(!found) {
                        add_item(closure_items, tmp);
                        changed = 1;
                    }   
                }
            }
        }   
    } while(changed);

    return closure_items;
}

lr_item_set_T *closure_lookahead(grammer_T *grammer, lr_item_set_T *items) {
	int changed, found, i, j, k, l;
    lr_item_set_T *closure_items = init_lr_item_set(); 
    lr_item_T *tmp;
	symbol_set_T *first_set;

    add_set(closure_items, items);

    do {
        changed = 0;

        // go over all closure items 
        for(i = 0; i < closure_items->size; ++i) {
            for(j = 0; j < grammer->symbols_size; ++j) {

                if(
					closure_items->set[i]->dot_index < closure_items->set[i]->rule->right_size
					&& closure_items->set[i]->rule->right[closure_items->set[i]->dot_index]->sym_type == NON_TERMINAL
					&& grammer->rules[j]->left->type == closure_items->set[i]->rule->right[closure_items->set[i]->dot_index]->symbol->non_terminal->type) {
					
					first_set = first(grammer, init_symbol_set_with_symbols(&grammer->rules[j]->right[0], 1));

					for(k = 0; k < first_set->size; ++k) {

						found = 0;
						tmp = init_lr_item(grammer->rules[j], closure_items->set[i]->dot_index, first_set->set[k]->symbol->terminal);

						for(l = 0; l < closure_items->size; ++l) {
							printf("\n%d, %s\n", k, first_set->set[k]->symbol->terminal->value);

							if((found = lr_item_equals(closure_items->set[l], tmp))) {
								break;
							}
						}

						if(!found) {
							add_item(closure_items, tmp);
							changed = 1;
						}
					}   
                }
            }
        }   
    } while(changed);

    return closure_items;
}

lr_item_set_T *go_to(grammer_T *grammer, lr_item_set_T *items, symbol_T *symbol) {
	int i;
    lr_item_set_T *goto_items = init_lr_item_set(); 

	for(i = 0; i < items->size; ++i) {
		if(
			items->set[i]->dot_index < items->set[i]->rule->right_size 
			&& symbol_equals(items->set[i]->rule->right[items->set[i]->dot_index], symbol)) {
			add_set(
				goto_items,
				init_lr_item_set_with_item(
					init_lr_item(items->set[i]->rule, items->set[i]->dot_index + 1, init_token("", TOK_null))));
		}
	}
	return closure(grammer, goto_items);
}

lr_item_set_T *lr0_items(grammer_T *grammer, lr_item_T *starting_item) {
    lr_item_set_T *lr0_items = closure(grammer, init_lr_item_set_with_item(starting_item)), *goto_set;
    int changed, i, j, count;

    do {
      	changed = 0;

		for(i = 0; i < lr0_items->size; ++i) {
			for (j = 0; j < grammer->symbols_size; ++j) {
				if(
					(goto_set = go_to(grammer, init_lr_item_set_with_item(lr0_items->set[i]), grammer->symbols[j]))->size != 0				
					&& (count = add_set(lr0_items, goto_set)) != 0
				) {
					changed = 1;
				}	
			}
		}
    } while (changed);

	return lr0_items;
}

lr_item_set_T *lr1_items(grammer_T *grammer, lr_item_T *starting_item) {
	lr_item_set_T *lr1_items = closure_lookahead(grammer, init_lr_item_set_with_item(starting_item)), *goto_set;
    int changed, i, j, count;

    do {
      	changed = 0;

		for(i = 0; i < lr1_items->size; ++i) {
			for (j = 0; j < grammer->symbols_size; ++j) {
				if(
					(goto_set = go_to(grammer, init_lr_item_set_with_item(lr1_items->set[i]), grammer->symbols[j]))->size != 0				
					&& (count = add_set(lr1_items, goto_set)) != 0
				) {
					changed = 1;
				}	
			}
		}
    } while (changed);

	return lr1_items;
}
