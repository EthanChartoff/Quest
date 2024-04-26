#include "../include/code_gen/register.h"
#include "../utils/err/err.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// special case for data byte registers
static register_T *get_data_byte_reg(register_pool_T **regs) {
    int i = 0;

    for(;i < NUM_REG; ++i) {
        if(regs[i]->type != DATA)
            continue;

        if(!(regs[i]->in_use & LOW_BITS)) {
            regs[i]->in_use = regs[i]->in_use | LOW_BITS;
            return init_register(i, BYTE, get_byte_data_reg_name(i, LOW_BITS));
        } else if(!(regs[i]->in_use & HIGH_BITS)) {
            regs[i]->in_use = regs[i]->in_use | HIGH_BITS;
            return init_register(i, BYTE, get_byte_data_reg_name(i, HIGH_BITS));
        }
    }

    thrw(REG_NOT_FOUND_ERR);
    return NULL;
}

// general case
static register_T *get_reg_reg(register_pool_T **regs, uint8_t type, uint8_t size) {
    int i = 0;
    uint64_t bits_on = (1 << (size * 2)) - 1;

    for(;i < NUM_REG; ++i) {
        if(regs[i]->type == type && !(regs[i]->in_use & bits_on)) {
            regs[i]->in_use = regs[i]->in_use | bits_on;
            return init_register(i, size, NULL);
        }
    }

    thrw(REG_NOT_FOUND_ERR);
    return NULL;
}

register_T *init_register(uint8_t type, uint8_t size, char *name) {
    register_T *reg = malloc(sizeof(register_T));
    if(!reg)
        thrw(ALLOC_ERR);

    reg->reg = type;
    reg->size = size;
    reg->name = name ? name : get_register_name(type, size);

    return reg;
}

register_pool_T *init_register_pool(uint8_t type) {
    register_pool_T *pool = malloc(sizeof(register_pool_T));
    if(!pool)
        thrw(ALLOC_ERR);

    pool->value = 0;
    pool->in_use = 0;
    pool->type = type;

    return pool;
}

register_T *get_register(register_pool_T **regs, uint8_t type, uint8_t size) {
    return type == DATA  && size == BYTE 
    ? get_data_byte_reg(regs) 
    : get_reg_reg(regs, type, size);
}

char *get_register_name(uint8_t type, uint8_t size) {
    int size_num = 0;

    while (size >>= 1) 
        size_num++;

    return strdup(REGS_STR[type][size_num]);
}

char *get_byte_data_reg_name(uint8_t type, uint8_t bits) {
    return strdup(DATA_REGS_STR[type][bits == HIGH_BITS]);
}

// void reg_alloc(register_T *reg, uint64_t value) {
//     reg->value = value;
//     reg->is_used = 1;

//     return;
// }

void reg_free(register_pool_T **regs, register_T *reg) {
    uint64_t bits_off = ~((1 << (reg->size * 2)) - 1);

    printf("lol %zd\n", reg->reg);
    regs[reg->reg]->in_use &= bits_off;
}

