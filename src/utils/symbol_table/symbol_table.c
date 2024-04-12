#include "include/symbol_table.h"
#include "../err/err.h"
#include "../hashes/hashes.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/**
 * Creates a new symbol table with the given capacity and load factor.
 * If capacity is 0, a default capacity is used.
 * If load factor is 0.0, a default load factor is used.
 * @param capacity The initial capacity of the symbol table.
 * @param load_factor The load factor of the symbol table.
 * @param hash A function that hashes strings.
 * @return A new symbol table.
 */
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

/**
 * Creates a new symbol table with default capacity and load factor.
 * @return A new symbol table.
 */
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

/**
 * Creates a new entry for the symbol table.
 * @param name The name of the variable.
 * @param type The type of the variable.
 * @param value The value of the variable.
 * @param declaration_type The declaration type of the variable.
 * @return The new entry.
 */
symbol_table_entry_T *init_symbol_table_entry(char *name, int type, void *value, entry_type_E declaration_type) {
    symbol_table_entry_T *entry = malloc(sizeof(symbol_table_entry_T));

    entry->name = name;
    entry->type = type;
    entry->value = value;
    entry->declaration_type = declaration_type;
    entry->next = NULL;

    return entry;
}

/**
 * Inserts an entry into the symbol table.
 * @param st The symbol table.
 * @param ste The entry to insert.
 * @return 1 on success, 0 on failure.
 */
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


/**
 * Finds an entry in the symbol table.
 * @param st The symbol table.
 * @param name The name of the entry to find.
 * @return The found entry or NULL if not found.
 */
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

/**
 * Resizes the symbol table.
 * @param st The symbol table.
 * @return 1 on success, 0 on failure.
 */
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

/**
 * Prints the symbol table.
 * @param st The symbol table.
 */
void symbol_table_print(symbol_table_T *st) {
    for(int i = 0; i < st->capacity; ++i) {
        symbol_table_entry_T *cur = st->buckets[i];

        while(cur) {
            printf("name: %s, type: %d, value: %p\n", cur->name, cur->type, cur->value);
            cur = cur->next;
        }
    }
}


