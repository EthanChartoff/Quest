#include "include/quest.h"
#include "include/lexer.h"
#include "utils/lexer_DFA/include/lexer_DFA.h"
#include "include/macros.h"
#include "include/lexer_automata.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Please specify input file. \n");
        return 1;
    }

    compile_file(argv[1]);
    // init_def ault_dfa();

    return 0;
}