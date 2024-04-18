#ifndef QUEST_REGISTER_H
#define QUEST_REGISTER_H

#include <cstdint>
#include <stdint.h>

typedef enum REGISTER_ENUM {
    RAX,
    RCX,
    RDX,
    RBX,
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

static const char *REGS_STR[NUM_REG] = {
    "a",
    "b",
    "c",
    "d",
    "sp",
    "bp",
    "si",
    "di",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15"
};

typedef enum REGISTER_SIZE {
    BYTE = 1,
    WORD = 2,
    DWORD = 4,
    QWORD = 8
} register_size_E;

typedef enum REGISTER_TYPE {
    DATA = 1,
    INDEX = 2,
    POINTER = 4,
    SEGMENT = 8,
    CONTROL = 16
} register_type_E;

typedef struct REGISTER_STRUCT {
    register_E reg;         // reg type
    register_size_E size;   // reg size
    char *name;             // name
} register_T;

typedef struct REGISTER_POOL_STRUCT {
    uint64_t value;
    uint64_t in_use;
    uint8_t type;
} register_pool_T;

register_T *init_register(char *name, uint8_t size, uint64_t value);



register_T *get_register(register_T **regs);
char *get_register_name(register_T **regs);


void reg_alloc(register_T *reg, uint64_t value);
void reg_free(register_T *reg);

#endif /* QUEST_REGISTER_H */