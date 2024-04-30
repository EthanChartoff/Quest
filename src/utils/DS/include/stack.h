#ifndef QUEST_STACK_H
#define QUEST_STACK_H

#include <stdlib.h>

#define IS_EMPTY(s) ((s)->top == NULL)

/**
 * Structure of a stack node
 */
typedef struct STACK_NODE_STRUCT {
  void *data;                      // The data stored in the stack node
  struct STACK_NODE_STRUCT *next;  // Pointer to the next stack node
} stack_node_T;

/**
 * Structure of a generic stack
 */
typedef struct GENERIC_STACK_STRUCT {
  stack_node_T *top;               // Pointer to the top of the stack
  size_t size;                     // Number of items in the stack
} stack_T;

stack_T *stack_init();
void stack_push(stack_T* s, void* data);
void *stack_pop(stack_T* s);
void *stack_peek(stack_T* s);
void stack_clear(stack_T* s);
void stack_flip(stack_T* s);
size_t stack_size(stack_T* s);

#endif /* QUEST_STACK_H */
