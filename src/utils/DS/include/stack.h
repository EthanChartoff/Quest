#ifndef QUEST_STACK_H
#define QUEST_STACK_H

#include <stdlib.h>

#define IS_EMPTY(s) ((s)->top == NULL)

typedef struct queue_node_T {
  void* data;
  struct queue_node_T* next;
} queue_node_T;

typedef struct Stack {
  queue_node_T* top;
  int size;
} Stack;


Stack* stack_init();
void stack_push(Stack* s, void* data);
void* stack_pop(Stack* s);
void* stack_peek(Stack* s);
void stack_clear(Stack* s);
int stack_size(Stack* s);

#endif /* QUEST_STACK_H */
