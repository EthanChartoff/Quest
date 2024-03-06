#include "include/lexer/token.h"
#include "include/parser/grammer.h"
#include "include/parser/lr_item.h"
#include "include/parser/rule.h"
#include "include/quest.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    // if(argc < 2) {
    //     printf("Please specify input file. \n");
    //     return 1;
    // }
    
    // compile_file(argv[1]);
    // init_default_dfa();
    token_T *sn =  init_token("lol1", TOK_AND);
    token_T *baa = init_token("lol2", TOK_ANDEQUEL);

    token_T *baasn[2] = {sn, baa};

    rule_T *goal = init_rule(init_token("goal", TOK_DO), &sn, 1);
    rule_T *sheepnoise1 = init_rule(sn, baasn, 2);
    rule_T *sheepnoise2 = init_rule(sn, &baa, 1);

    rule_T *rules[3] = {goal, sheepnoise1, sheepnoise2}; 
    grammer_T gram = {
        rules,
        3
    };

    lr_item_T **itms = closure(&gram, init_lr_item(goal, 0));
    
    for(int i = 0; i < 3; ++i) {
        printf("%s\n", itms[i]->rule->right[0]->value);
    }
    return 0;
}