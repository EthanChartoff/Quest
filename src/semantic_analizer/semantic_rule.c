#include "../include/semantic_analizer/semantic_rule.h"

#include <stdlib.h>


semantic_rule_T *init_sementic_rule(rule_T *rule, void (*definition)(int argc, ...), int argc) {
    semantic_rule_T *sr = malloc(sizeof(semantic_rule_T));

    sr->rule = rule;
    sr->definition = definition;
    sr->argc = argc;
}