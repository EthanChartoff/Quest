#include "include/lang.h"
#include "include/parser/lr_item.h"
#include "include/parser/rule.h"
#include "include/parser/slr.h"
#include "include/macros.h"
#include "include/parser/bnf.h"
#include "include/parser/symbol.h"
#include "utils/DS/include/generic_set.h"


// TODO: make a sysmtem that doesnt need to have all these defs
static void init_default_lang() {    
    /*
        symbols
    */
    set_T *syms = set_init(symbol_cmp_generic);

    symbol_T *start = init_symbol_non_terminal(init_non_terminal("S'", NON_TERM_start));
    symbol_T *labeled_statement = init_symbol_non_terminal(init_non_terminal("labeled_statement", NON_TERM_labeled_statement));
    symbol_T *iteration_statement = init_symbol_non_terminal(init_non_terminal("iteration_statement", NON_TERM_iteration_statement));
    symbol_T *selection_statement = init_symbol_non_terminal(init_non_terminal("selection_statement", NON_TERM_selection_statement));
    symbol_T *compound_statement = init_symbol_non_terminal(init_non_terminal("compound_statement", NON_TERM_compound_statement));
    symbol_T *unary_operator = init_symbol_non_terminal(init_non_terminal("unary_operator", NON_TERM_unary_operator));
    symbol_T *assignment_operator = init_symbol_non_terminal(init_non_terminal("assignment_operator", NON_TERM_assignment_operator));
    symbol_T *expression = init_symbol_non_terminal(init_non_terminal("expression", NON_TERM_expression));
    symbol_T *primary_expression = init_symbol_non_terminal(init_non_terminal("primary_expression", NON_TERM_primary_expression));
    symbol_T *assignment_expression = init_symbol_non_terminal(init_non_terminal("assignment_expression", NON_TERM_assignment_expression));
    symbol_T *postfix_expression = init_symbol_non_terminal(init_non_terminal("postfix_expression", NON_TERM_postfix_expression));
    symbol_T *unary_expression = init_symbol_non_terminal(init_non_terminal("unary_expression", NON_TERM_unary_expression));
    symbol_T *multiplicative_expression = init_symbol_non_terminal(init_non_terminal("multiplicative_expression", NON_TERM_multiplicative_expression));
    symbol_T *additive_expression = init_symbol_non_terminal(init_non_terminal("additive_expression", NON_TERM_additive_expression));
    symbol_T *shift_expression = init_symbol_non_terminal(init_non_terminal("shift_expression", NON_TERM_shift_expression));
    symbol_T *relational_expression = init_symbol_non_terminal(init_non_terminal("relational_expression", NON_TERM_relational_expression));
    symbol_T *equality_expression = init_symbol_non_terminal(init_non_terminal("equality_expression", NON_TERM_equality_expression));
    symbol_T *and_expression = init_symbol_non_terminal(init_non_terminal("and_expression", NON_TERM_and_expression));
    symbol_T *exclusive_or_expression = init_symbol_non_terminal(init_non_terminal("exclusive_or_expression", NON_TERM_exclusive_or_expression));
    symbol_T *inclusive_or_expression = init_symbol_non_terminal(init_non_terminal("inclusive_or_expression", NON_TERM_inclusive_or_expression));
    symbol_T *logical_and_expression = init_symbol_non_terminal(init_non_terminal("logical_and_expression", NON_TERM_logical_and_expression));
    symbol_T *logical_or_expression = init_symbol_non_terminal(init_non_terminal("logical_or_expression", NON_TERM_logical_or_expression));
    symbol_T *constant_expression = init_symbol_non_terminal(init_non_terminal("constant_expression", NON_TERM_constant_expression));
    symbol_T *expression_statement = init_symbol_non_terminal(init_non_terminal("expression_statement", NON_TERM_expression_statement));
    symbol_T *parameter_list = init_symbol_non_terminal(init_non_terminal("parameter_list", NON_TERM_parameter_list));
    symbol_T *function_definition = init_symbol_non_terminal(init_non_terminal("function_definition", NON_TERM_function_definition));
    symbol_T *type_specifier = init_symbol_non_terminal(init_non_terminal("type_specifier", NON_TERM_type_specifier));
    symbol_T *declaration = init_symbol_non_terminal(init_non_terminal("declaration", NON_TERM_declaration));
    symbol_T *statement = init_symbol_non_terminal(init_non_terminal("statement", NON_TERM_statement));
    symbol_T *statement_list = init_symbol_non_terminal(init_non_terminal("statement_list", NON_TERM_statement_list));
    symbol_T *program = init_symbol_non_terminal(init_non_terminal("program", NON_TERM_program));

    set_add(syms, start);
    set_add(syms, labeled_statement);
    set_add(syms, iteration_statement);
    set_add(syms, selection_statement);
    set_add(syms, compound_statement);
    set_add(syms, unary_operator);
    set_add(syms, assignment_operator);
    set_add(syms, expression);
    set_add(syms, primary_expression);
    set_add(syms, assignment_expression);
    set_add(syms, postfix_expression);
    set_add(syms, unary_expression);
    set_add(syms, multiplicative_expression);
    set_add(syms, additive_expression);
    set_add(syms, shift_expression);
    set_add(syms, relational_expression);
    set_add(syms, equality_expression);
    set_add(syms, and_expression);
    set_add(syms, exclusive_or_expression);
    set_add(syms, inclusive_or_expression);
    set_add(syms, logical_and_expression);
    set_add(syms, logical_or_expression);
    set_add(syms, constant_expression);
    set_add(syms, expression_statement);
    set_add(syms, parameter_list);
    set_add(syms, function_definition);
    set_add(syms, type_specifier);
    set_add(syms, declaration);
    set_add(syms, statement);
    set_add(syms, statement_list);
    set_add(syms, program);


    symbol_T *logical_or = init_symbol_terminal(init_token("||", TOK_OR));
    symbol_T *logical_and = init_symbol_terminal(init_token("&&", TOK_AND));
    symbol_T *bitor = init_symbol_terminal(init_token("|", TOK_BITOR));
    symbol_T *bitxor = init_symbol_terminal(init_token("^", TOK_BITXOR));
    symbol_T *bitand = init_symbol_terminal(init_token("&", TOK_BITAND));
    symbol_T *equal_equal = init_symbol_terminal(init_token("==", TOK_EQUELEQUEL));
    symbol_T *not_equal = init_symbol_terminal(init_token("!=", TOK_NOTEQUEL));
    symbol_T *less = init_symbol_terminal(init_token("<", TOK_LESSER));
    symbol_T *less_equal = init_symbol_terminal(init_token("<=", TOK_LESSEREQUEL));
    symbol_T *greater = init_symbol_terminal(init_token(">", TOK_GREATER));
    symbol_T *greater_equal = init_symbol_terminal(init_token(">=", TOK_GREATEREQUEL));
    symbol_T *lshift = init_symbol_terminal(init_token("<<", TOK_SHIFTLEFT));
    symbol_T *rshift = init_symbol_terminal(init_token(">>", TOK_SHIFTRIGHT));
    symbol_T *plus = init_symbol_terminal(init_token("+", TOK_PLUS));
    symbol_T *minus = init_symbol_terminal(init_token("-", TOK_MINUS));
    symbol_T *divide = init_symbol_terminal(init_token("/", TOK_SLASH));
    symbol_T *multiply = init_symbol_terminal(init_token("*", TOK_STAR));
    symbol_T *mod = init_symbol_terminal(init_token("%", TOK_PRECENT));
    symbol_T *not = init_symbol_terminal(init_token("!", TOK_NOT));
    symbol_T *bitnot = init_symbol_terminal(init_token("~", TOK_BITNOT));

    symbol_T *assign = init_symbol_terminal(init_token("=", TOK_EQUEL));
    symbol_T *assign_plus = init_symbol_terminal(init_token("+=", TOK_PLUSEQUEL));
    symbol_T *assign_minus = init_symbol_terminal(init_token("-=", TOK_MINUSEQUEL));
    symbol_T *assign_multiply = init_symbol_terminal(init_token("*=", TOK_STAREQUEL));
    symbol_T *assign_divide = init_symbol_terminal(init_token("/=", TOK_SLASHEQUEL));
    symbol_T *assign_mod = init_symbol_terminal(init_token("%=", TOK_PRECENTEQUEL));
    symbol_T *assign_lshift = init_symbol_terminal(init_token("<<=", TOK_SHIFTLEFTEQUEL));
    symbol_T *assign_rshift = init_symbol_terminal(init_token(">>=", TOK_SHIFTRIGHTEQUEL));
    symbol_T *assign_bitand = init_symbol_terminal(init_token("&=", TOK_ANDEQUEL));
    symbol_T *assign_bitor = init_symbol_terminal(init_token("|=", TOK_OREQUEL));
    symbol_T *assign_bitxor = init_symbol_terminal(init_token("^=", TOK_XOREQUEL));

    symbol_T *comma = init_symbol_terminal(init_token(",", TOK_COMMA));
    symbol_T *semicolon = init_symbol_terminal(init_token(";", TOK_SEMICOLON));
    symbol_T *lparen = init_symbol_terminal(init_token("(", TOK_LPAREN));
    symbol_T *rparen = init_symbol_terminal(init_token(")", TOK_RPAREN));
    symbol_T *lbracket = init_symbol_terminal(init_token("[", TOK_LBRACK));
    symbol_T *rbracket = init_symbol_terminal(init_token("]", TOK_RBRACK));
    symbol_T *lbrace = init_symbol_terminal(init_token("{", TOK_LBRACE));
    symbol_T *rbrace = init_symbol_terminal(init_token("}", TOK_RBRACE));

    symbol_T *if_tok = init_symbol_terminal(init_token("if", TOK_IF));
    symbol_T *else_tok = init_symbol_terminal(init_token("else", TOK_ELSE));
    symbol_T *while_tok = init_symbol_terminal(init_token("while", TOK_WHILE));

    symbol_T *id = init_symbol_terminal(init_token("id", TOK_IDENTIFIER));
    symbol_T *num = init_symbol_terminal(init_token("num", TOK_NUMBER_CONSTANT));

    symbol_T *int_tok = init_symbol_terminal(init_token("int", TOK_INT));
    symbol_T *float_tok = init_symbol_terminal(init_token("float", TOK_FLOAT));
    symbol_T *char_tok = init_symbol_terminal(init_token("char", TOK_CHAR));
    symbol_T *void_tok = init_symbol_terminal(init_token("void", TOK_VOID));

    symbol_T *return_tok = init_symbol_terminal(init_token("ret", TOK_RET));

    set_add(syms, logical_or);
    set_add(syms, logical_and);
    set_add(syms, bitor);
    set_add(syms, bitxor);
    set_add(syms, bitand);
    set_add(syms, equal_equal);
    set_add(syms, not_equal);
    set_add(syms, less);
    set_add(syms, less_equal);
    set_add(syms, greater);
    set_add(syms, greater_equal);
    set_add(syms, lshift);
    set_add(syms, rshift);
    set_add(syms, plus);
    set_add(syms, minus);
    set_add(syms, divide);
    set_add(syms, multiply);
    set_add(syms, mod);
    set_add(syms, not);
    set_add(syms, bitnot);
    set_add(syms, assign);
    set_add(syms, assign_plus);
    set_add(syms, assign_minus);
    set_add(syms, assign_multiply);
    set_add(syms, assign_divide);
    set_add(syms, assign_mod);
    set_add(syms, assign_lshift);
    set_add(syms, assign_rshift);
    set_add(syms, assign_bitand);
    set_add(syms, assign_bitor);
    set_add(syms, assign_bitxor);
    set_add(syms, comma);
    set_add(syms, semicolon);
    set_add(syms, lparen);
    set_add(syms, rparen);
    set_add(syms, lbracket);
    set_add(syms, rbracket);
    set_add(syms, lbrace);
    set_add(syms, rbrace);
    set_add(syms, if_tok);
    set_add(syms, else_tok);
    set_add(syms, while_tok);
    set_add(syms, id);
    set_add(syms, num);
    set_add(syms, int_tok);
    set_add(syms, float_tok);
    set_add(syms, char_tok);
    set_add(syms, void_tok);
    set_add(syms, return_tok);

    symbol_T *stat_list[] = {statement_list, statement};

    symbol_T *declaration_list[] = {type_specifier, id, assign, constant_expression, semicolon};
    symbol_T *exp_stmt_list[] = {constant_expression, semicolon};

    symbol_T *logic_or_exp_list[] = {logical_or_expression, logical_or, logical_and_expression};
    symbol_T *logic_and_exp_list[] = {logical_and_expression, logical_and, inclusive_or_expression};
    



    set_T *rules = set_init(rule_cmp_generic);
    
    rule_T *start_r = init_rule(start->symbol->non_terminal, &program, 1);
    rule_T *program_sl = init_rule(program->symbol->non_terminal, &statement_list, 1);

    rule_T *sl_s = init_rule(statement_list->symbol->non_terminal, &statement, 1);
    rule_T *sl_sl = init_rule(statement_list->symbol->non_terminal, stat_list, 2);

    rule_T *s_exp_stmt = init_rule(statement->symbol->non_terminal, &expression_statement, 1);
    rule_T *s_compound_stmt = init_rule(statement->symbol->non_terminal, &compound_statement, 1);
    rule_T *s_selection_stmt = init_rule(statement->symbol->non_terminal, &selection_statement, 1);
    rule_T *s_iteration_stmt = init_rule(statement->symbol->non_terminal, &iteration_statement, 1);
    // rule_T *s_jump_stmt = init_rule(statement->symbol->non_terminal, &jump_statement, 1); dont need for now
    rule_T *s_labeled_stmt = init_rule(statement->symbol->non_terminal, &labeled_statement, 1);
    rule_T *s_decl = init_rule(statement->symbol->non_terminal, &declaration, 1);

    rule_T *decl = init_rule(declaration->symbol->non_terminal, declaration_list, 5);

    rule_T *type_int = init_rule(type_specifier->symbol->non_terminal, &int_tok, 1);
    rule_T *type_float = init_rule(type_specifier->symbol->non_terminal, &float_tok, 1);
    rule_T *type_char = init_rule(type_specifier->symbol->non_terminal, &char_tok, 1);
    rule_T *type_void = init_rule(type_specifier->symbol->non_terminal, &void_tok, 1);

    /* 
        function
        param-list
        param
    */ 

    rule_T *exp_stmt = init_rule(expression_statement->symbol->non_terminal, exp_stmt_list, 2);

    



    set_add(rules, start_r);
    set_add(rules, program_sl);
    set_add(rules, sl_s);
    set_add(rules, sl_sl);
    set_add(rules, s_exp_stmt);
    set_add(rules, s_compound_stmt);
    set_add(rules, s_selection_stmt);
    set_add(rules, s_iteration_stmt);
    set_add(rules, s_labeled_stmt);
    set_add(rules, s_decl);
    set_add(rules, decl);
    set_add(rules, type_int);
    set_add(rules, type_float);
    set_add(rules, type_char);
    set_add(rules, type_void);

    grammer_T *gram = init_grammer(rules, syms);

    set_T *itms = lr0_items(gram, init_lr_item(start_r, 0, NULL));
    slr_T *slr = init_slr(itms, gram);

    action_tbl_print_to_file(slr->action, PARSER_ACTION_PATH);
    action_tbl_pretty_print_to_file(slr->action, PARSER_ACTION_PRETTY_PATH);
    goto_tbl_print_to_file(slr->go_to, PARSER_GOTO_PATH);
    goto_tbl_pretty_print_to_file(slr->go_to, PARSER_GOTO_PRETTY_PATH);
}

void init_quest() {
    init_default_lang();

    return;
}