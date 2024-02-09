#include "include/lexer_DFA.h"
#include <ctype.h>
#include <stdio.h>

// add transition for keyword states
void add_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    if(
        is_id(c) && 
        (dfa->flags & ADD_IDENTIFIER_STATE_FLAG) &&
        (dfa->last_states[IDENTIFIER]) &&
        src_state->type == IDENTIFIER
    ) {
        dfa->DFA[src_state->index][c] = dfa->last_states[IDENTIFIER]->index;
    }
    else {
        dfa->DFA[src_state->index][c] = -1;
    }
}

// add transition for id state according to the languages rules
// also add transition from first state to id state
void add_id_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    if(is_id(c)) {
        dfa->DFA[src_state->index][c] = dest_state_index;
        dfa->DFA[0][c] = dest_state_index;
    } else {
        dfa->DFA[src_state->index][c] = -1;
    }
}

// add transition for num state according to the languages rules
// also add transition from first state to num state
void add_num_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    if(isdigit(c)) {
        dfa->DFA[src_state->index][c] = dest_state_index;
        dfa->DFA[0][c] = dest_state_index;
    } else {
        dfa->DFA[src_state->index][c] = -1;
    }
}

// add transition for first char state according to the languages rules
// also add transition from first state to first char state
void add_first_char_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
        // if input is not single quotes
        if(is_single_quotes(c)) {
            dfa->DFA[src_state->index][c] = dest_state_index;
            dfa->DFA[0][c] = src_state->index;
        } else {
            dfa->DFA[src_state->index][c] = src_state->index;
        }
}

// add transition for second char state 
// note: the state isn't suppose to have a transition to another state,
//       its the end of the token
void add_second_char_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    dfa->DFA[src_state->index][c] = -1;
}

// add transition for first string state according to the languages rules
// also add transition from first state to first string state
void add_first_string_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    // if input is quotes
    if(is_quotes(c)) {
        dfa->DFA[src_state->index][c] = dest_state_index;
        dfa->DFA[0][c] = src_state->index;
    } else {
        dfa->DFA[src_state->index][c] = src_state->index;
    }
}

// add transition for second string state 
// note: the state isn't suppose to have a transition to another state,
//       its the end of the token
void add_second_string_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c) {
    dfa->DFA[src_state->index][c] = -1;
}