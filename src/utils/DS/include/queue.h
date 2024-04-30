#ifndef QUEST_QUEUE_H
#define QUEST_QUEUE_H

#include <stdlib.h>


/**
 * Generic Queue Node Structure
 *
 * Contains data and a pointer to the next node in the queue.
 */
typedef struct GENERIC_QUEUE_NODE_STRUCT {
    void* data;                  /* Data stored in the node */
    struct GENERIC_QUEUE_NODE_STRUCT *next;  /* Pointer to the next node in the queue */
} queue_node_T;

/**
 * Generic Queue Structure
 *
 * Contains a pointer to the head and tail nodes of the queue,
 * as well as the current size of the queue.
 */
typedef struct GENERIC_QUEUE_STRUCT {
    queue_node_T *head;   /* Pointer to the head node of the queue */
    queue_node_T *tail;   /* Pointer to the tail node of the queue */
    int size;            /* Current size of the queue */
} queue_T;

queue_T *queue_init();
int is_empty(queue_T* q);
void queue_enqueue(queue_T* q, void* data);
void *queue_dequeue(queue_T* q);
void *queue_peek(queue_T* q);
void queue_clear(queue_T* q);
int queue_size(queue_T* q);

#endif /* QUEST_QUEUE_H */
