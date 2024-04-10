#ifndef QUEST_CODE_GENERATOR_H
#define QUEST_CODE_GENERATOR_H

#include "register.h"

#define NUM_REGISTERS 4

typedef struct CODE_GENERATOR_STRUCT {
    register_T registers[NUM_REGISTERS];
    char *dest;
} code_gen_T;

code_gen_T *init_code_gen(char *dest);

register_T *code_gen_get_register(code_gen_T *cg);

void code_gen_print_to_file(code_gen_T *cg, char *dest);

#endif /* QUEST_CODE_GENERATOR_H */