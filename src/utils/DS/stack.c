#include "include/stack.h"


Stack* stack_init() {
  Stack* s = (Stack*)malloc(sizeof(Stack));
  s->top = NULL;
  s->size = 0;
  return s;
}

void stack_push(Stack* s, void* data) {
  queue_node_T* new_node = (queue_node_T*)malloc(sizeof(queue_node_T));
  new_node->data = data;
  new_node->next = s->top;
  s->top = new_node;
  s->size++;
}

void* stack_pop(Stack* s) {
  if (IS_EMPTY(s)) {
    return NULL;
  }
  queue_node_T* temp = s->top;
  void* data = temp->data;
  s->top = s->top->next;
  free(temp);
  s->size--;
  return data;
}

void* stack_peek(Stack* s) {
  if (IS_EMPTY(s)) {
    return NULL;
  }
  return s->top->data;
}

void stack_clear(Stack* s) {
  while (!IS_EMPTY(s)) {
    stack_pop(s);
  }
}

int stack_size(Stack* s) {
  return s->size;
}
