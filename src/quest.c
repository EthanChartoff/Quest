#include "include/quest.h"
#include "include/lexer.h"
#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

void compile(char *src) {
    lexer_T* lex = init_lexer(src);
    token_T* tk = 0;

    while((tk = lexer_next_token(lex))->type != TOK_eof) {
        if(tk->type == TOK_UNKNOWN) {
            printf("token is unknown: TOKEN(%s) (%d)\n", tk->value, tk->type);
            // exit(EXIT_FAILURE);
        } else {
            printf("TOKEN(%s) (%d)\n", tk->value, tk->type);
        }
    }
}

void compile_file(const char *filename) {
    char *src = read_file(filename);
    compile(src);
    free(src);
}
