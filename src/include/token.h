#ifndef QUEST_TOKEN_H
#define QUEST_TOKEN_H

typedef enum {
    TK_ID,          // Identifier
    TK_NUM,         // Number literal
    TK_INT,         // type "int"
    TK_VOID,        // type "void"
    TK_CHAR,        // type "char"
    TK_LPAREN,      // (
    TK_RPAREN,      // )
    TK_LBRACE,      // {
    TK_RBRACE,      // }
    TK_LSBRACKET,   // [
    TK_RSBRACKET,   // ]
    TK_COLON,       // :
    TK_SEMICOLON,   // ;
    TK_COMMA,       // ,
    TK_RET,         // "ret" 
    TK_EOF          // End of file
} token_type;

typedef struct TOKEN_STRUCT
{
    char* value;
    token_type type;
} token_T;

token_T* init_token(char* value, int type);

#endif