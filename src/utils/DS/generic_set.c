#include <stdlib.h>
#include "include/generic_set.h"

// Function to initialize a new set
set_T* set_init(int (*compare)(const void*, const void*)) {
	set_T* set = (set_T*)malloc(sizeof(set_T));
	set->head = NULL;
	set->compare = compare;
	set->size = 0;
	return set;
}

// Function to add an element to the set
int set_add(set_T* set, void* data) {
	// Check for duplicates (using the comparison function)
	set_node_T* current = set->head;
	while (current != NULL) {
		if (set->compare(current->data, data) == 0) {
			return 0;  // Element already exists
		}
		current = current->next;
  	}

	// Create a new node for the data
	set_node_T* new_node = (set_node_T*)malloc(sizeof(set_node_T));
	new_node->data = data;
	new_node->next = NULL;

	// Insert the new node at the head of the list
	new_node->next = set->head;
	set->head = new_node;
	set->size++;
	return 1;  // Element added successfully
}

int set_add_all(set_T* set, set_T *more_set) {
	int i, c;
	set_node_T *cur;

	cur = more_set->head;
	for(i = 0; i < more_set->size; ++i) {
		c += set_add(set, cur->data);
		cur = cur->next;
	}
	return c;
}

// Function to check if an element exists in the set
int set_contains(set_T* set, void* data) {
  set_node_T* current = set->head;
  while (current != NULL) {
    if (set->compare(current->data, data) == 0) {
      return 1;  // Element found
    }
    current = current->next;
  }
  return 0;  // Element not found
}

void set_free(set_T* set) {
  set_node_T* current = set->head;
  while (current != NULL) {
    set_node_T* temp = current;
    current = current->next;
    free(temp->data);  // Free data if needed (depending on data type)
    free(temp);
  }
  free(set);
}
