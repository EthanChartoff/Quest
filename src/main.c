#include "include/lexer/token.h"
#include "include/parser/grammer.h"
#include "include/parser/item_set.h"
#include "include/parser/lr_item.h"
#include "include/parser/non_terminal.h"
#include "include/parser/rule.h"
#include "include/parser/symbol.h"
#include "include/quest.h"
#include "utils/DS/include/generic_set.h"
#include "include/macros.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    // if(argc < 2) {
    //     printf("Please specify input file. \n");
    //     return 1;
    // }
    
    // compile_file(argv[1]);
    // init_default_dfa();
    symbol_T *E_s =  init_symbol_non_terminal(init_non_terminal("E'", NON_TERM_start));
    symbol_T *E = init_symbol_non_terminal(init_non_terminal("E", NON_TERM_E));
    symbol_T *T = init_symbol_non_terminal(init_non_terminal("T" ,NON_TERM_T));
    symbol_T *F = init_symbol_non_terminal(init_non_terminal("F" ,NON_TERM_F));

    symbol_T *p = init_symbol_terminal(init_token("+", TOK_PLUS));
    symbol_T *x = init_symbol_terminal(init_token("*", TOK_STAR));
    symbol_T *id = init_symbol_terminal(init_token("id", TOK_IDENTIFIER));
    symbol_T *lp = init_symbol_terminal(init_token("(", TOK_LPAREN));
    symbol_T *rp = init_symbol_terminal(init_token(")", TOK_RPAREN));

    symbol_T *EpT[] = {E, p, T};
    symbol_T *TxF[] = {T, x, F};
    symbol_T *lEr[] = {lp, E, rp};


    rule_T *start = init_rule(E_s->symbol->non_terminal, &E, 1);
    rule_T *EEpT = init_rule(E->symbol->non_terminal, EpT, 2);
    rule_T *ET = init_rule(E->symbol->non_terminal, &T, 1);
    rule_T *TTxF = init_rule(T->symbol->non_terminal, TxF, 2);
    rule_T *TF = init_rule(T->symbol->non_terminal, &F, 1);
    rule_T *FlEr = init_rule(F->symbol->non_terminal, lEr, 2);
    rule_T *Fid = init_rule(F->symbol->non_terminal, &id, 1);

    set_T *rules = set_init(rule_cmp_generic);
    set_add(rules, start);
    set_add(rules, EEpT);
    set_add(rules, ET);
    set_add(rules, TTxF);
    set_add(rules, TF);
    set_add(rules, FlEr);
    set_add(rules, Fid);

    
    set_T *syms = set_init(token_cmp_generic);
    set_add(syms, p);
    set_add(syms, x);
    set_add(syms, id);
    set_add(syms, lp);
    set_add(syms, rp);
    
    grammer_T *gram = init_grammer(rules, syms);

    set_T *la = set_init(token_cmp_generic);
    set_add(la, init_token("eof", TOK_eof));

    set_T *tmp = set_init(lr_item_cmp_generic);
    set_add(tmp, init_lr_item(start, 0, NULL));

    set_T *itms = lr0_items(gram, init_lr_item(start, 0, NULL)), *itm_itm;
    // printf("\n%d\n", itms->size);
    set_node_T *curr = itms->head, *cur_itm;
    lr_item_T *itm_itm_itm;

    for(int i = 0; i < itms->size; ++i) {
        itm_itm = curr->data;
        
        // print_item(((lr_item_T *) itm_itm));

        printf("\n%d\n", i);
        cur_itm = itm_itm->head;
        // printf("\n%d\n", itm_itm->size);
        for(int j = 0; j < itm_itm->size; ++j) {
            itm_itm_itm = cur_itm->data;
            print_item(itm_itm_itm);
            cur_itm = cur_itm->next;
        }
        curr = curr->next;
    }
    return 0;
}