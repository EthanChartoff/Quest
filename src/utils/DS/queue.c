#include "include/queue.h"


queue_T* queue_init() {
	queue_T* q = (queue_T*)malloc(sizeof(queue_T));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

int is_empty(queue_T* q) {
  return (q->head == NULL);
}

void queue_enqueue(queue_T* q, void* data) {
	queue_node_T* new_node = (queue_node_T*)malloc(sizeof(queue_node_T));
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

void* queue_dequeue(queue_T* q) {
	if (is_empty(q)) {
		return NULL;
	}
	queue_node_T* temp = q->head;
	void* data = temp->data;
	q->head = q->head->next;
	if (is_empty(q)) {
		q->tail = NULL;
	}
	free(temp);
	q->size--;
	return data;
}

void* queue_peek(queue_T* q) {
	if (is_empty(q)) {
		return NULL;
	}
	return q->head->data;
}

void queue_clear(queue_T* q) {
	while (!is_empty(q)) {
		queue_dequeue(q);
	}
}

int queue_size(queue_T* q) {
  	return q->size;
}
