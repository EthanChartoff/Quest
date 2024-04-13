//===--= translations.h =----------------------------------------------------===
//
// here are all the translations that are used in the code generator,
// they are stored in the translation table and each translation correlates to 
// a pattern in the AST
//
//===------------------------------------------------------------------------===

#ifndef QUEST_TRANSLATIONS_H
#define QUEST_TRANSLATIONS_H

#include "../semantic_analizer/AST.h"
#include "register.h"
#include "../../utils/DS/include/stack.h"

void trans_decl(ast_node_T *ast, stack_T *astack, register_T **regs);
void trans_mov(ast_node_T *ast, stack_T *astack, register_T **regs);

#endif /* QUEST_TRANSLATIONS_H */