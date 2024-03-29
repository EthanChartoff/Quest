#ifndef QUEST_SEMANTIC_ANALYZER_H
#define QUEST_SEMANTIC_ANALYZER_H

#include "../parser/parse_tree.h"

void traverse_parse_tree(parse_tree_node_T *tree, int layer);

#endif