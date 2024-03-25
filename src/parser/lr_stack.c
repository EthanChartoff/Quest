#include "../include/parser/lr_stack.h"
#include "../utils/err/err.h"
#include <stdlib.h>

lr_stack_T *init_lr_stack(size_t alloc_size) {
    lr_stack_T *s = malloc(sizeof(lr_stack_T));
    if(!s)
        thrw(ALLOC_ERR);

    s->top = NULL;
    s->size = 0;
    s->capacity = 0;
    s->alloc_size = alloc_size;

    return s;
}

void lr_stack_push(lr_stack_T *s, int data) {
    if(lr_stack_full(s))
        s->top = realloc(s->top, sizeof(int) * s->capacity + s->alloc_size);

    s->top[s->size] = data;
    s->size++;
    s->capacity += s->alloc_size;
}

int lr_stack_pop(lr_stack_T *s) {
    if(IS_EMPTY(s))
        return -1;

    s->size--;
    return s->top[s->size];
}

int lr_stack_peek(lr_stack_T *s) {
    if(IS_EMPTY(s))
        return -1;

    return s->top[s->size - 1];
}   

int lr_stack_peek_inside(lr_stack_T *s, int n) {
    int i, tmp;
    int items[n];

    for(i = 0; i < n; ++i) {
        items[i] = lr_stack_pop(s);
    }
    tmp = lr_stack_peek(s);
    for(i = 0; i < n; ++i) {
        lr_stack_push(s, items[n - i - 1]);
    }
    return tmp;
}

int lr_stack_full(lr_stack_T *s) {
    return s->capacity <= s->size; 
}

void lr_stack_clear(lr_stack_T *s) {
    while (!IS_EMPTY(s))
        lr_stack_pop(s);
}