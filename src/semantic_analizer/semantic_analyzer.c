#include "../include/semantic_analizer/semantic_analyzer.h"
#include "../utils/DS/include/stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static ast_node_T *build_ast_rec(parse_tree_node_T *tree, sdt_T *sdt, stack_T *ast_s) {
    if(tree->symbol->sym_type == TERMINAL) {
        stack_push(ast_s, init_ast_leaf(tree->symbol));
        return NULL;
    }
        
    int i;
    ast_node_T **astns, *ast = NULL;

    for(i = 0; i < tree->n_children; ++i) {
        build_ast_rec(tree->children[i], sdt, ast_s);                
    }

    if(sdt->definitions[tree->rule_index]->definition)
        sdt->definitions[tree->rule_index]->definition(ast_s);
    
    // printf("%zu\n", ast_s->size);
    return stack_peek(ast_s);
}

ast_node_T *build_ast(parse_tree_T *tree) {
    stack_T *ast_s = stack_init();
    return build_ast_rec(tree->root, init_default_sdt(tree->rules, tree->n_rules), ast_s);
}

