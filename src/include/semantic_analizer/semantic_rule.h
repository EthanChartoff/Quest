//===--= semantic_rule.h =--------------------------------------------===
//
// a semantic rule 
//
//===-----------------------------------------------------------------===

#ifndef QUEST_SEMANTIC_RULE_H
#define QUEST_SEMANTIC_RULE_H

#include "../parser/rule.h"

typedef struct SEMANTIC_RULE_STRUCT {
    rule_T *rule;                       // production rule, for example, E -> E + T
    void (*definition)(int argc, ...);  // definition of rule, for example. E.val = E1.val + T.val, implemented by function ptr
    int argc;                           // arguments definition takes
} semantic_rule_T;

semantic_rule_T *init_sementic_rule(rule_T *rule, void (*definition)(int argc, ...), int argc);

#endif /* QUEST_SEMANTIC_RULE_H */