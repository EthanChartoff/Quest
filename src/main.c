#include "include/lexer/token.h"
#include "include/parser/grammer.h"
#include "include/parser/item_set.h"
#include "include/parser/lr_item.h"
#include "include/parser/non_terminal.h"
#include "include/parser/rule.h"
#include "include/parser/symbol.h"
#include "include/quest.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    // if(argc < 2) {
    //     printf("Please specify input file. \n");
    //     return 1;
    // }
    
    // compile_file(argv[1]);
    // init_default_dfa();
    symbol_T *S_s =  init_symbol_non_terminal(init_non_terminal("S'", NON_TERM_start));
    symbol_T *S = init_symbol_non_terminal(init_non_terminal("S", NON_TERM_S));
    symbol_T *C = init_symbol_non_terminal(init_non_terminal("C" ,NON_TERM_C));

    symbol_T *d = init_symbol_terminal(init_token("d", TOK_DO));
    symbol_T *c = init_symbol_terminal(init_token("c", TOK_CASE));

    symbol_T *CC[] = {C, C};
    symbol_T *cC[] = {c, C};

    rule_T *start = init_rule(S_s->symbol->non_terminal, &S, 1);
    rule_T *SCC = init_rule(S->symbol->non_terminal, CC, 2);
    rule_T *CcC = init_rule(C->symbol->non_terminal, cC, 2);
    rule_T *Cd = init_rule(C->symbol->non_terminal, &d, 1);


    rule_T *rules[] = {start, SCC, CcC, Cd}; 
    symbol_T *symbols[] = {S_s, S, C, d, c};

    grammer_T gram = {
        rules,
        4,
        symbols,
        5
    };


    lr_item_set_T *itms = lr1_items(&gram, init_lr_item(start, 0, init_token("eof", TOK_eof)));
    
    for(int i = 0; i < itms->size; ++i) {
        printf("%zu - %s, %s\n", itms->set[i]->dot_index, itms->set[i]->rule->left->value, itms->set[i]->lookahead->value);
    }
    return 0;
}