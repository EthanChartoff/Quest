#include "include/quest.h"
#include "include/lexer/lexer.h"
#include "include/io.h"
#include "include/macros.h"
#include "include/parser/parser.h"
#include "include/parser/slr.h"
#include "utils/DS/include/queue.h"
#include <stdlib.h>
#include <stdio.h>

void compile(char *src) {
    lexer_T* lex = init_lexer(src);
    token_T* tk = 0;
    queue_T *queue = queue_init();
    parser_T *prs = init_parser(init_default_slr());

    do {
        tk = lexer_next_token(lex);

        if(tk->type == TOK_UNKNOWN) {
            // printf("token is unknown: TOKEN(%s) (%d)\n", tk->value, tk->type);
            // exit(EXIT_FAILURE);
        } else {
            queue_enqueue(queue, tk);
        }
    } while(tk->type != TOK_eof);

    parse(prs, queue);    
}

void compile_file(const char *filename) {
    char *src = read_file(filename);
    compile(src);
    free(src);
}
