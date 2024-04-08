#include "../include/semantic_analizer/semantic_rule.h"

#include <stdlib.h>


semantic_rule_T *init_sementic_rule(rule_T *rule, void (*definition)(stack_T *astack, parse_tree_node_T *tree, symbol_table_T *sym_tbl)) {
    semantic_rule_T *sr = malloc(sizeof(semantic_rule_T));

    sr->rule = rule;
    sr->definition = definition;

    return sr;
}