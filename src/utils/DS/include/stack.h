#ifndef QUEST_STACK_H
#define QUEST_STACK_H

#include <stdlib.h>

#define IS_EMPTY(s) ((s)->top == NULL)

typedef struct Node {
  void* data;
  struct Node* next;
} Node;

typedef struct Stack {
  Node* top;
  int size;
} Stack;


Stack* stack_init();
void stack_push(Stack* s, void* data);
void* stack_pop(Stack* s);
void* stack_peek(Stack* s);
void stack_clear(Stack* s);
int stack_size(Stack* s);

#endif /* QUEST_STACK_H */
