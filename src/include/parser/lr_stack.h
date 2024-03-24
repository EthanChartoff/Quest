#ifndef QUEST_LR_STACK_H
#define QUEST_LR_STACK_H

#include <stddef.h>

#define IS_EMPTY(s) ((s)->size == 0)


typedef struct LR_STACK_STRUCT {
    int *top;           // top of the stack
    size_t size;        // size of stack
    size_t capacity;    // capacity of stack
    size_t alloc_size;  // how many bytes to allocate when stack is full
} lr_stack_T;

lr_stack_T *init_lr_stack(size_t alloc_size);

void lr_stack_push(lr_stack_T *s, int data);
int lr_stack_pop(lr_stack_T *s);
int lr_stack_peek(lr_stack_T *s);
int lr_stack_full(lr_stack_T *s);
void lr_stack_clear(lr_stack_T *s);


#endif /* QUEST_LR_STACK_H */