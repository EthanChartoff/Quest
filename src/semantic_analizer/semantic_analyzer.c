#include "../include/semantic_analizer/semantic_analyzer.h"
#include "../utils/DS/include/stack.h"
#include "../utils/symbol_table/include/symbol_table_tree.h"

#include <stdio.h>

static void build_ast_rec(parse_tree_node_T *tree, sdt_T *sdt, stack_T *ast_s, stack_T *st_s) {
    if(tree == NULL)
        return;

    if(tree->symbol->sym_type == TERMINAL) {
        stack_push(ast_s, init_ast_leaf(tree->symbol));
        printf("%s\n", tree->symbol->symbol->terminal->value);
        return;
    }
        
    int i;

    for(i = 0; i < tree->n_children; ++i)
        build_ast_rec(tree->children[i], sdt, ast_s, st_s); 
    
    if(sdt->definitions[tree->rule_index]->definition) 
        sdt->definitions[tree->rule_index]->definition(ast_s, tree, st_s);    
}


ast_node_T *build_ast(parse_tree_T *tree, sdt_T *sdt) {
    stack_T *ast_s = stack_init();
    stack_T *st_s = stack_init();
    stack_push(st_s, init_symbol_table_tree_leaf(init_symbol_table_default()));
    
    build_ast_rec(tree->root, sdt, ast_s, st_s);

    symbol_table_tree_node_T *sym_tbl = stack_pop(st_s);
    symbol_table_print(sym_tbl->table);
    return stack_pop(ast_s);
}

