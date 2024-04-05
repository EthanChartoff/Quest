#include "../include/semantic_analizer/semantic_analyzer.h"
#include "../utils/DS/include/stack.h"
#include <stdio.h>

static void build_ast_rec(parse_tree_node_T *tree, sdt_T *sdt, stack_T *ast_s) {
    if(tree == NULL)
        return;

    if(tree->symbol->sym_type == TERMINAL) {
        stack_push(ast_s, init_ast_leaf(tree->symbol));
        return;
    }
        
    int i;
    char *val = tree->symbol->sym_type == NON_TERMINAL 
        ? tree->symbol->symbol->non_terminal->value  
        : tree->symbol->symbol->terminal->value;

    for(i = 0; i < tree->n_children; ++i)
        build_ast_rec(tree->children[i], sdt, ast_s); 
    
    if(sdt->definitions[tree->rule_index]->definition) 
        sdt->definitions[tree->rule_index]->definition(ast_s, tree);    
}


ast_node_T *build_ast(parse_tree_T *tree, sdt_T *sdt) {
    stack_T *ast_s = stack_init();
    build_ast_rec(tree->root, sdt, ast_s);
    return stack_pop(ast_s);
}

