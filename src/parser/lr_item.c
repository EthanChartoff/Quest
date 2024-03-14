#include "../include/parser/lr_item.h"
#include <stdio.h>
#include <stdlib.h>


lr_item_T *init_lr_item(rule_T *rule, size_t dot_index, token_T *lookahead) {
    lr_item_T *item = malloc(sizeof(lr_item_T));
    
    item->rule = rule;
    item->dot_index = dot_index;
    item->lookahead = lookahead;

    return item;
}

int lr_item_equals(const lr_item_T *item1, const lr_item_T *item2) {
    int flag = 1;

    if(item1->lookahead == NULL)
        flag = item2->lookahead == NULL ? 1 : 0;
    

    if(flag && item1->lookahead->type == item2->lookahead->type)
        flag = 1;
    else 
        flag = 0;


    return rule_equals(item1->rule, item2->rule) 
            && item1->dot_index == item2->dot_index
            && flag;  
}

symbol_set_T *first(const grammer_T *gram, const symbol_set_T *syms) {
    int i, j, k, no_null;
    symbol_set_T *first_set = init_symbol_set(), *tmp;

    for(i = 0; i < syms->size; ++i) {

        // symbol is terminal
        if(syms->set[i]->sym_type == TERMINAL) {
            add_symbol(first_set, syms->set[i]);
            return first_set;
        }

        // symbol is non-terminal
        for(j = 0; j < gram->rules_size; ++j) {
            if(gram->rules[j]->left == syms->set[i]->symbol->non_terminal) {
                tmp = first(gram, init_symbol_set_with_symbols(gram->rules[j]->right, gram->rules[j]->right_size));
                no_null = 1;

                for(k = 0; k < tmp->size; ++k) {
                    if(tmp->set[k]->symbol->terminal->type == TOK_null)
                        no_null = 0;
                    else {
                        add_symbol(first_set, tmp->set[k]);
                    }
                }

                if(no_null || j + 1 == gram->rules_size)
                    break;
            }
        }
    }
    return first_set;
}