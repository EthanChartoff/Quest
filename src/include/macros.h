#ifndef QUEST_MACROS_H
#define QUEST_MACROS_H

#define TOKS_PATH "/home/goodman/school/Quest/src/include/lexer/tokens.h"
#define LEXER_DFA_PATH "/home/goodman/school/Quest/build/lexer_dfa.dat"
#define LEXER_DFA_STATES_PATH "/home/goodman/school/Quest/build/lexer_dfa_states.dat"
#define LEXER_DFA_STATES_DETAILS_PATH "/home/goodman/school/Quest/build/lexer_dfa_states_details.dat"

#define PARSER_ACTION_PATH "/home/goodman/school/Quest/build/parser_action.dat"
#define PARSER_ACTION_PRETTY_PATH "/home/goodman/school/Quest/build/parser_action_pretty.dat"
#define PARSER_GOTO_PATH "/home/goodman/school/Quest/build/parser_goto.dat"
#define PARSER_GOTO_PRETTY_PATH "/home/goodman/school/Quest/build/parser_goto_pretty.dat"
#define PARSER_BNF "/home/goodman/school/Quest/resources/language/quest.ebnf"
#define PARSER_BNF_NON_TERMINALS "/home/goodman/school/Quest/src/include/parser/non_terminals_bnf.h"
#define PARSER_BNF_XLAT "/home/goodman/school/Quest/resources/slr_xlat"
#define PARSER_SLR_BIN "/home/goodman/school/Quest/build/slr.bin"

#define PARSER_NON_TERMINALS_HEADER "\
#ifndef NON_TERM \n\
#define NON_TERM(name, symbol) \n\
#endif \n\
\n\
NON_TERM(null, \"\") \n\
NON_TERM(start, \"S'\") \n\
"
#define PARSER_NON_TERMINALS_FOOTER "\n#undef NON_TERM"


#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define IF_SIGN(x) if((x)) {return ((x) / (abs(x)));} 

#define print_item(x) printf("[%s -> %s {%zu}] rs: %d\n", x->rule->left->value, x->rule->right[0]->sym_type == TERMINAL ? x->rule->right[0]->symbol->terminal->value : x->rule->right[0]->symbol->non_terminal->value, x->dot_index ,x->rule->right_size);


#endif