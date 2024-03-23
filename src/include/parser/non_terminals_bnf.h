#ifndef NON_TERM 
#define NON_TERM(name, symbol) 
#endif 

NON_TERM(null, "") 
NON_TERM(start, "S'") 

NON_TERM(program, "program")
NON_TERM(statement_list, "statement_list")
NON_TERM(statement, "statement")
NON_TERM(assignment, "assignment")
NON_TERM(conditional, "conditional")
NON_TERM(while_loop, "while_loop")
NON_TERM(statement_block, "statement_block")
NON_TERM(expression, "expression")
NON_TERM(math_expression, "math_expression")
NON_TERM(operator, "operator")
NON_TERM(constant, "constant")

#undef NON_TERM