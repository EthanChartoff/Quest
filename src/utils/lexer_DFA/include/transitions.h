#include "lexer_DFA.h"

void add_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_id_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_num_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_first_char_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_second_char_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_first_string_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);
void add_second_string_transition(lexer_dfa_T *dfa, lexer_dfa_state_T *src_state, int dest_state_index, int c);