#include "../include/parser/rule.h"
#include "../include/macros.h"
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

int rule_cmp(const rule_T *rule1, const rule_T *rule2) {
    int i, delta;

    delta = rule1->left->type - rule2->left->type;
    IF_SIGN((delta));

    
    delta = rule1->right_size - rule2->right_size;
    IF_SIGN(delta);

    for(i = 0; i < rule1->right_size; ++i) {
        delta = rule1->right[i] - rule2->right[i];
        IF_SIGN(delta);
    }

    return 0;
}

int rule_cmp_generic(const void *rule1, const void *rule2) {
    return rule_cmp((const rule_T *) rule1, (const rule_T *) rule2);
}

int find_first_nt(const rule_T *rule, int offset) {
    int i;

    for(i = offset; i < rule->right_size; ++i) {
        if(rule->right[i]->sym_type == NON_TERMINAL)
            return i;
    }
    return -1;
}