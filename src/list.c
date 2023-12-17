#include "include/list.h"
#include <stdlib.h>
#include <stdio.h>

list_T* init_list(size_t item_size) {
    list_T* list = calloc(1, sizeof(list_T));
    list->size = 0;
    list->item_size = item_size;
    list->items = 0;

    return list;
}

void list_add(list_T* list, void* item) {
    if(!list->items)
        list->items = calloc(1, list->item_size);
    else 
        list->items = realloc(list->items, list->item_size * list->size);
    
    list->items[list->size] = item;
    list->size++;
}