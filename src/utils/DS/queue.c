#include "include/queue.h"


Queue* queue_init() {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

int is_empty(Queue* q) {
  return (q->head == NULL);
}

void queue_enqueue(Queue* q, void* data) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  if (is_empty(q)) {
    q->head = new_node;
  } else {
    q->tail->next = new_node;
  }
  q->tail = new_node;
  q->size++;
}

void* queue_dequeue(Queue* q) {
  if (is_empty(q)) {
    return NULL;
  }
  Node* temp = q->head;
  void* data = temp->data;
  q->head = q->head->next;
  if (is_empty(q)) {
    q->tail = NULL;
  }
  free(temp);
  q->size--;
  return data;
}

void* queue_peek(Queue* q) {
  if (is_empty(q)) {
    return NULL;
  }
  return q->head->data;
}

void queue_clear(Queue* q) {
  while (!is_empty(q)) {
    queue_dequeue(q);
  }
}

int queue_size(Queue* q) {
  return q->size;
}
