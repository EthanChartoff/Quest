#include "include/macros.h"
#include "include/quest.h"
#include "include/token.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Please specify input file. \n");
        return 1;
    }
    compile_file(argv[1]);

    printf("%d, %d", TOK2_plus, TOK_plus);
    return 0;
}