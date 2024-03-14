#include "../include/parser/symbol_set.h"
#include <stdlib.h>

symbol_set_T *init_symbol_set() {
    symbol_set_T *set = (symbol_set_T*) malloc(sizeof(symbol_set_T));

    set->set = NULL;
    set->size = 0;
    return set;
}

symbol_set_T *init_symbol_set_with_symbols(symbol_T **syms, const size_t size) {
	symbol_set_T *set = (symbol_set_T*) malloc(sizeof(symbol_set_T));
	int i;

    set->set = malloc(sizeof(symbol_T *) * size);
    set->size = size;

	for(i = 0; i < set->size; ++i) {
		set->set[i] = malloc(sizeof(symbol_T));
		
		set->set[i]->symbol = syms[i]->symbol;
		set->set[i]->sym_type = syms[i]->sym_type;
	}

    return set;
}

int add_symbol(symbol_set_T *set, symbol_T *item) {
    size_t i;

	for (i = 0; i < set->size; i++) {
		if (symbol_equals(set->set[i], item)) {
			return 0; 
		}
  	}

  	set->set = (symbol_T**) realloc(set->set, sizeof(symbol_T*) * (set->size + 1));
  	set->set[set->size] = item;
 	set->size++;

	return 1;
}

int remove_symbol(symbol_set_T *set, symbol_T *item) {
	int i, j;

	for(i = 0; i < set->size; ++i) {
		if(symbol_equals(set->set[i], item)) {
			for(j = i; j < set->size - 1; ++j) {
				set->set[j] = set->set[j+1];
			}
			set->size--;
			break;
		}
	}
	set->set = realloc(set->set, sizeof(symbol_T*) * set->size);

	return 1;
}

