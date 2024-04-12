#ifndef QUEST_OPERAND_H
#define QUEST_OPERAND_H

#include "register.h"
#include "../parser/symbol.h"

typedef enum OPERAND_TYPES_ENUM {
    SYMBOL,
    REGISTER
} operand_type_E;

typedef union OPERAND_UNION {
    symbol_T *sym;
    register_T *reg;
} operand_U;

typedef struct OPERAND_STRUCT {
    operand_type_E type;
    operand_U *operand;
} operand_T;

operand_T *init_operand_symbol(symbol_T *sym);
operand_T *init_operand_register(register_T *reg);

void operand_free(operand_T *op);

#endif /* QUEST_OPERAND_H */