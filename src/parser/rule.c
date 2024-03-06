#include "../include/parser/rule.h"
#include <stdio.h>
#include <stdlib.h>

// initialize rule using tokens
rule_T *init_rule(token_T *left, token_T **right, size_t right_size) {
    rule_T *rule = malloc(sizeof(rule_T));

    if(!rule) {
        printf("cant allocate memory fir rule");
        exit(EXIT_FAILURE);
    }

    rule->left = left;
    rule->right = right;
    rule->right_size = right_size;

    return rule;
}

int rule_compare(const rule_T *rule1, const rule_T *rule2) {
    int i;

    if(rule1->left->type == rule2->left->type && rule1->right_size == rule2->right_size) {
        for(i = 0; i < rule1->right_size; ++i) {
            if(rule1->right[i]->type != rule2->right[i]->type)
                return 0;
        }
        return 1;
    }
    return 0;
}