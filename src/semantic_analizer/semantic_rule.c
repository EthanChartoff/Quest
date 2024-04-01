#include "../include/semantic_analizer/semantic_rule.h"

#include <stdlib.h>


semantic_rule_T *init_sementic_rule(rule_T *rule, ast_node_T *(*definition)(parse_tree_node_T *pn, stack_T *astack)) {
    semantic_rule_T *sr = malloc(sizeof(semantic_rule_T));

    sr->rule = rule;
    sr->definition = definition;

    return sr;
}