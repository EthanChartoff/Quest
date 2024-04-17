#include "../include/code_gen/register.h"
#include <stdio.h>
#include <stdlib.h>


register_T *init_register(register_E type, uint8_t is_preserved) {
    register_T *reg = malloc(sizeof(register_T));

    reg->type = type;
    reg->is_preserved = is_preserved;
    reg->value = 0;
    reg->is_used = 0;

    return reg;
}

register_T *get_register(register_T **regs) {
    for(int i = 0; i < NUM_REG; ++i) {
        if(!regs[i]->is_used && !regs[i]->is_preserved) {
            regs[i]->is_used = 1;
            return regs[i];
        }
    }

    return NULL;
}

void reg_alloc(register_T *reg, uint64_t value) {
    reg->value = value;
    reg->is_used = 1;

    return;
}
void reg_free(register_T *reg) {
    reg->is_used = 0;

    return;
}