#include "../include/code_gen/translation_rule.h"
#include "../utils/err/err.h"

#include <stdlib.h>

translation_rule_T *init_translation_rule(symbol_T *symbol, char *(*translation)(ast_node_T *ast, stack_T *astack, register_T **regs)) {
    translation_rule_T *rule = malloc(sizeof(translation_rule_T));
    if(!rule)
        thrw(ALLOC_ERR);

    rule->symbol = symbol;
    rule->translation = translation;
    return rule;   
}