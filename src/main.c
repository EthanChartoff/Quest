#include "include/lexer/token.h"
#include "include/parser/action_table.h"
#include "include/parser/bnf.h"
#include "include/parser/goto_table.h"
#include "include/parser/grammer.h"
#include "include/parser/lr_item.h"
#include "include/parser/non_terminal.h"
#include "include/parser/rule.h"
#include "include/parser/slr.h"
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
    
    // action_tbl_print_to_file(slr->action, PARSER_ACTION_PATH);
    // action_tbl_pretty_print_to_file(slr->action, PARSER_ACTION_PRETTY_PATH);
    // goto_tbl_print_to_file(slr->go_to, PARSER_GOTO_PATH);
    // goto_tbl_pretty_print_to_file(slr->go_to, PARSER_GOTO_PRETTY_PATH);
    

    // printf("\n%zu\n", follow(gram, init_non_terminal("F", NON_TERM_F))->size);
    // printf("\n%d\n", itms->size);
    // set_node_T *curr = itms->head, *cur_itm;
    // lr_item_T *itm_itm_itm;

    // for(int i = 0; i < itms->size; ++i) {
    //     itm_itm = curr->data;
        
    //     // print_item(((lr_item_T *) itm_itm));

    //     printf("\n%d\n", i);
    //     cur_itm = itm_itm->head;
    //     // printf("\n%d\n", itm_itm->size);
    //     for(int j = 0; j < itm_itm->size; ++j) {
    //         itm_itm_itm = cur_itm->data;
    //         print_item(itm_itm_itm);
    //         cur_itm = cur_itm->next;
    //     } 
    //     curr = curr->next;
    // }

    // bnf_make_non_terminals(PARSER_BNF);

    init_default_slr();
    return 0;
}