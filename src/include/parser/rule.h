//===--= Rule.h =-------------------------------------===
//
// A grammer rule. (add a rule explanation and grammer and maybe example)  
//
//
// 
//
//===------------------------------------------------===

#ifndef QUEST_RULE_H
#define QUEST_RULE_H

#include "../lexer/token.h"
#include <stddef.h>

typedef struct RULE_STRUCT {
    token_T *left;
    token_T **right;
    size_t right_size;
} rule_T;

rule_T *init_rule(token_T *left, token_T **right, size_t right_size);
int rule_compare(const rule_T *rule1, const rule_T *rule2);

#endif