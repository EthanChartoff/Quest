//===--- The Quest Language: Tokens -------------------===
//
// In here all of Quest's tokens are defined.
// Macros are used to define the tokens for external 
// use, like defining enums and functions.
//
//
// WORK IN PROGRESS
//
// - TODO: not necessary, but maybe organize by type, defenitions, etc...
//===--------------------------------------------------===

#ifndef TOK
#define TOK(name, lexeme, val, is_kw)
#endif
#ifndef BASETOK
#define BASETOK(name)                 TOK(name,       ,     , 0)
#endif
#ifndef DEBUG
#define DEBUG(name)                   TOK(name,       ,     , 0)
#endif
#ifndef KEYWORD
#define KEYWORD(name, lexeme)         TOK(name, lexeme,     , 1)
#endif
#ifndef PUNCTUATOR
#define PUNCTUATOR(name, lexeme)      TOK(name, lexeme,     , 0)
#endif
#ifndef PUNCTUAVAL
#define PUNCTUAVAL(name, lexeme, val) TOK(name, lexeme, =val, 0)
#endif
#ifndef OPERATOR
#define OPERATOR(name, lexeme)        TOK(name, lexeme,     , 1)
#endif
#ifndef OPERAVAL
#define OPERAVAL(name, lexeme, val)   TOK(name, lexeme, =val, 1)
#endif

//------------------
// Debug Tokens (4)
//------------------

DEBUG(null)
DEBUG(UNKNOWN)
DEBUG(eof)
DEBUG(COMMENT)

//------------------
// Base (4)
//------------------

BASETOK(IDENTIFIER)
BASETOK(NUMBER_CONSTANT)
BASETOK(CHAR_CONSTANT)
BASETOK(STRING_LITERAL)

//------------------
// Keywords (24)
//------------------

KEYWORD(BOOL,     "bool")
KEYWORD(BREAK,    "break")
KEYWORD(CASE,     "case")
KEYWORD(CHAR,     "char")
KEYWORD(CONST,    "const")
KEYWORD(CONTINUE, "continue")
KEYWORD(DO,       "do")
KEYWORD(DOUBLE,   "double")
KEYWORD(ELSE,     "else")
KEYWORD(FALSE,    "false")
KEYWORD(FLOAT,    "float")
KEYWORD(FOR,      "for")
KEYWORD(IF,       "if")
KEYWORD(INT,      "int")
KEYWORD(LONG,     "long")
KEYWORD(RET,      "ret")
KEYWORD(SHORT,    "short")
KEYWORD(SIGNED,   "signed")
KEYWORD(SWITCH,   "switch")
KEYWORD(TRUE,     "true")
KEYWORD(TYPEDEF,  "typedef")
KEYWORD(UNSIGNED, "unsigned")
KEYWORD(VOID,     "void")
KEYWORD(WHILE,    "while")

//------------------
// Operators (38)
//------------------

// one character symbols have theire ASCII value used as theire token's value
OPERAVAL(DOT,       ".", '.')
OPERAVAL(COMMA,     ",", ',')
OPERAVAL(TILDE,     "~", '~')
OPERAVAL(NOT,       "!", '!')
OPERAVAL(BITAND,    "&", '&')
OPERAVAL(BITOR,     "|", '|')
OPERAVAL(BITXOR,    "^", '^')
OPERAVAL(BITNOT,    "!", '!')
OPERAVAL(STAR,      "*", '*')
OPERAVAL(SLASH,     "/", '/')
OPERAVAL(PLUS,      "+", '+')
OPERAVAL(MINUS,     "-", '-')
OPERAVAL(PRECENT,   "%", '%')
OPERAVAL(GREATER,   ">", '>')
OPERAVAL(LESSER,    "<", '<')
OPERAVAL(EQUEL,     "=", '=')

OPERATOR(ELLIPSES,        "...")
OPERATOR(ARROW,           "->")
OPERATOR(AND,             "&&")
OPERATOR(OR,              "||")
OPERATOR(XOR,             "^^")
OPERATOR(SHIFTLEFT,       "<<")
OPERATOR(SHIFTRIGHT,      ">>")
OPERATOR(EQUELEQUEL,      "==")
OPERATOR(GREATEREQUEL,    ">=")
OPERATOR(LESSEREQUEL,     "<=")
OPERATOR(PLUSEQUEL,       "+=")
OPERATOR(MINUSEQUEL,      "-=")
OPERATOR(STAREQUEL,       "*=")
OPERATOR(SLASHEQUEL,      "/=")
OPERATOR(PRECENTEQUEL,    "%=")
OPERATOR(ANDEQUEL,        "&=")
OPERATOR(OREQUEL,         "|=")
OPERATOR(XOREQUEL,        "^=")
OPERATOR(NOTEQUEL,        "!=")
OPERATOR(TILDEEQUEL,      "~=")
OPERATOR(SHIFTLEFTEQUEL,  "<<=")
OPERATOR(SHIFTRIGHTEQUEL, ">>=")

//------------------
// Punctuators (10)
//------------------

// one character symbols have theire ASCII value used as theire token's value
PUNCTUAVAL(LPAREN,    "(", '(')
PUNCTUAVAL(RPAREN,    ")", ')')
PUNCTUAVAL(LBRACK,    "[", '[')
PUNCTUAVAL(RBRACK,    "]", ']')
PUNCTUAVAL(LBRACE,    "{", '{') 
PUNCTUAVAL(RBRACE,    "}", '}')
PUNCTUAVAL(LCHEVRON,  "<", '<')
PUNCTUAVAL(RCHEVRON,  ">", '>')
PUNCTUAVAL(COLON,     ":", ':')
PUNCTUAVAL(SEMICOLON, ";", ';')


#undef ALIAS
#undef OPERAVAL
#undef OPERATOR
#undef PUNCTUAVAL
#undef PUNCTUATOR
#undef KEYWORD
#undef TOK
