#ifndef QUEST_GENERIC_SET
#define QUEST_GENERIC_SET

#include <stdlib.h>

// Define a node structure for the set elements
typedef struct GENERIC_SET_NODE_STRUCT {
	void *data;                            // Pointer to the element data (can hold any type)
	struct GENERIC_SET_NODE_STRUCT *next;  // Pointer to the next node in the set
} set_node_T;

// Define the set structure
typedef struct GENERIC_SET_STRUCT {
	set_node_T *head;  							// Pointer to the head node of the set
	int (*compare)(const void*, const void*);  	// Pointer to a comparison function
	size_t size;  								// Size of the set (number of elements)
} set_T;

set_T* set_init(int (*compare)(const void*, const void*));
int set_add(set_T* set, void* data);
int set_add_all(set_T* set, set_T *more_set);
int set_remove(set_T* set, void* data);
int set_contains(set_T* set, void* data);
void set_free(set_T* set);

#endif

