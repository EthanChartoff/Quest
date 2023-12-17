#include "include/parser.h"
#include "include/token_type.h"
#include "include/AST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------//
//                                                                  //   
//       The quest compiler parser                                  //
//                                                                  //
//                                                                  //
// - TODO: try to make parsing logic better and more readable       //
// - TODO: and finish                                               //
//------------------------------------------------------------------//


static token_T* eat(parser_T* par, int type) {
    if(par->token->type != type) {
        printf("[PARSER]: Unexpected token: %s, expected token: %s\n", 
            token_type_to_str(par->token->type), token_type_to_str(type));
        exit(1);
    } 
    par->token = lexer_next_token(par->lexer);
    return par->token;
}

static AST_T* parse_id(parser_T* par) {
    char* val = calloc(strlen(par->token->value) + 1, sizeof(char));
    strcpy(val, par->token->value);
    printf("%s\n", par->token->value);
    
    eat(par, TOK_IDENTIFIER);

    AST_T* ast = init_ast(AST_VARIABLE);
    ast->name = val;
    return ast;
}

static AST_T* parse_token(parser_T* par) {
    switch (par->token->type) {
        case TOK_IDENTIFIER: 
            return parse_id(par);
        default: {
            printf("[PARSER]: Unexpected token: %s\n", token_to_str(par->token));
            exit(1);
        }
    }
}

static AST_T* parse_compound(parser_T* par) {
    AST_T* compound = init_ast(AST_COMPOUND);

    while (par->token->type != TOK_EOF)   
        list_add(compound->children, parse_token(par));

    return compound;
}

parser_T* init_parser(lexer_T *lex) {
    parser_T *par = calloc(1, sizeof(parser_T));
    par->lexer = lex;
    par->token = lexer_next_token(par->lexer);

    return par;
}

AST_T* parser_parse(parser_T* par) {
    return parse_compound(par);
}


