//===--= semantic_rule.h =--------------------------------------------===
//
// a semantic rule 
//
//===-----------------------------------------------------------------===

#ifndef QUEST_SEMANTIC_RULE_H
#define QUEST_SEMANTIC_RULE_H

#include "../parser/parse_tree.h"
#include "../../utils/DS/include/stack.h"
#include "AST.h"

typedef struct SEMANTIC_RULE_STRUCT {
    rule_T *rule;                                                           // production rule, for example, E -> E + T
    ast_node_T *(*definition)(parse_tree_node_T *pn, stack_T *astack);   // definition of rule, for example. E.val = E1.val + T.val, implemented by function ptr
} semantic_rule_T;

semantic_rule_T *init_sementic_rule(rule_T *rule, ast_node_T *(*definition)(parse_tree_node_T *pn, stack_T *astack));

#endif /* QUEST_SEMANTIC_RULE_H */