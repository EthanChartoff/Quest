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
#include "non_terminal.h"
#include "symbol.h"
#include <stddef.h>

typedef struct RULE_STRUCT {
    non_terminal_T *left;
    symbol_T **right;
    size_t right_size;
} rule_T;

rule_T *init_rule(non_terminal_T *left, symbol_T **right, size_t right_size);

int rule_cmp(const rule_T *rule1, const rule_T *rule2);
int rule_cmp_generic(const void *rule1, const void *rule2);

int find_first_nt(const rule_T *rule, int offset);


#endif