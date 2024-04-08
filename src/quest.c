#include "include/quest.h"
#include "include/lang.h"
#include "include/lexer/lexer.h"
#include "include/io.h"
#include "include/parser/parse_tree.h"
#include "include/parser/parser.h"
#include "include/semantic_analizer/semantic_analyzer.h"
#include "utils/DS/include/queue.h"
#include <stdlib.h>

void compile(char *src) {
    quest_T *q = init_quest(src);

    lexer_T* lex = q->lexer;
    parser_T *prs = q->parser;

    token_T* tk = 0;
    queue_T *queue = queue_init();

    do {
        tk = lexer_next_token(lex);

        if(tk->type == TOK_UNKNOWN) {
            // printf("token is unknown: TOKEN(%s) (%d)\n", tk->value, tk->type);
            // exit(EXIT_FAILURE);
        } else {
            queue_enqueue(queue, tk);
        }
    } while(tk->type != TOK_eof);
    
    parse_tree_T *tree = parse(prs, queue);
    parse_tree_traverse_postorder(tree->root, 0);

    ast_node_T *ast = build_ast(tree, q->sdt);
    traverse_ast(ast, 0); 
}

void compile_file(const char *filename) {
    char *src = read_file(filename);
    compile(src);
    free(src);
}
