#ifndef QUEST_TRANSLATION_RULE_H
#define QUEST_TRANSLATION_RULE_H

#include "../parser/symbol.h"
#include "../semantic_analizer/AST.h"
#include "../../utils/DS/include/stack.h"

typedef struct TRANSLATION_RULE_STRUCT {
    symbol_T *symbol;
    char *translation;
} translation_rule_T;

translation_rule_T *init_translation_rule(symbol_T *symbol, char *translation);


#endif /* QUEST_TRANSLATION_RULE_H */