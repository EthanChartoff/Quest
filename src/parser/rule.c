#include "../include/parser/rule.h"
#include <stdio.h>
#include <stdlib.h>


// initialize rule using tokens
rule_T *init_rule(non_terminal_T *left, symbol_T **right, size_t right_size) {
    rule_T *rule = malloc(sizeof(rule_T));

    if(!rule) {
        printf("cant allocate memory for rule");
        exit(EXIT_FAILURE);
    }

    rule->left = left;
    rule->right = right;
    rule->right_size = right_size;

    return rule;
}

int rule_equals(const rule_T *rule1, const rule_T *rule2) {
    int i;

    if(
        rule1->left->type == rule2->left->type 
        && rule1->right_size == rule2->right_size
    ) {
        for(i = 0; i < rule1->right_size; ++i) {
            if(!symbol_equals(rule1->right[i], rule2->right[i]))
                return 0;
        }
        
        return 1;
    }
    return 0;
}