#ifndef QUEST_GRAMMER_H
#define QUEST_GRAMMER_H

#include "rule.h"
#include "symbol.h"
#include "../lexer/token.h"
#include "../../utils/DS//include/generic_set.h"

typedef struct GRAMMER_STRUCT {
    set_T *rules;
    set_T *symbols;
} grammer_T;

grammer_T *init_grammer(set_T *rules, set_T *symbols);

#endif