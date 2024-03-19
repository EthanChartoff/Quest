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

set_T *first(const grammer_T *gram, const symbol_T *sym) {
    int i;
    set_T *first_set = set_init(token_cmp_generic);
    set_node_T *cn;
    rule_T *cur_rule;

    // if symbol is term, return it
    if(sym->sym_type == TERMINAL) {
        set_add(first_set, sym->symbol->terminal);
    }
    // sym is non-term
    else {
        cn = gram->rules->head;
        for(i = 0; i < gram->rules->size; ++i) {
            cur_rule = cn->data;
            
            // get rules of symbol and see what is there start symbol 
            if(!non_terminal_cmp(sym->symbol->non_terminal, cur_rule->left)) 
                set_add_all(first_set, first(gram, cur_rule->right[0]));

            cn = cn->next;
        }
    }

    return first_set;
}

set_T *follow(const grammer_T *gram, const non_terminal_T *nt) {
    int i, j;
    set_T *follow_set = set_init(token_cmp_generic);
    set_node_T *cn;
    rule_T *cur_rule;


    if(nt->type == NON_TERM_start)
        set_add(follow_set, init_token("", TOK_eof));

    cn = gram->rules->head;
    for(i = 0; i < gram->rules->size; ++i) { 
        cur_rule = cn->data;

        // get immidiate terminals, meanining terminals in the grammer that follow the nt
        for(j = 0; j < cur_rule->right_size; ++j) {    

            if(cur_rule->right[j]->sym_type == NON_TERMINAL
            && !non_terminal_cmp(nt, cur_rule->right[j]->symbol->non_terminal)
            && j + 1 < cur_rule->right_size) {                
                set_add_all(follow_set, first(gram, cur_rule->right[j + 1]));
            }
        }

        // get non-immidiate terminals, meaning follow of non-terminal ending symbol
        if(cur_rule->right[cur_rule->right_size - 1]->sym_type == NON_TERMINAL 
        && !non_terminal_cmp(cur_rule->right[cur_rule->right_size - 1]->symbol->non_terminal, nt)) {
            set_add_all(follow_set, follow(gram, cur_rule->left));
        }

        cn = cn->next;
    } 

    return follow_set;
}

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
					&& cur_gram_rule->left->type == cur_item->rule->right[cur_item->dot_index]->symbol->non_terminal->type) {
					
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


set_T *lr0_items(grammer_T *grammer, lr_item_T *starting_item) {
    set_T *lr1_items, *goto_set, *tmp = set_init(lr_item_cmp_generic);
	set_T *lr1 = set_init(lr_item_set_cmp_generic);
    set_node_T *cn_item, *cn_sym;
    symbol_T *cur_sym;

    int changed, i, j, count, c;

    set_add(tmp, starting_item);
    lr1_items = closure(grammer, tmp);
	set_add(lr1, lr1_items);
    
    do {
      	changed = 0;

        cn_item = lr1->head;
		for(i = 0; i < lr1->size && cn_item != NULL; ++i) {
            lr1_items = cn_item->data;
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
