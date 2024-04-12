#ifndef QUEST_CODE_GENERATOR_H
#define QUEST_CODE_GENERATOR_H

#include "TTS.h"
#include "register.h"
#include "../semantic_analizer/AST.h"
#include "../../utils/symbol_table/include/symbol_table_tree.h"

typedef struct CODE_GENERATOR_STRUCT {
    register_T **registers;
    tts_T *tts;
    symbol_table_tree_T *sym_tbl;
    char *dest;
    char *output;
} code_gen_T;

code_gen_T *init_code_gen(register_T **registers, tts_T *tts, symbol_table_tree_T *sym_tbl, char *dest);
code_gen_T *init_code_gen_default(char *dest, tts_T *tts, symbol_table_tree_T *sym_tbl);

char *generate_code(ast_node_T *ast, code_gen_T *cg);

register_T *code_gen_get_register(code_gen_T *cg);

void code_gen_print_to_file(code_gen_T *cg, char *dest);


// ==---------------==
//  Registers 
// ==---------------==

static const register_T NASM_REGS[NUM_REG] = {
    {RAX, 0, 0, 0},
    {RBX, 0, 1, 0},
    {RCX, 0, 0, 0},
    {RDX, 0, 0, 0},
    {RSP, 0, 1, 0},
    {RBP, 0, 1, 0},
    {RSI, 0, 1, 0},
    {RDI, 0, 1, 0},
    {R8,  0, 0, 0},
    {R9,  0, 0, 0},
    {R10, 0, 0, 0},
    {R11, 0, 0, 0},
    {R12, 0, 1, 0},
    {R13, 0, 1, 0},
    {R14, 0, 1, 0},
    {R15, 0, 1, 0},
};


#endif /* QUEST_CODE_GENERATOR_H */