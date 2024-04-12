#include "../include/code_gen/code_generator.h"
#include "../include/code_gen/nasm_macros.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char *generate_global_variables(code_gen_T *cg) {
    int i;
    symbol_table_entry_T *cur;
    char *tmp;

    cg->output = realloc(cg->output, strlen(cg->output) + strlen(DATA) + 1);
    strcat(cg->output, DATA);

    for(i = 0; i < cg->sym_tbl->root->table->capacity; ++i) {
        cur = cg->sym_tbl->root->table->buckets[i];

        while(cur) {
            tmp = malloc(strlen(DQ) + strlen(cur->name) + 1);

            switch (cur->type) {
                case TOK_INT:
                    sprintf(tmp, DQ, cur->name);
                    strcat(cg->output, tmp);
                    break;

                case TOK_CHAR:
                    sprintf(tmp, DB, cur->name);
                    strcat(cg->output, tmp);
                    break;

                default:
                    break;
            }

            cur = cur->next;
        }   
    }
    
    return cg->output;
}

static void generate_code_rec(ast_node_T *ast, stack_T *astack, code_gen_T *cg) {
    if(!ast)
        return;
    
    int i;
    for(i = 0; i < ast->n_children; ++i) {
        generate_code_rec(ast->children[i], astack, cg);
    }    
}   

code_gen_T *init_code_gen(register_T **registers, tts_T *tts, symbol_table_tree_T *sym_tbl, char *dest) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->dest = dest;
    cg->registers = registers;
    cg->tts = tts;
    cg->sym_tbl = sym_tbl;
    cg->output = malloc(sizeof(char));
    if(!cg->output)
        thrw(ALLOC_ERR);
    cg->output[0] = '\0';

    return cg;
}

code_gen_T *init_code_gen_default(char *dest, tts_T *tts, symbol_table_tree_T *sym_tbl) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->dest = dest;
    cg->registers = malloc(sizeof(register_T *) * NUM_REG);
    if(!cg->registers)
        thrw(ALLOC_ERR);
    memcpy(cg->registers, NASM_REGS, sizeof(register_T *) * NUM_REG);
    cg->tts = tts;
    cg->sym_tbl = sym_tbl;
    cg->output = malloc(sizeof(char));
    if(!cg->output)
        thrw(ALLOC_ERR);
    cg->output[0] = '\0';

    return cg;
}

char *generate_code(ast_node_T *ast, code_gen_T *cg) {
    stack_T *astack = stack_init();
    
    return generate_global_variables(cg);
    // generate_code_rec(ast, astack, cg);
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
