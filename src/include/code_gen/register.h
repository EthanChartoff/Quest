#ifndef QUEST_REGISTER_H
#define QUEST_REGISTER_H

#include <cstdint>

typedef struct REGISTER_STRUCT {
    char *name;
    uint64_t value;
    uint8_t is_used;
} register_T;

register_T *init_register(char *name);

void reg_alloc(register_T *reg, uint64_t value);
void reg_free(register_T *reg);

#endif /* QUEST_REGISTER_H */