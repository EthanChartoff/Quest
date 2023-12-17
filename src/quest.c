#include "include/quest.h"
#include "include/lexer.h"
#include "include/io.h"
#include "include/token_type.h"
#include "include/parser.h"
#include <stdlib.h>
#include <stdio.h>

void compile(char *src) {
    lexer_T* lex = init_lexer(src);
    token_T* tk = 0;
    // parser_T* par = init_parser(lex);
    // AST_T* root = parser_parse(par);

    // printf("%p\n", root->children->items);

    while((tk = lexer_next_token(lex))->type != TOK_EOF)
        printf("%s\n", token_to_str(tk));
}

void compile_file(const char *filename) {
    char *src = read_file(filename);
    compile(src);
    free(src);
}
