#include "../include/parser/grammer.h"
#include <stdlib.h>

/**
 * @brief Create a grammar
 * @param rules set of rules of the grammar
 * @param symbols set of symbols of the grammar
 * @return grammar
 */
grammer_T *init_grammer(set_T *rules, set_T *symbols) {
    grammer_T *gram = malloc(sizeof(grammer_T));

    gram->rules = rules;
    gram->symbols = symbols;

    return gram;
}

/**
 * @brief Get all terminal symbols from a set of symbols of a grammar
 * @param symbols set of symbols
 * @return array of pointers to terminal symbols
 */
token_T **terminals_in_symbol_set(set_T *symbols) {
    token_T **terms;
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc = 0;

    /* count number of terminal symbols */
    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL)
            termc++;
        cn = cn->next;
    }

    terms = malloc(sizeof(token_T *) * termc);
    termc = 0;

    /* add terminal symbols to array */
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

/**
 * @brief Get all terminal symbols from a set of symbols of a grammar and the terminal symbol "$"
 * @param symbols set of symbols
 * @return array of pointers to terminal symbols
 */
token_T **terminals_in_symbol_set_and_dollar(set_T *symbols) {
    token_T **terms = terminals_in_symbol_set(symbols);

    terms = realloc(terms, (n_terminals_in_symbol_set(symbols) + 1) * sizeof(token_T *));
    terms[n_terminals_in_symbol_set(symbols)] = init_token("$", TOK_eof);

    return terms;
}

/**
 * @brief Get number of terminal symbols in a set of symbols of a grammar
 * @param symbols set of symbols
 * @return number of terminal symbols
 */
size_t n_terminals_in_symbol_set(set_T *symbols) {
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc = 0;

    /* count number of terminal symbols */
    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == TERMINAL)
            termc++;
        cn = cn->next;
    }

    return termc;
}

/**
 * @brief Get all non-terminal symbols from a set of symbols of a grammar
 * @param symbols set of symbols
 * @return array of pointers to non-terminal symbols
 */
non_terminal_T **non_terminals_in_symbol_set(set_T *symbols) {
    non_terminal_T **nterms;
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc = 0;

    /* count number of non-terminal symbols */
    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    nterms = malloc(sizeof(non_terminal_T *) * termc);
    termc = 0;

    /* add non-terminal symbols to array */
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

/**
 * @brief Get number of non-terminal symbols in a set of symbols of a grammar
 * @param symbols set of symbols
 * @return number of non-terminal symbols
 */
size_t n_non_terminals_in_symbol_set(set_T *symbols) {
    symbol_T *cur_sym;
    set_node_T *cn = symbols->head;
    int i, termc = 0;

    /* count number of non-terminal symbols */
    for(i = 0; i < symbols->size; ++i) {
        cur_sym = cn->data;
        if(cur_sym->sym_type == NON_TERMINAL)
            termc++;
        cn = cn->next;
    }

    return termc;
}

/**
 * @brief Find the index of a rule in the grammar, given the right side of the rule
 * @param gram grammar
 * @param right right side of rule
 * @param right_size number of symbols in right side of rule
 * @return index of rule in grammar or -1 if not found
 */
size_t find_right_grammer_index(const grammer_T *gram, symbol_T **right, size_t right_size) {
    int i ,j, equ = 0;
    set_node_T *cn = gram->rules->head;
    rule_T *rule;   

    /* find rule in grammar */
    for(i = 0; i < gram->rules->size; ++i) {
        rule = cn->data;
        if(rule->right_size == right_size) {
            equ = 1;
            for(j = 0; j < right_size; ++j) {
                if(symbol_cmp(rule->right[j], right[j])) {
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
