#include "../include/code_gen/code_generator.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

code_gen_T *init_code_gen(register_T **registers, char *dest) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->dest = dest;
    cg->registers = registers;
    cg->output = NULL;

    return cg;
}

code_gen_T *init_code_gen_default(char *dest) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->dest = dest;
    cg->registers = malloc(sizeof(register_T *) * NUM_REG);
    if(!cg->registers)
        thrw(ALLOC_ERR);
    memcpy(cg->registers, NASM_REGS, sizeof(register_T *) * NUM_REG);
    cg->output = NULL;

    return cg;
}

char *generate_code(ast_node_T *ast) {
    code_gen_T *cg = init_code_gen_default("/home/goodman/school/Quest/tests");
    stack_T *astack = stack_init();
    
}

register_T *code_gen_get_register(code_gen_T *cg) {
    for(int i = 0; i < NUM_REG; ++i) {
        if(!cg->registers[i]->is_used && !cg->registers[i]->is_preserved) {
            return cg->registers[i];
        }
    }

    return NULL;
}

void code_gen_print_to_file(code_gen_T *cg, char *dest) {
    FILE *fp = fopen(dest, "w");
    
    fprintf(fp, "%s", cg->output);
    fclose(fp);

    return;
}