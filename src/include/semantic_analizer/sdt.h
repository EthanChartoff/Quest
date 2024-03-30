#ifndef QUEST_SDT_H
#define QUEST_SDT_H

#include "../../utils/DS/include/generic_set.h"
#include "semantic_rule.h"

typedef struct SDT_STRUCT {
    semantic_rule_T **definitions;
    size_t n_defenitions;
} sdt_T;

sdt_T *init_sdt(semantic_rule_T **definitions, size_t n_defenitions);
sdt_T *init_default_sdt(rule_T **rules, size_t n_rules);

#endif /* QUEST_SDT_H */
