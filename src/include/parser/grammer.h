#ifndef QUEST_GRAMMER_H
#define QUEST_GRAMMER_H

#include "rule.h"
#include <stddef.h>
#include "../lexer/token.h"
#include "symbol.h"

typedef struct GRAMMER_STRUCT {
    rule_T **rules;
    size_t rules_size;
    symbol_T **symbols;
    size_t symbols_size;
} grammer_T;

grammer_T *init_grammer(rule_T **rules, size_t rules_size, symbol_T **symbols, size_t symbols_size);

#endif