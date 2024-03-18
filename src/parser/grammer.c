#include "../include/parser/grammer.h"
#include <stdlib.h>


grammer_T *init_grammer(set_T *rules, set_T *symbols) {
    grammer_T *gram = malloc(sizeof(grammer_T));

    gram->rules = rules;
    gram->symbols = symbols;

    return gram;
}

token_T **terminals_in_symbol_set(set_T *symbols) {
    token_T **terms;
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL)
            termc++;
        cn = cn->next;
    }

    terms = malloc(sizeof(token_T *) * termc);
    termc = 0;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL) {
            terms[termc] = cur_sym->symbol->terminal;
            termc++;
        }
        cn = cn->next;
    }

    return terms;
}

size_t n_terminals_in_symbol_set(set_T *symbols) {
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL)
            termc++;
        cn = cn->next;
    }

    return termc;
}

non_terminal_T **non_terminals_in_symbol_set(set_T *symbols) {
    non_terminal_T **nterms;
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    nterms = malloc(sizeof(non_terminal_T *) * termc);
    termc = 0;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL) {
            nterms[termc] = cur_sym->symbol->non_terminal;
            termc++;
        }
        cn = cn->next;
    }

    return nterms;
}

size_t n_non_terminals_in_symbol_set(set_T *symbols) {
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    return termc;
}