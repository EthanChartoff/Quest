#ifndef QUEST_PARSE_TREE_NODE_H
#define QUEST_PARSE_TREE_NODE_H

#include "rule.h"
#include "symbol.h"
#include <stddef.h>
#include <sys/types.h>

typedef struct PARSE_TREE_NODE_STRUCT {
    symbol_T *symbol;                           // symbol in curr node on parse tree
    ssize_t rule_index;                         // index of rule in rules arr (or -1 indicating that it has no rule where its in the ledt side)
    struct PARSE_TREE_NODE_STRUCT **children;   // arr of children of parse tree node 
    size_t n_children;                          // number of children the node has
} parse_tree_node_T;

typedef struct PARSE_TREE_STRUCT {
    parse_tree_node_T *root;    // root node of parse tree
    rule_T **rules;             // array of all rules. in array so getting of rule is theta(1);
    size_t n_rules;             // number of rules
} parse_tree_T;

parse_tree_T *init_parse_tree(parse_tree_node_T *root, rule_T **rules, size_t n_rules);

parse_tree_node_T *init_parse_tree_node(symbol_T *sym, ssize_t rule_index, parse_tree_node_T **children, size_t n_children);
parse_tree_node_T *init_parse_tree_leaf(symbol_T *sym);

void parse_tree_traverse_preorder(parse_tree_node_T *tree, int layer);
void parse_tree_traverse_postorder(parse_tree_node_T *tree, int layer);




#endif /* QUEST_PARSE_TREE_NODE_H */