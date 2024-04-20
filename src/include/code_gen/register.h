#ifndef QUEST_REGISTER_H
#define QUEST_REGISTER_H

#include "../lexer/token.h"
#include <stdint.h>

#define LOW_BITS 0x3    // 0000 0011  
#define HIGH_BITS 0xC   // 0000 1100   

#define NUM_REG 16
#define NUM_SIZE 4

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
} register_E;

typedef enum REGISTER_SIZE {
    BYTE = 1,
    WORD = 2,
    DWORD = 4,
    QWORD = 8
} register_size_E;

typedef enum REGISTER_TYPE {
    DATA = 1,
    POINTER = 2,
    INDEX = 4,
    SEGMENT = 8,
    CONTROL = 16,
    FLAGS = 32,
    STACK = 64,
    SCRATCH = 128
} register_type_E;

static const char *REGS_STR[NUM_REG][NUM_SIZE] = {
    {"al", "ax", "eax", "rax"},
    {"cl", "cx", "ecx", "rcx"},
    {"dl", "dx", "edx", "rdx"},
    {"bl", "bx", "ebx", "rbx"},
    {"spl", "sp", "esp", "rsp"},
    {"bpl", "bp", "ebp", "rbp"},
    {"sil", "si", "esi", "rsi"},
    {"dil", "di", "edi", "rdi"},
    {"r8b", "r8w", "r8d", "r8"},
    {"r9b", "r9w", "r9d", "r9"},
    {"r10b", "r10w", "r10d", "r10"},
    {"r11b", "r11w", "r11d", "r11"},
    {"r12b", "r12w", "r12d", "r12"},
    {"r13b", "r13w", "r13d", "r13"},
    {"r14b", "r14w", "r14d", "r14"},
    {"r15b", "r15w", "r15d", "r15"}
};

typedef struct REGISTER_STRUCT {
    register_E reg;         // reg type
    register_size_E size;   // reg size
    char *name;             // name
} register_T;

typedef struct REGISTER_POOL_STRUCT {
    uint64_t value;         // reg pool value
    uint64_t in_use;        // is reg or part of reg in use
    register_type_E type;   // type of reg
} register_pool_T;

register_T *init_register(uint8_t type, uint8_t size, char *name);
register_pool_T *init_register_pool(uint8_t type);

register_T *get_register(register_pool_T **regs, uint8_t type, uint8_t size);
char *get_register_name(uint8_t type, uint8_t size);

void reg_alloc(register_T *reg, uint64_t value);
void reg_free(register_pool_T **regs, register_T *reg);

#endif /* QUEST_REGISTER_H */
