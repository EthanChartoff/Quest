#include "../include/semantic_analizer/semantic_analyzer.h"
#include "../utils/DS//include/stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static ast_node_T *build_ast_rec(parse_tree_node_T *tree, sdt_T *sdt, stack_T *ast_s) {
    if(tree->rule_index == -1) {
        stack_push(ast_s, init_ast_leaf(tree->symbol));
        return NULL;
    }
        
    int i;
    ast_node_T **astns, *ast = NULL;

    for(i = 0; i < tree->n_children; ++i) {
        build_ast_rec(tree->children[i], sdt, ast_s);                
    }

    if(sdt->definitions[tree->rule_index]->definition) {
        astns = malloc(sizeof(ast_node_T *) * tree->n_children);
        for(i = 0; i < tree->n_children; ++i) {
            astns[i] = stack_pop(ast_s);
        }
        ast = sdt->definitions[tree->rule_index]->definition(tree, astns);
        stack_push(ast_s, ast);
    }

    return stack_peek(ast_s);
}

ast_node_T *build_ast(parse_tree_T *tree) {
    stack_T *ast_s = stack_init();
    return build_ast_rec(tree->root, init_default_sdt(tree->rules, tree->n_rules), ast_s);
}