#include "../include/code_gen/code_generator.h"
#include "../include/code_gen/nasm_macros.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static register_pool_T **copy_nasm_regs() {
    int i = 0;
    register_pool_T **tmp = malloc(sizeof(register_pool_T *) * NUM_REG);
    if(!tmp)
        thrw(ALLOC_ERR);

    for(;i < NUM_REG; ++i) {
        tmp[i] = malloc(sizeof(register_T));
        if(!tmp[i])
            thrw(ALLOC_ERR);

        *tmp[i] = NASM_REGS[i];
    }
    return tmp;
}

static void generate_text_section(code_gen_T *cg) {
    cg->output = realloc(cg->output, strlen(cg->output) + strlen(TEXT_SECTION) + strlen(GLOBAL("_start")) + strlen(LABEL("_start")) + 1);
    strcat(cg->output, TEXT_SECTION);
    strcat(cg->output, GLOBAL("_start"));
    strcat(cg->output, LABEL("_start"));    
}

static char *generate_global_variables(code_gen_T *cg) {
    int i;
    symbol_table_entry_T *cur;
    char *tmp;

    cg->output = realloc(cg->output, strlen(cg->output) + strlen(BSS_SECTION) + 1);
    strcat(cg->output, BSS_SECTION);

    for(i = 0; i < cg->sym_tbl->root->table->capacity; ++i) {
        cur = cg->sym_tbl->root->table->buckets[i];

        while(cur) {
            tmp = malloc(strlen(RESB("1")) + strlen(cur->name) + 1);

            switch (cur->type) {
                case TOK_INT:
                    sprintf(tmp, RESD("1"), cur->name);
                    strcat(cg->output, tmp);
                    break;

                case TOK_CHAR:
                    sprintf(tmp, RESB("1"), cur->name);
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

// reverser code string using its lines. for exampla:
//  mov DWORD [a], ecx
//  mov ecx, 94
//  mov eax, [a]
// should be
//  mov eax, [a]
//  mov ecx, 94
//  mov DWORD [a], ecx
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

static char *generate_code_rec(ast_node_T *ast, stack_T *astack, stack_T *code_stack, code_gen_T *cg, char *tmp) {
    if(!ast)
        return NULL;
    
    int i;
    for(i = 0; i < ast->n_children ; ++i) {
        tmp = generate_code_rec(ast->children[i], astack, stack_init(), cg, NULL);
        if(tmp) 
            stack_push(code_stack, strdup(tmp));
        
        free(tmp);
    }

    tmp = NULL;
    if(ast->symbol->sym_type == TERMINAL) {
        if(cg->tts->tok_translation[ast->symbol->symbol->terminal->type]) 
            tmp = cg->tts->tok_translation[ast->symbol->symbol->terminal->type]->translation(ast, astack, code_stack, cg->registers);
    } 
    else {
        if(cg->tts->non_term_translation[ast->symbol->symbol->non_terminal->type])
            tmp = cg->tts->non_term_translation[ast->symbol->symbol->non_terminal->type]->translation(ast, astack, code_stack, cg->registers);
    }

    // flip stack
    char *tmp2;

    while(!IS_EMPTY(code_stack)) {
        tmp2 = stack_pop(code_stack);

        if(!tmp)
            tmp = strdup(tmp2);
        else {
            tmp = realloc(tmp, strlen(tmp) + strlen(tmp2) + 1);
            strcat(tmp, strdup(tmp2));
        }
    }

    // printf("tmp: %s\n", tmp);
    return tmp;
}   

static char *gen_code_instructions(ast_node_T *ast, code_gen_T *cg) {
    stack_T *astack = stack_init();
    stack_T *code_stack = stack_init();

    return reverse_code(generate_code_rec(ast, astack, code_stack, cg, NULL));
}

code_gen_T *init_code_gen(register_pool_T **registers, tts_T *tts, symbol_table_tree_T *sym_tbl) {
    code_gen_T *cg = malloc(sizeof(code_gen_T));
    if(!cg)
        thrw(ALLOC_ERR);

    cg->registers = registers 
    ? registers 
    : copy_nasm_regs();
    cg->tts = tts;
    cg->sym_tbl = sym_tbl;
    cg->label_counter = 0;
    cg->output = calloc(1, 1);
    if(!cg->output)
        thrw(ALLOC_ERR);

    return cg;
}

char *generate_code(ast_node_T *ast, code_gen_T *cg) {
    cg->output = strdup(generate_global_variables(cg));
    generate_text_section(cg);
    
    strcat(cg->output, gen_code_instructions(ast, cg));
    strcat(cg->output, END_PROGRAM);

    return cg->output;
}