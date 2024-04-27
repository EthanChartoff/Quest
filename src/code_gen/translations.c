#include "../include/code_gen/translations.h"
#include "../include/code_gen/nasm_macros.h"
#include "../include/code_gen/register.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *alloc_instruction_mem() {
    char *tmp = malloc(1);
    *tmp = '\0';
    if(!tmp)
        thrw(ALLOC_ERR);

    return tmp;
}

static char *reverse_code(char *code) {
    stack_T *code_stack = stack_init();
    char *tmp = strtok(code, "\n");

    while(tmp) {
        stack_push(code_stack, strdup(tmp));
        tmp = strtok(NULL, "\n");
    }

    free(code);
    code = calloc(1, 1);
    while(!IS_EMPTY(code_stack)) {
        tmp = stack_pop(code_stack);
        code = realloc(code, strlen(code) + strlen(tmp) + 2);
        strcat(code, tmp);
        strcat(code, "\n");
    }

    return code;
}


char *trans_num_const(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg = get_register(regs, DATA, DWORD);  // TODO: maybe have access to paren to see type size? or have symbols have types
    sprintf(tmp, MOV, reg->name, ast->symbol->symbol->terminal->value);
    stack_push(astack, reg);

    return tmp;
}

char *trans_id(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg = get_register(regs, DATA, DWORD); 
    sprintf(tmp, MOV_REG_TYPE, reg->name, ast->symbol->symbol->terminal->value);
    stack_push(astack, reg);

    return tmp;
}

char *trans_plus(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg2 = stack_pop(astack);
    register_T *reg1 = stack_pop(astack);

    sprintf(tmp, ADD, reg1->name, reg2->name);
    stack_push(astack, reg1);
    reg_free(regs, reg2);

    return tmp;
}

char *trans_minus(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();

    register_T *reg2 = stack_pop(astack);
    register_T *reg1 = stack_pop(astack);

    sprintf(tmp, SUB, reg1->name, reg2->name);
    stack_push(astack, reg1);
    reg_free(regs, reg2);

    return tmp;
}

char *trans_assign(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();
    
    register_T *reg_const = stack_pop(astack);
    reg_free(regs, stack_pop(astack));

    sprintf(tmp, MOV_MEM_TYPE, SIZE_TO_STR(reg_const->size), ast->children[0]->symbol->symbol->terminal->value, reg_const->name);
    reg_free(regs, reg_const);

    return tmp;
}

char *trans_greater(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp1 = alloc_instruction_mem();
    char *tmp2 = alloc_instruction_mem();

    register_T *reg1 = stack_pop(astack);
    register_T *reg2 = stack_pop(astack);
    
    sprintf(tmp1, CMP, reg2->name, reg1->name);
    reg_free(regs, reg1);
    reg_free(regs, reg2);

    reg1 = get_register(regs, DATA, BYTE);
    sprintf(tmp2, SETG, reg1->name);
    strcat(tmp1, tmp2);
    stack_push(astack, reg1);

    free(tmp2);
    return strdup(reverse_code(tmp1));
}

char *trans_less(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp1 = alloc_instruction_mem();
    char *tmp2 = alloc_instruction_mem();
    register_T *reg1 = stack_pop(astack);
    register_T *reg2 = stack_pop(astack);

    sprintf(tmp1, CMP, reg2->name, reg1->name);
    reg_free(regs, reg1);
    reg_free(regs, reg2);

    reg1 = get_register(regs, DATA, BYTE);
    sprintf(tmp2, SETL, reg1->name);
    strcat(tmp1, tmp2);
    stack_push(astack, reg1);

    free(tmp2);
    return strdup(reverse_code(tmp1));
}


char *trans_decl(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp = alloc_instruction_mem();
    
    register_T *reg_const = stack_pop(astack);
    reg_free(regs, stack_pop(astack));

    sprintf(tmp, MOV_MEM_TYPE, SIZE_TO_STR(reg_const->size), ast->children[1]->symbol->symbol->terminal->value, reg_const->name);
    reg_free(regs, reg_const);

    return tmp;
}   

char *trans_selection_stmt(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp1 = alloc_instruction_mem();
    char *tmp2 = alloc_instruction_mem();
    char *tmp3 = alloc_instruction_mem();
    char *tmp4 = alloc_instruction_mem();
    char *tmp5 = alloc_instruction_mem();

    char *tmp_exp = NULL;
    char *tmp_if = NULL;
    char *tmp_else = NULL;

    register_T *reg_exp = stack_pop(astack);

    // // if without else
    if(ast->n_children == 2) {
        tmp_if = stack_pop(code_stack);
        tmp_exp = stack_pop(code_stack);

        sprintf(tmp1, CMP, reg_exp->name, "0");
        sprintf(tmp2, JZ, "end_if");
        sprintf(tmp3, LABEL("end_if"));

        tmp3 = realloc(tmp3, strlen(tmp_exp) + strlen(tmp1) + strlen(tmp2) + strlen(tmp_if) + strlen(tmp3) + 1);
        strcat(tmp3, tmp_if);
        strcat(tmp3, tmp2);
        strcat(tmp3, tmp1);
        strcat(tmp3, tmp_exp);

        tmp5 = strdup(tmp3);
    }
    // if with else
    else if(ast->n_children == 3) {
        tmp_else = stack_pop(code_stack);
        tmp_if = stack_pop(code_stack);
        tmp_exp = stack_pop(code_stack);

        sprintf(tmp1, CMP, reg_exp->name, "0");
        sprintf(tmp2, JZ, "else");
        sprintf(tmp3, JMP, "end");
        sprintf(tmp4, LABEL("else"));
        sprintf(tmp5, LABEL("end"));

        tmp5 = realloc(tmp5, strlen(tmp_else) + strlen(tmp4) + strlen(tmp3) + strlen(tmp2) + strlen(tmp1) + strlen(tmp_exp) + strlen(tmp5) + 1);
        strcat(tmp5, strdup(tmp_else));
        strcat(tmp5, tmp4);
        strcat(tmp5, tmp3);
        strcat(tmp5, strdup(tmp_if));
        strcat(tmp5, tmp2);
        strcat(tmp5, tmp1);
        strcat(tmp5, strdup(tmp_exp));
    }
    
    free(tmp1);
    free(tmp2);
    free(tmp3);
    free(tmp4);
    free(tmp_exp);
    free(tmp_if);
    free(tmp_else);
    

    reg_free(regs, reg_exp);
    return tmp5;
}

char *trans_iteration_stmt(ast_node_T *ast, stack_T *astack, stack_T *code_stack, register_pool_T **regs) {
    char *tmp1 = alloc_instruction_mem();
    char *tmp2 = alloc_instruction_mem();
    char *tmp3 = alloc_instruction_mem();
    char *tmp4 = alloc_instruction_mem();
    char *tmp5 = alloc_instruction_mem();

    char *tmp_while = stack_pop(code_stack);
    char *tmp_exp = stack_pop(code_stack);

    register_T *reg_exp = stack_pop(astack);

    sprintf(tmp1, LABEL("loop"));
    sprintf(tmp2, CMP, reg_exp->name, "0");
    sprintf(tmp3, JZ, "end_loop");
    sprintf(tmp4, JMP, "loop");
    sprintf(tmp5, LABEL("end_loop"));

    // printf("%s\n", tmp_while);

    tmp5 = realloc(tmp5, strlen(tmp_while) + strlen(tmp4) + strlen(tmp3) + strlen(tmp2) + strlen(tmp1) + strlen(tmp_exp) + strlen(tmp5) + 1);
    strcat(tmp5, tmp_exp);
    strcat(tmp5, tmp4);
    strcat(tmp5, tmp3);
    strcat(tmp5, tmp2);
    strcat(tmp5, tmp1);
    strcat(tmp5, tmp_while);

    free(tmp1);
    free(tmp2);
    free(tmp3);
    free(tmp4);

    reg_free(regs, reg_exp);

    return tmp5;
}
