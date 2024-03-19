#include "../include/parser/grammer.h"
#include <stdio.h>
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
    int i, termc = 0;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL)
            termc++;
        cn = cn->next;
    }

    terms = malloc(sizeof(token_T *) * termc);
    termc = 0;

    cn = symbols->head;
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

token_T **terminals_in_symbol_set_and_dollar(set_T *symbols) {
    token_T **terms = terminals_in_symbol_set(symbols);

    terms = realloc(terms, (n_terminals_in_symbol_set(symbols) + 1) * sizeof(token_T *));
    terms[n_terminals_in_symbol_set(symbols)] = init_token("", TOK_eof);

    return terms;
}

size_t n_terminals_in_symbol_set(set_T *symbols) {
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc = 0;

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
    int i, termc = 0;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    nterms = malloc(sizeof(non_terminal_T *) * termc);
    termc = 0;

    cn = symbols->head;
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
    int i, termc = 0;

    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    return termc;
}

size_t find_right_grammer_index(const grammer_T *gram, const symbol_T **right, const size_t right_size) {
    int i ,j, equ = 0;
    set_node_T *cn = gram->rules->head;
    rule_T *rule;   

    for(i = 0; i < gram->rules->size; ++i) {
        rule = cn->data;

        if(rule->right_size == right_size) {
            equ = 1;
            for(j = 0; j < right_size; ++j) {
                if(symbol_cmp(rule->right[i], right[i])) {
                    equ = 0;
                    break;
                }
            }
            if(equ)
                return i;
        }
        cn = cn->next;
    }

    return -1;
}