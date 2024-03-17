#include "../include/parser/lr_item.h"
#include "../include/macros.h"
#include <stdio.h>
#include <stdlib.h>


lr_item_T *init_lr_item(rule_T *rule, size_t dot_index, set_T *lookaheads) {
    lr_item_T *item = malloc(sizeof(lr_item_T));
    
    item->rule = rule;
    item->dot_index = dot_index;
    item->lookaheads = lookaheads;

    return item;
}

int lr_item_cmp(const lr_item_T *item1, const lr_item_T *item2) {
    int delta, i;
    set_node_T *cur1, *cur2;
    
    delta = rule_cmp(item1->rule, item2->rule);
    IF_SIGN(delta)

    delta = item1->dot_index - item2->dot_index;
    IF_SIGN(delta);

    // delta = item1->lookaheads->size - item2->lookaheads->size;
    // IF_SIGN(delta);

    // cur1 = item1->lookaheads->head;
    // cur2 = item2->lookaheads->head;

    // for (i = 0; i < item1->lookaheads->size; ++i) {
    //     delta =  token_cmp_generic(cur1->data, cur2->data);
    //     IF_SIGN(delta);

    //     cur1 = cur1->next;
    //     cur2 = cur2->next;
    // }

    return 0;
}

int lr_item_cmp_generic(const void *item1, const void *item2) {
    return lr_item_cmp((const lr_item_T *) item1, (const lr_item_T *) item2);
}

int lr_item_set_cmp(const set_T *set1, const set_T *set2) {
    int i, delta;
    set_node_T *cur_set1, *cur_set2;
    
    delta = set1->size - set2->size;
    IF_SIGN(delta);

    cur_set1 = set1->head;
    cur_set2 = set2->head;
    for(i = 0; i < set1->size; ++i) {
        delta = lr_item_cmp_generic(cur_set1->data, cur_set2->data);
        IF_SIGN(delta);

        cur_set1 = cur_set1->next;
        cur_set2 = cur_set2->next;

    }

    return 0;
}

int lr_item_set_cmp_generic(const void *item1, const void *item2) {
    return lr_item_set_cmp((const set_T *) item1, (const set_T *) item2);
}


// set_T *first(const grammer_T *gram, const symbol_T **syms, const size_t size) {
//     int i, j, k, no_null;
//     set_T *first_set = set_init(token_cmp_generic), *tmp, *right_set;
//     set_node_T *cn_rule, *cn_tmp;
//     symbol_T *cur_sym; 
//     rule_T *cur_rule;
//     token_T *cur_tmp;

//     for(i = 0; i < size; ++i) {

//         // symbol is terminal
//         if(syms[i]->sym_type == TERMINAL) {
//             set_add(first_set, syms[i]->symbol->terminal);
//             // return first_set;
//         }

//         else {
            
//         }
            
//     }
//     return first_set;
// }


// Closure of Item Sets
//
// If I is a set of items for a grammar G, then CLOSURE(I) is the set of items
// constructed from I by the two rules:
// 1. Initially, add every item in I to CLOSURE(I).
// 2. If A -> a.Bb is in CLOSURE(I) and B ! is a production, then add the
// item B -> .y to CLOSURE(I), if it is not already there.
set_T *closure(grammer_T *grammer, set_T *items) {
    int changed_c, found, i, j, k;
    set_T *closure_items = set_init(lr_item_cmp_generic); 
    set_node_T *cn_closure_item, *cn_gram_rule;
    lr_item_T *tmp, *cur_item; 
    rule_T *cur_gram_rule;


    set_add_all(closure_items, items);

    do {
        changed_c = 0;
        cn_closure_item = closure_items->head;
        // go over all closure items 
        for(i = 0; i < closure_items->size && cn_closure_item != NULL; ++i) {
            cur_item = cn_closure_item->data;

            cn_gram_rule = grammer->rules->head;
            for(j = 0; j < grammer->rules->size; ++j) {   
                cur_gram_rule = cn_gram_rule->data;

                if(
					cur_item->dot_index < cur_item->rule->right_size
					&& (k = find_first_nt(cur_item->rule, cur_item->dot_index)) != -1
					&& cur_gram_rule->left->type == cur_item->rule->right[k]->symbol->non_terminal->type) {
					
                    changed_c += set_add(
                        closure_items, 
                        init_lr_item(
                            cur_gram_rule, 
                            0, 
                            NULL
                        )
                    );
                }
                cn_gram_rule = cn_gram_rule->next;
            }
            cn_closure_item = cn_closure_item->next;
        }   
    } while(changed_c);

    return closure_items;
}

set_T *go_to(grammer_T *grammer, set_T *items, symbol_T *symbol) {
	int i;
    set_T *goto_items = set_init(lr_item_cmp_generic); 
    set_node_T *cn_closure_item;
    lr_item_T *tmp, *cur_item; 

    cn_closure_item = items->head;
	for(i = 0; i < items->size && cn_closure_item != NULL; ++i) {
        cur_item = cn_closure_item->data;
        
		if(
			cur_item->dot_index < cur_item->rule->right_size 
			&& symbol_equals(cur_item->rule->right[cur_item->dot_index], symbol)) {
                    
                set_add(
                    goto_items,
                    init_lr_item(cur_item->rule, cur_item->dot_index + 1, NULL)
                );
		}
        cn_closure_item = cn_closure_item->next;

	}
	return closure(grammer, goto_items);
}


// set_T *closure_lookahead(grammer_T *grammer, set_T *items) {
// 	int changed_c, changed, i, j, k;
//     set_T *closure_items = set_init(lr_item_cmp_generic), *first_set; 
//     set_node_T *cn_closure_item, *cn_gram_rule;
//     lr_item_T *tmp, *cur_item; 
//     rule_T *cur_gram_rule;

//     set_add_all(closure_items, items);

//     do {
//         changed_c = 0;
//         cn_closure_item = closure_items->head;

//         // go over all closure items 
//         for(i = 0; i < closure_items->size && cn_closure_item != NULL; ++i) {
//             cur_item = cn_closure_item->data;

//             cn_gram_rule = grammer->rules->head;
//             for(j = 0; j < grammer->rules->size; ++j) {
//                 cur_gram_rule = cn_gram_rule->data;
//                 if(
// 					cur_item->dot_index < cur_item->rule->right_size
//                     && (k = find_first_nt(cur_item->rule, cur_item->dot_index)) != -1
// 					&& cur_gram_rule->left->type == cur_item->rule->right[k]->symbol->non_terminal->type) {
                    
//                         tmp = init_lr_item(
//                             cur_gram_rule, 
//                             0, 
//                             cur_item->lookaheads);
//                         changed_c += set_add(closure_items, tmp);
//                 }
//                 cn_gram_rule = cn_gram_rule->next;
//             }
//             cn_closure_item = cn_closure_item->next;
//         }   
//     } while(changed_c);

//     return closure_items;
// }

// set_T *go_to_lookahead(grammer_T *grammer, set_T *items, symbol_T *symbol) {
// 	int i;
//     set_T *goto_items = set_init(lr_item_cmp_generic); 
//     set_node_T *cn_closure_item;
//     lr_item_T *tmp, *cur_item; 

//     cn_closure_item = items->head;


// 	for(i = 0; i < items->size && cn_closure_item != NULL; ++i) {

//         cur_item = cn_closure_item->data;

// 		if(
// 			cur_item->dot_index < cur_item->rule->right_size 
// 			&& symbol_equals(cur_item->rule->right[cur_item->dot_index], symbol)) {  

//                 set_add(
//                 goto_items,		
//                 init_lr_item(cur_item->rule, cur_item->dot_index + 1, first(grammer, cur_item->rule->right, cur_item->rule->right_size)));
// 		}
//         cn_closure_item = cn_closure_item->next;
// 	}

// 	return closure_lookahead(grammer, goto_items);
// }


set_T *lr0_items(grammer_T *grammer, lr_item_T *starting_item) {
    set_T *lr1_items, *goto_set, *tmp = set_init(lr_item_cmp_generic);
	set_T *lr1 = set_init(lr_item_set_cmp_generic);
    set_node_T *cn_item, *cn_sym;
    symbol_T *cur_sym;
    lr_item_T *itm_itm_itm;

    int changed, i, j, count, c;

    set_add(tmp, starting_item);
    lr1_items = closure(grammer, tmp);
	set_add(lr1, lr1_items);
    
    do {
      	changed = 0;

        cn_item = lr1->head;
		for(i = 0; i < lr1->size && cn_item != NULL; ++i) {
            cn_sym = grammer->symbols->head;
			for (j = 0; j < grammer->symbols->size; ++j) {
                cur_sym = cn_sym->data;
                
				if(
					(goto_set = go_to(grammer, lr1_items, cur_sym))->size != 0				
					&& (count = set_add(lr1, goto_set)) != 0
				) {
					changed = 1;
				}	
                cn_sym = cn_sym->next;
			}
            cn_item = cn_item->next;
		}
    } while (changed);


	return lr1;
}

// set_T *lr1_items(grammer_T *grammer, lr_item_T *starting_item) {
// 	set_T *lr1_items, *goto_set, *tmp = set_init(lr_item_cmp_generic);
// 	set_T *lr1 = set_init(lr_item_set_cmp_generic);
//     set_node_T *cn_item, *cn_sym;
//     symbol_T *cur_sym;
//     lr_item_T *itm_itm_itm;

//     int changed, i, j, count, c;

//     set_add(tmp, starting_item);
//     lr1_items = closure_lookahead(grammer, tmp);
// 	set_add(lr1, lr1_items);
    
//     do {
//       	changed = 0;

//         cn_item = lr1->head;
// 		for(i = 0; i < lr1->size && cn_item != NULL; ++i) {
//             lr1_items = cn_item->data;

//             cn_sym = grammer->symbols->head;
// 			for (j = 0; j < grammer->symbols->size; ++j) {
//                 cur_sym = cn_sym->data;
// 				if(
// 					(goto_set = go_to_lookahead(grammer, lr1_items, cur_sym))->size != 0				
// 					&& (count = set_add(lr1, goto_set)) != 0
// 				) {
// 					changed = 1;
// 				}	
//                 cn_sym = cn_sym->next;
// 			}
//             cn_item = cn_item->next;
// 		}
//     } while (changed);


// 	return lr1;
// }

// set_T *lalr_items(grammer_T *grammer, lr_item_T *starting_item) {
//     int *flags, i;

//     // Construct lr1
//     set_T *lr1 = lr1_items(grammer, starting_item);
    
//     flags = calloc(lr1->size, sizeof(int));
//     // For each core present among the set of LR(1) items, find all sets having
//     // that core, and replace these sets by their union

// }
