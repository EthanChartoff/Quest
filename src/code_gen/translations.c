#include "../include/code_gen/translations.h"
#include "../include/code_gen/nasm_macros.h"
#include "../include/code_gen/register.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *trans_decl(ast_node_T *ast, stack_T *astack, register_T **regs) {
    char *tmp1 = calloc(1, 1);
    if(!tmp1)
        thrw(ALLOC_ERR);
    char *tmp2 = calloc(1, 1);
    if(!tmp2)
        thrw(ALLOC_ERR);
    
    register_T *reg = get_register(regs);
    
    sprintf(tmp1, MOV, REGS_STR[reg->type], ast->children[2]->symbol->symbol->terminal->value);
    sprintf(tmp2, MOV_MEM, ast->children[1]->symbol->symbol->terminal->value, REGS_STR[reg->type]);
    strcat(tmp1, tmp2);

    reg_free(reg);

    return tmp1;
}   

