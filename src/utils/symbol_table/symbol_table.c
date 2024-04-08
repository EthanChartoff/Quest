#include "include/symbol_table.h"
#include "../err/err.h"
#include "../hashes/hashes.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

symbol_table_T *init_symbol_table(unsigned int capacity, float load_factor, unsigned int (*hash)(char *, size_t length)) {
    symbol_table_T *st = malloc(sizeof(symbol_table_T));
    if(!st)
        thrw(ALLOC_ERR);

    st->size = 0;
    st->capacity = capacity ? capacity : DEFAULT_INITIAL_CAPACITY;
    st->load_factor = load_factor ? load_factor : DEFAULT_LOAD_FACTOR;
    st->buckets = (symbol_table_entry_T **)malloc(st->capacity * sizeof(symbol_table_entry_T *));
    if(!st->buckets)
        thrw(ALLOC_ERR);
    st->hash = hash ? hash : hash_JOAAT;

    return st;
}

symbol_table_T *init_symbol_table_default() {
    symbol_table_T *st = malloc(sizeof(symbol_table_T));
    if(!st)
        thrw(ALLOC_ERR);

    st->size = 0;
    st->capacity = DEFAULT_INITIAL_CAPACITY;
    st->load_factor = DEFAULT_LOAD_FACTOR;
    st->buckets = (symbol_table_entry_T **)calloc(st->capacity, sizeof(symbol_table_entry_T *));
    if(!st->buckets)
        thrw(ALLOC_ERR);
    st->hash = hash_JOAAT;

    return st;
}

symbol_table_entry_T *init_symbol_table_entry(char *name, int type, void *value) {
    symbol_table_entry_T *entry = malloc(sizeof(symbol_table_entry_T));

    entry->name = name;
    entry->type = type;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

unsigned int symbol_table_insert(symbol_table_T *st, symbol_table_entry_T *ste) {
    if(!ste) {
        thrw(ARG_ERR);
        return 0;
    }

    uint32_t i = st->hash(ste->name, strlen(ste->name)) % st->capacity;

    if(!st->buckets[i]) 
        st->buckets[i] = ste;
    else {
        ste->next = st->buckets[i];
        st->buckets[i] = ste;   
    }

    // check if need to resize    
    if(((float)st->size / st->capacity >= st->load_factor))
        return symbol_table_resize(st);
    
    st->size++;

    return 1;
}


symbol_table_entry_T *symbol_table_find(symbol_table_T *st, char *name) {
    uint32_t i = st->hash(name, strlen(name));
    symbol_table_entry_T *tmp = st->buckets[i];

    while(tmp) {
        if(strcmp(tmp->name, name)) 
            return st->buckets[i];
        tmp = tmp->next;
    }
    
    return NULL;
}

unsigned int symbol_table_resize(symbol_table_T *st) {
    // check if need to resize
    if(((float)st->size / st->capacity >= st->load_factor))
        return 0;

    symbol_table_entry_T **new_buckets, *cur, *next;
    int i, new_index;

    st->capacity *= DEFAULT_RESIZE_CONSTANT;
    new_buckets = (symbol_table_entry_T **)calloc(st->capacity, sizeof(symbol_table_entry_T *));
    if(!new_buckets)
        thrw(ALLOC_ERR);
    
    // rehash all elements into new table
    for(i = 0; i < st->capacity; ++i) {
        cur = st->buckets[i];

        while(cur) {
            new_index = st->hash(cur->name, strlen(cur->name)) % st->capacity;
            next = cur->next;

            cur->next = new_buckets[new_index];
            new_buckets[new_index] = cur;
            cur = next;
        }
    }

    // free prev table
    free(st->buckets);
    st->buckets = new_buckets;

    return 0;
}

void symbol_table_print(symbol_table_T *st) {
    for(int i = 0; i < st->capacity; ++i) {
        symbol_table_entry_T *cur = st->buckets[i];

        while(cur) {
            printf("name: %s, type: %d, value: %p\n", cur->name, cur->type, cur->value);
            cur = cur->next;
        }
    }
}
