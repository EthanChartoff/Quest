#ifndef QUEST_SEMANTIC_ANALYZER_H
#define QUEST_SEMANTIC_ANALYZER_H

#include "../parser/parse_tree.h"
#include "../quest.h"
#include "AST.h"
#include "sdt.h"

ast_node_T *build_ast(parse_tree_T *tree, quest_T *q);

#endif