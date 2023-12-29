#ifndef QUEST_LEXER_DFA_H
#define QUEST_LEXER_DFA_H
#include "../include/token.h"
#include <stddef.h>

int init_dfa(token_T* toks[], size_t n_toks, const char *filename);
int init_default_dfa();

#endif