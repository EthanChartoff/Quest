#ifndef QUEST_STACK_H
#define QUEST_STACK_H

#include <stdlib.h>

#define IS_EMPTY(s) ((s)->top == NULL)

typedef struct stack_node_T {
  void* data;
  struct stack_node_T* next;
} stack_node_T;

typedef struct GENERIC_STACK_STRUCT {
  stack_node_T* top;
  size_t size;
} stack_T;


stack_T* stack_init();
void stack_push(stack_T* s, void* data);
void *stack_pop(stack_T* s);
void *stack_peek(stack_T* s);
void stack_clear(stack_T* s);
void stack_flip(stack_T* s);
size_t stack_size(stack_T* s);

#endif /* QUEST_STACK_H */
