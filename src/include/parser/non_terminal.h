#ifndef QUEST_NON_TERMINAL
#define QUEST_NON_TERMINAL

typedef enum NON_TERMINAL_ENUM {
    #define NON_TERM(name, symbol) NON_TERM_##name,
    #include "non_terminals.h"
    #undef NON_TERM
    NUM_NON_TERM
} non_terminal_E;


typedef struct NON_TERMINAL_T {
    non_terminal_E type;
    char *value;
} non_terminal_T;

non_terminal_T *init_non_terminal(char *value, non_terminal_E type);

#endif