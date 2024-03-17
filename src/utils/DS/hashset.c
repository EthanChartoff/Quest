#include "include/hashset.h"
#include "../err/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Create a new hash set
hashset_T *init_hash_set(int initial_capacity, float load_factor, unsigned int (*hash_func)(void *), int (*compare_func)(void *, void *)) {
  	hashset_T *set = (hashset_T *)malloc(sizeof(hashset_T));
	if(!set)
		thrw(ALLOC_ERR);

  	set->size = 0;
  	set->capacity = initial_capacity > 0 ? initial_capacity : 4;									// Minimum capacity of 4
  	set->load_factor = load_factor > 0 ? load_factor : 0.75;      									// load factor
  	set->buckets = (hashset_node_T **)calloc(set->capacity, sizeof(hashset_node_T *));	 // 
	if(!set->buckets)
		thrw(ALLOC_ERR);
  	set->hash_func = hash_func != NULL ? hash_func : hash_set_hash;				// apply default hash func if not given one 	 
	set->compare_func = compare_func; // apply default cmp func if not given one

	return set;
}

// a random hash function
unsigned int hash_set_hash(void *data) {
	unsigned long long key = (unsigned long long)data;
	key += ~(key << 15);
	key *= 224682251;
	key ^= (key >> 13);
	key *= 1831564602;
	return (unsigned int)(key ^ (key >> 16));
}

// Default comparison function (simple pointer comparison)
int default_compare_func(void* a, void* b) {
  return a == b;
}

// Add an element to the hash set
int hash_set_add(hashset_T *set, void* data) {
	int index = set->hash_func(data) % set->capacity;
	hashset_node_T *new_node = (hashset_node_T *)malloc(sizeof(hashset_node_T)), *curr = set->buckets[index];

	while (curr != NULL) {
		if (set->compare_func(curr->data, data)) {
			return 0; // Element already exists, don't add again
		}
		curr = curr->next;
	}

	if(!new_node)
		thrw(ALLOC_ERR);
	new_node->data = data;
	new_node->next = set->buckets[index];
	set->buckets[index] = new_node;
	set->size++;

	// Check for resize condition
	if ((float)set->size / set->capacity >= set->load_factor) {
		if (!hash_set_resize(set, set->capacity * 2)) {
			thrw(HASHSET_RESIZE_ERR); // Resize failed
		}
	}

	return 1;
}

int hash_set_add_all(hashset_T *set, hashset_T *other_set) {
	hashset_node_T *curr;
	int add_c;
	
	if (other_set == NULL || other_set->size == 0) {
		return 0;  // Nothing to add
	}

	for (int i = 0; i < other_set->capacity; i++) {
		curr = other_set->buckets[i];
		while (curr != NULL) {
			add_c += hash_set_add(set, curr->data);  // Add each element from the other set
			curr = curr->next;
		}
	}

	return add_c;
}

// Check if an element exists in the hash set
int hash_set_contains(hashset_T *set, void* data) {
	int index = set->hash_func(data) % set->capacity;
	hashset_node_T *current = set->buckets[index];

	while (current != NULL) {
		if (set->compare_func(current->data, data)) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

// Resize the hash table dynamically
int hash_set_resize(hashset_T *set, int new_capacity) {
	hashset_node_T **temp_buckets, *current, *temp_node;
	int new_index;

	temp_buckets = (hashset_node_T **)calloc(new_capacity, sizeof(hashset_node_T *));
	if (!temp_buckets)
		thrw(ALLOC_ERR);
	

	// Rehash all elements into the new table
	for (int i = 0; i < set->capacity; i++) {
		current = set->buckets[i];
		while (current != NULL) {
			new_index = set->hash_func(current->data) % new_capacity;
			temp_node = current;
			current = current->next;
			temp_node->next = temp_buckets[new_index];
			temp_buckets[new_index] = temp_node;
		}
	}

	// Free old table memory
	free(set->buckets);
	set->buckets = temp_buckets;
	set->capacity = new_capacity;

	return true;
}

void hash_set_free(hashset_T *set) {
	hashset_node_T *current, *temp;

	for (int i = 0; i < set->capacity; i++) {
		current = set->buckets[i];
		while (current != NULL) {
			temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(set->buckets);
	free(set);
}