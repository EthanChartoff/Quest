#ifndef QUEST_QUEUE_H
#define QUEST_QUEUE_H

#include <stdlib.h>


typedef struct GENERIC_QUEUE_NODE_STRUCT {
    void* data;
    struct GENERIC_QUEUE_NODE_STRUCT* next;
} queue_node_T;

typedef struct GENERIC_QUEUE_STRUCT {
    queue_node_T* head;
    queue_node_T* tail;
    int size;
} queue_T;

queue_T* queue_init();
int is_empty(queue_T* q);
void queue_enqueue(queue_T* q, void* data);
void* queue_dequeue(queue_T* q);
void* queue_peek(queue_T* q);
void queue_clear(queue_T* q);
int queue_size(queue_T* q);

#endif /* QUEST_QUEUE_H */
