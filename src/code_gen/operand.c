#include "../include/code_gen/operand.h"
#include "../utils/err/err.h"
#include <stdlib.h>

operand_T *init_tts_node_symbol(symbol_T *sym) {
    operand_T *node = malloc(sizeof(operand_T));
    if(!node)
        thrw(ALLOC_ERR);

    node->type = SYMBOL;
    node->operand->sym = sym;

    return node;
}

operand_T *init_tts_node_register(register_T *reg) {
    operand_T *node = malloc(sizeof(operand_T));
    if(!node)
        thrw(ALLOC_ERR);

    node->type = REGISTER;
    node->operand->reg = reg;

    return node;
}
