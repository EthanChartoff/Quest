#ifndef QUEST_CODE_GENERATOR_H
#define QUEST_CODE_GENERATOR_H

#include "TTS.h"
#include "register.h"
#include "../semantic_analizer/AST.h"
#include "../../utils/symbol_table/include/symbol_table_tree.h"
#include <stdint.h>

typedef struct CODE_GENERATOR_STRUCT {
    register_pool_T **registers;
    tts_T *tts;
    symbol_table_tree_T *sym_tbl;
    uint32_t label_counter;
    char *output;
} code_gen_T;

code_gen_T *init_code_gen(register_pool_T **registers, tts_T *tts, symbol_table_tree_T *sym_tbl);

char *generate_code(ast_node_T *ast, code_gen_T *cg);


// ==---------------==
//  Registers 
// ==---------------==

static const register_pool_T NASM_REGS[NUM_REG] = {
    {RAX, 0, DATA},
    {RBX, 0, DATA},
    {RCX, 0, DATA},
    {RDX, 0, DATA},
    {RSP, 0, POINTER},
    {RBP, 0, POINTER},
    {RSI, 0, INDEX},
    {RDI, 0, INDEX},
    {R8,  0, SCRATCH},
    {R9,  0, SCRATCH},
    {R10, 0, SCRATCH},
    {R11, 0, SCRATCH},
    {R12, 0, SCRATCH},
    {R13, 0, SCRATCH},
    {R14, 0, SCRATCH},
    {R15, 0, SCRATCH},
};

#endif /* QUEST_CODE_GENERATOR_H */