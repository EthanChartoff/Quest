#include "../include/code_gen/translations.h"
#include "../include/code_gen/nasm_macros.h"
#include "../include/code_gen/register.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>

static char *alloc_instruction_mem() {
    char *tmp = calloc(1, 1);
    if(!tmp)
        thrw(ALLOC_ERR);

    return tmp;
}

char *trans_num_const(ast_node_T *ast, stack_T *astack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg = get_register(regs, DATA, DWORD);  // TODO: maybe have access to paren to see type size? or have symbols have types
    sprintf(tmp, MOV, reg->name, ast->symbol->symbol->terminal->value);
    stack_push(astack, reg);

    return tmp;
}

char *trans_plus(ast_node_T *ast, stack_T *astack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg1 = stack_pop(astack);
    register_T *reg2 = stack_pop(astack);

    sprintf(tmp, ADD, reg1->name, reg2->name);
    stack_push(astack, reg1);
    reg_free(regs, reg2);

    return tmp;
}

char *trans_minus(ast_node_T *ast, stack_T *astack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg1 = stack_pop(astack);
    register_T *reg2 = stack_pop(astack);

    sprintf(tmp, SUB, reg1->name, reg2->name);
    stack_push(astack, reg1);
    reg_free(regs, reg2);

    return tmp;
}

char *trans_decl(ast_node_T *ast, stack_T *astack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();
    
    register_T *reg_const = stack_pop(astack);

    sprintf(tmp, MOV_MEM_TYPE, SIZE_TO_STR(reg_const->size), ast->children[1]->symbol->symbol->terminal->value, reg_const->name);
    reg_free(regs, reg_const);

    return tmp;
}   

char *trans_selection_stmt(ast_node_T *ast, stack_T *astack, register_pool_T **regs);



