// #include "../include/parser/item_set.h"
// #include <stdio.h>
// #include <stdlib.h>

// lr_item_set_T *init_lr_item_set() {
//     lr_item_set_T *set = (lr_item_set_T*)malloc(sizeof(lr_item_set_T));
//     set->set = NULL;
//     set->size = 0;
//     return set;
// }

// lr_item_set_T *init_lr_item_set_with_item(lr_item_T *item) {
// 	lr_item_set_T *set = init_lr_item_set();
// 	add_item(&set, item);

//     return set;
// }

// int add_item(lr_item_set_T **set, lr_item_T *item) {
// 	size_t i;

// 	for (i = 0; i < (*set)->size; i++) {
// 		if (lr_item_equals((*set)->set[i], item)) {
// 			return 0; 
// 		}
//   	}

//   	(*set)->set = (lr_item_T**)realloc((*set)->set, sizeof(lr_item_T*) * ((*set)->size + 1));
//   	(*set)->set[(*set)->size] = item;
//  	(*set)->size++;

// 	return 1;
// }

// int add_set(lr_item_set_T **set, lr_item_set_T *set_to_add) {
// 	int added_count = 0, found;
// 	size_t i, j;

// 	for (i = 0; i < set_to_add->size; ++i) {
// 		found = 0;

// 		for(j = 0; j < (*set)->size; ++j) {
// 			if(lr_item_equals((*set)->set[j], set_to_add->set[i])) {
// 				found = 1;
// 				break;
// 			}
// 		}

// 		if(!found) {
// 			(*set)->set = (lr_item_T**)realloc((*set)->set, sizeof(lr_item_T*) * ((*set)->size + 1));
// 			(*set)->set[(*set)->size] = set_to_add->set[i];
// 			(*set)->size++;
// 			added_count++;
// 		}
// 	}

// 	return added_count;
// }

// int is_item_in_set(const lr_item_set_T *set, const lr_item_T *item) {
// 	int i;

// 	for(i = 0; i < set->size; ++i) {
// 		if(lr_item_equals(set->set[i], item)) {
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

// int lr_item_set_equals(const lr_item_set_T *set1, const lr_item_set_T *set2) {
// 	if(set1->size != set2->size)
// 		return 0;

// 	int i;

// 	for(i = 0; i < set1->size; ++i) {
// 		if(!is_item_in_set(set1, set2->set[i]))
// 			return 0;
// 	}
// 	return 1;
// }

// int lr_item_set_equals_generic(const void *set1, const void *set2) {
// 	return lr_item_set_equals((lr_item_set_T *) set1, (lr_item_set_T *) set2);
// }
