#include "../include/code_gen/code_generator.h"
#include "../include/code_gen/nasm_macros.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static register_T **copy_nasm_regs() {
    register_T **tmp = malloc(sizeof(register_T *) * NUM_REG);
    if(!tmp)
        thrw(ALLOC_ERR);

    for(int i = 0; i < NUM_REG; ++i) {
        tmp[i] = malloc(sizeof(register_T));
        if(!tmp[i])
            thrw(ALLOC_ERR);

        *tmp[i] = NASM_REGS[i];
    }
    return tmp;
}

static void generate_text_section(code_gen_T *cg) {
    cg->output = realloc(cg->output, strlen(cg->output) + strlen(TEXT) + strlen(GLOBAL("_start")) + strlen(LABEL("_start")) + 1);
    strcat(cg->output, TEXT);
    strcat(cg->output, GLOBAL("_start"));
    strcat(cg->output, LABEL("_start"));    
}

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

static void generate_code_rec(ast_node_T *ast, stack_T *astack, tts_T *tts, register_T **regs) {
    if(!ast)
        return;
    
    int i;
    for(i = 0; i < ast->n_children; ++i) {
        generate_code_rec(ast->children[i], astack, tts, regs);
    }

    if(ast->symbol->sym_type == TERMINAL) {
        if(tts->tok_translation[ast->symbol->symbol->terminal->type])
            tts->tok_translation[ast->symbol->symbol->terminal->type]->translation(ast, astack, regs);
    } 
    else {
        if(tts->non_term_translation[ast->symbol->symbol->non_terminal->type])
            tts->non_term_translation[ast->symbol->symbol->non_terminal->type]->translation(ast, astack, regs);
    }
}   

code_gen_T *init_code_gen(register_T **registers, tts_T *tts, symbol_table_tree_T *sym_tbl) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->registers = registers 
    ? registers 
    : copy_nasm_regs();
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
    
    char *tmp = generate_global_variables(cg);
    cg->output = strdup(tmp);
    free(tmp);
    generate_text_section(cg);
    // generate_code_rec(ast, astack, cg->tts, cg->registers);

    return cg->output;
}

register_T *code_gen_get_register(code_gen_T *cg) {
    for(int i = 0; i < NUM_REG; ++i) {
        if(!cg->registers[i]->is_used && !cg->registers[i]->is_preserved) {
            return cg->registers[i];
        }
    }

    return NULL;
}