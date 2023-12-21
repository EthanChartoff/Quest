//===--- The Quest Language's Tokens ----------===
//
// In here all of Quest's tokens are defined.
// Macros are used to define the tokens for external 
// use, like defining enums and functions.
//
// WORK IN PROGRESS
//
//===------------------------------------------===

#ifndef TOK
#define TOK(name, str, str_name, val, is_kw)
#endif
#ifndef PUNCTUATOR
#define PUNCTUATOR(name, str, name_str, is_kw)      TOK(name, str, name_str,    , 0)
#endif
#ifndef PUNCTUAVAL
#define PUNCTUAVAL(name, str, name_str, val, is_kw) TOK(name, str, name_str, val, 0)
#endif
#ifndef OPERATOR
#define OPERATOR(name, str, name_str, is_kw)        TOK(name, str, name_str,    , 1)
#endif
#ifndef OPERAVAL
#define OPERAVAL(name, str, name_str, val, is_kw)   TOK(name, str, name_str, val, 1)
#endif
#ifndef KEYWORD
#define KEYWORD(name, name_str, is_kw)              TOK(name, ,  , name_str,    , 1)
#endif
#ifndef ALIAS
#define ALIAS(name, str, name_str, is_kw)           TOK(name)
#endif

//------------------
// Keywords
// -----------------



PUNCTUATOR(star,                "*")
PUNCTUATOR(starequal,           "*=")
PUNCTUATOR(plus,                "+")
PUNCTUATOR(plusplus,            "++")

#undef ALIAS
#undef KEYWORD
#undef PUNCTUATOR
#undef TOK
