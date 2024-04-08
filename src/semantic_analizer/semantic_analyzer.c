#include "../include/semantic_analizer/semantic_analyzer.h"
#include "../utils/DS/include/stack.h"
#include "../utils/symbol_table/include/symbol_table_tree.h"

#include <stdio.h>

static void build_ast_rec(parse_tree_node_T *tree, sdt_T *sdt, stack_T *ast_s, symbol_table_tree_T *stt) {
    if(tree == NULL)
        return;

    if(tree->symbol->sym_type == TERMINAL) {
        stack_push(ast_s, init_ast_leaf(tree->symbol));
        return;
    }
        
    int i;

    for(i = 0; i < tree->n_children; ++i)
        build_ast_rec(tree->children[i], sdt, ast_s, stt); 
    
    if(sdt->definitions[tree->rule_index]->definition) 
        sdt->definitions[tree->rule_index]->definition(ast_s, tree, stt->root->table);    
}


ast_node_T *build_ast(parse_tree_T *tree, sdt_T *sdt) {
    stack_T *ast_s = stack_init();
    symbol_table_tree_T *stt = init_symbol_table_tree(
        init_symbol_table_tree_leaf(init_symbol_table_default())
    );
    build_ast_rec(tree->root, sdt, ast_s, stt);

    symbol_table_print(stt->root->table);
    return stack_pop(ast_s);
}

