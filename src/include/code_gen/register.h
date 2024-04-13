#ifndef QUEST_REGISTER_H
#define QUEST_REGISTER_H

#include <stdint.h>

typedef enum REGISTER_TYPE {
    RAX,
    RBX,
    RCX,
    RDX,
    RSP, 
    RBP,
    RSI,
    RDI, 
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
    NUM_REG
} register_E;

typedef struct REGISTER_STRUCT {
    register_E type;        // what register this is
    uint64_t value;         // val in the reg
    uint8_t is_preserved;   // is this register preserved
    uint8_t is_used;        // is this register used
} register_T;

register_T *init_register(register_E type, uint8_t is_preserved);

register_T *get_register(register_T **regs);

void reg_alloc(register_T *reg, uint64_t value);
void reg_free(register_T *reg);

#endif /* QUEST_REGISTER_H */