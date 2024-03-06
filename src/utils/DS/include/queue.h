#ifndef QUEST_QUEUE_H
#define QUEST_QUEUE_H

#include <stdlib.h>


typedef struct Node {
  void* data;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* head;
  Node* tail;
  int size;
} Queue;

Queue* queue_init();
int is_empty(Queue* q);
void queue_enqueue(Queue* q, void* data);
void* queue_dequeue(Queue* q);
void* queue_peek(Queue* q);
void queue_clear(Queue* q);
int queue_size(Queue* q);

#endif /* QUEST_QUEUE_H */
