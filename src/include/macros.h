#ifndef QUEST_MACROS_H
#define QUEST_MACROS_H

#define TOKS_PATH "/home/goodman/school/Quest/src/include/lexer/tokens.h"
#define LEXER_DFA_PATH "/home/goodman/school/Quest/build/lexer_dfa.dat"
#define LEXER_DFA_STATES_PATH "/home/goodman/school/Quest/build/lexer_dfa_states.dat"
#define LEXER_DFA_STATES_DETAILS_PATH "/home/goodman/school/Quest/build/lexer_dfa_states_details.dat"

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define IF_SIGN(x) if((x)) {return ((x) / (abs(x)));} 

#define print_item(x) printf("[%s -> %s {%zu}] rs: %d\n", x->rule->left->value, x->rule->right[0]->sym_type == TERMINAL ? x->rule->right[0]->symbol->terminal->value : x->rule->right[0]->symbol->non_terminal->value, x->dot_index ,x->rule->right_size);


#endif