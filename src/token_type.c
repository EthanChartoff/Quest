#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "include/token_type.h"

// initialize a token with a value and a type and allocate memory to it.
token_T* init_token(char* value, int type) {
    token_T* tk = calloc(1, sizeof(token_T));
    tk->value = value;
    tk->type = type;

    return tk;
}

// convert token type to str. 
// gets an int but supposed to get type of token, if not the result will be an error.
// note: maybe have another function for the tokens with an alt value 
char* token_type_to_str(const int type) {
    switch (type) {
        case TOK_LBRACK:
            return "TOK_LBRACK";
        case TOK_RBRACK:
            return "TOK_RBRACK";
        case TOK_LPAREN:
            return "TOK_LPAREN";
        case TOK_RPAREN:
            return "TOK_RPAREN";
        case TOK_LCURLY:
            return "TOK_LCURLY";
        case TOK_RCURLY:
            return "TOK_RCURLY";
        case TOK_DOT:
            return "TOK_DOT";
        case TOK_BITAND:
            return "TOK_BITAND";
        case TOK_ASTERISK:
            return "TOK_ASTERISK";
        case TOK_PLUS:
            return "TOK_PLUS";
        case TOK_MINUS:
            return "TOK_MINUS";
        case TOK_TILDE: // also TOK_COMPLIMENT
            return "TOK_TILDE";
        case TOK_EXCLAMATIONMARK: // also TOK_NOT
            return "TOK_EXCLAMATIONMARK";
        case TOK_SLASH:
            return "TOK_SLASH";
        case TOK_PERCENT:
            return "TOK_PERCENT";
        case TOK_LESS:
            return "TOK_LESS";
        case TOK_GREATER:
            return "TOK_GREATER";
        case TOK_CARET: // also TOK_BITXOR
            return "TOK_CARET";
        case TOK_PIPE: // also TOK_BITOR 
            return "TOK_PIPE";
        case TOK_QUESTIONMARK:
            return "TOK_QUESTIONMARK";
        case TOK_COLON:
            return "TOK_COLON";
        case TOK_SEMICOLON:
            return "TOK_SEMICOLON";
        case TOK_EQUAL:
            return "TOK_EQUAL";
        case TOK_COMMA:
            return "TOK_COMMA";
        case TOK_HASH:
            return "TOK_HASH";
        case TOK_NEWLINE:
            return "TOK_NEWLINE";
        case TOK_PLUSPLUS:
            return "TOK_PLUSPLUS";
        case TOK_MINUSMINUS:
            return "TOK_MINUSMINUS";
        case TOK_LESSLESS:
            return "TOK_LESSLESS";
        case TOK_GREATERGREATER:
            return "TOK_GREATERGREATER";
        case TOK_LESSEQUAL:
            return "TOK_LESSEQUAL";
        case TOK_GREATEREQUAL:
            return "TOK_GREATEREQUAL";
        case TOK_EQUALEQUAL:
            return "TOK_EQUALEQUAL";
        case TOK_EXCLAMATIONMARKEQUAL: // also TOK_NOTEQUAL
            return "TOK_NOTEQUAL";
        case TOK_ANDAND:
            return "TOK_ANDAND"; // also TOK_AND (maybe this is confusing)
        case TOK_PIPEPIPE:
            return "TOK_PIPEPIPE"; // also TOK_OR
        case TOK_DOTDOTDOT:
            return "TOK_DOTDOTDOT";
        case TOK_ASTERISKEQUAL:
            return "TOK_ASTERISKEQUAL";
        case TOK_SLASHEQUAL:
            return "TOK_SLASHEQUAL";
        case TOK_PERCENTEQUAL:
            return "TOK_PERCENTEQUAL";
        case TOK_PLUSEQUAL:
            return "TOK_PLUSEQUAL";
        case TOK_MINUSEQUAL:
            return "TOK_MINUSEQUAL";
        case TOK_LESSLESSEQUAL:
            return "TOK_LESSLESSEQUAL";
        case TOK_GREATERGREATEREQUAL:
            return "TOK_GREATERGREATEREQUAL";
        case TOK_ANDEQUAL:
            return "TOK_ANDEQUAL";
        case TOK_CARETEQUAL:
            return "TOK_CARETEQUAL"; // also TOK_XOREQUAL 
        case TOK_PIPEEQUAL: // also TOK_OREQUAL 
            return "TOK_OREQUAL";
        case TOK_EOF:
            return "TOK_EOF";
        case TOK_IDENTIFIER:
            return "TOK_IDENTIFIER";
        case TOK_NUMBER:
            return "TOK_NUMBER";
        case TOK_CHARACTER_CONSTANT:
            return "TOK_CHARACTER_CONSTANT";
        case TOK_STRING_LITERAL:
            return "TOK_STRING_LITERAL";
        case TOK_MACRO_PARAMETER:
            return "TOK_MACRO_PARAMETER";
        case TOK_UNKNOWN_CHAR:
            return "TOK_UNKNOWN_CHAR";
        case TOK_BREAK:
            return "TOK_BREAK";
        case TOK_CASE:
            return "TOK_CASE";
        case TOK_CHAR:
            return "TOK_CHAR";
        case TOK_CONST:
            return "TOK_CONST";
        case TOK_CONTINUE:
            return "TOK_CONTINUE";
        case TOK_DEFAULT:
            return "TOK_DEFAULT";
        case TOK_DO:
            return "TOK_DO";
        case TOK_DOUBLE:
            return "TOK_DOUBLE";
        case TOK_ELSE:
            return "TOK_ELSE";
        case TOK_ENUM:
            return "TOK_ENUM";
        case TOK_FLOAT:
            return "TOK_FLOAT";
        case TOK_FOR:
            return "TOK_FOR";
        case TOK_IF:
            return "TOK_IF";
        case TOK_INT:
            return "TOK_INT";
        case TOK_LONG:
            return "TOK_LONG";
        case TOK_RET:
            return "TOK_RET";
        case TOK_SHORT:
            return "TOK_SHORT";
        case TOK_SIGNED:
            return "TOK_SIGNED";
        case TOK_SIZEOF:
            return "TOK_SIZEOF";
        case TOK_STATIC:
            return "TOK_STATIC";
        case TOK_STRUCT:
            return "TOK_STRUCT";
        case TOK_SWITCH:
            return "TOK_SWITCH";
        case TOK_TYPEDEF:
            return "TOK_TYPEDEF";
        case TOK_UNION:
            return "TOK_UNION";
        case TOK_UNSIGNED:
            return "TOK_UNSIGNED";
        case TOK_VOID:
            return "TOK_VOID";
        case TOK_WHILE:
            return "TOK_WHILE";
        case TOK_NULL:
            return "TOK_NULL";
        case TOK_LAST_TOKEN:
            return "TOK_LAST_TOKEN";
    }
    return "token type not found";
}

// convert a token to a string.
char* token_to_str(token_T *tk) {
    const char *template = "<value=%s, type=%s, type_value=%d>";
    const char *type_str = token_type_to_str(tk->type);
    int type_value_length = log10(tk->type ? tk->type : 1) + 1;

    char *str = calloc(strlen(template) + strlen(type_str) + type_value_length + 1, sizeof(char));
    sprintf(str, "<value=%s, type=%s, type_value=%d>", tk->value, type_str, tk->type);
    return str;
}

char* token_to_str_details(const token_T *tk) {
    
}