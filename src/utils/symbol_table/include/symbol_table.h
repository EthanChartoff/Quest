//===--= symbol_table.h =---------------------------------------------===
//
// a symbol table 
//
//===-----------------------------------------------------------------===

#ifndef QUEST_SYMBOL_TABLE_H
#define QUEST_SYMBOL_TABLE_H

#define DEFAULT_INITIAL_CAPACITY 8 
#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_RESIZE_CONSTANT 2

#include <stddef.h>

typedef enum ENTRY_TYPES_ENUM {
    GLOBAL,
    LOCAL
} entry_type_E;
    

typedef struct SYMBOL_TABLE_ENTRY_STRUCT {
    char *name;
    int type;
    void *value;
    entry_type_E declaration_type;
    struct SYMBOL_TABLE_ENTRY_STRUCT *next;
} symbol_table_entry_T;

typedef struct SYMBOL_TABLE_STRUCT {
    size_t size;                                    // current entries in the symbol table
    size_t capacity;                                // number of entries that can be in the symbol table, is effected by load factor
    float load_factor;                              // load factor of table
    symbol_table_entry_T **buckets;                 // actual members of hash table. members are arranged in a chained table, meaning each member is using a linked list if there is any collision 
    unsigned int (*hash)(char *, size_t length);    // hash function of the table
} symbol_table_T;

symbol_table_T *init_symbol_table(unsigned int capacity, float load_factor, unsigned int (*hash)(char *, size_t length));
symbol_table_T *init_symbol_table_default();

symbol_table_entry_T *init_symbol_table_entry(char *name, int type, void *value, entry_type_E declaration_type);

unsigned int symbol_table_insert(symbol_table_T *st, symbol_table_entry_T *ste);
symbol_table_entry_T *symbol_table_find(symbol_table_T *st, char *name);
unsigned int symbol_table_resize(symbol_table_T *st);

void symbol_table_print(symbol_table_T *st);

#endif /* QUEST_SYMBOL_TABLE_H */