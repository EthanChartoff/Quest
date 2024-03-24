#include "include/stack.h"
#include "../err/err.h"

stack_T* stack_init() {
  stack_T* s = (stack_T*)malloc(sizeof(stack_T));
  if(!s)
    thrw(ALLOC_ERR);

  s->top = NULL;
  s->size = 0;

  return s;
}

void stack_push(stack_T* s, void* data) {
  stack_node_T* new_node = (stack_node_T*)malloc(sizeof(stack_node_T));
  if(!new_node)
    thrw(ALLOC_ERR);

  new_node->data = data;
  new_node->next = s->top;
  s->top = new_node;
  s->size++;
}

void* stack_pop(stack_T* s) {
  if (IS_EMPTY(s)) {
    return NULL;
  }
  stack_node_T* temp = s->top;
  void* data = temp->data;

  s->top = s->top->next;
  free(temp);
  s->size--;

  return data;
}

void* stack_peek(stack_T* s) {
  if (IS_EMPTY(s)) {
    return NULL;
  }
  
  return s->top->data;
}

void stack_clear(stack_T* s) {
  while (!IS_EMPTY(s)) {
    stack_pop(s);
  }
}

size_t stack_size(stack_T* s) {
  return s->size;
}
