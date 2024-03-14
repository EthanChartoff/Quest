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
    symbol_T *E_s =  init_symbol_non_terminal(init_non_terminal("S'", NON_TERM_start));
    symbol_T *E = init_symbol_non_terminal(init_non_terminal("S", NON_TERM_S));
    symbol_T *T = init_symbol_non_terminal(init_non_terminal("E" ,NON_TERM_E));
    symbol_T *F = init_symbol_non_terminal(init_non_terminal("F", NON_TERM_F));

    symbol_T *p = init_symbol_terminal(init_token("+", TOK_PLUS));
    symbol_T *x = init_symbol_terminal(init_token("*", TOK_STAR));
    symbol_T *lp = init_symbol_terminal(init_token("(", TOK_LPAREN));
    symbol_T *rp = init_symbol_terminal(init_token(")", TOK_RPAREN));
    symbol_T *id = init_symbol_terminal(init_token("id", TOK_IDENTIFIER));

    symbol_T *EpT[3] = {x, p, E};

    rule_T *start_r = init_rule(E_s->symbol->non_terminal, &E, 1);
    rule_T *EtoEpT = init_rule(E->symbol->non_terminal, EpT, 3);
    rule_T *EtoT = init_rule(E->symbol->non_terminal, &T, 1);
    // rule_T *TtoTxF = init_rule(T->symbol->non_terminal, TxF, 3);
    rule_T *TtoF = init_rule(T->symbol->non_terminal, &F, 1);
    // rule_T *E_paren = init_rule(F->symbol->non_terminal, l_E_r, 1);
    rule_T *idr = init_rule(F->symbol->non_terminal, &id, 1);


    rule_T *rules[] = {start_r, EtoEpT, EtoT, TtoF, idr}; 
    symbol_T *symbols[] = {E_s, E, T, F, p, x, lp, rp, id};

    grammer_T gram = {
        rules,
        7,
        symbols,
        9
    };


    lr_item_set_T *itms = lr1_items(&gram, init_lr_item(start_r, 0, init_token("eof", TOK_eof)));
    
    for(int i = 0; i < itms->size; ++i) {
        printf("%zu - %s, %s\n", itms->set[i]->dot_index, itms->set[i]->rule->left->value, itms->set[i]->lookahead->value);
    }
    return 0;
}