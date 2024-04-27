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

// tok
char *trans_num_const(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_id(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_plus(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_minus(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_assign(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_greater(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_less(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);


// nt
char *trans_decl(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_selection_stmt(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);
char *trans_iteration_stmt(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs);

#endif /* QUEST_TRANSLATIONS_H */