//===--- The Quest Language: Lexer -------------------===
//
// The lexer of the compiler.
//
//
// WORK IN PROGRESS
//
//===------------------------------------------------===

#include "include/lexer.h"
#include "include/lexer_automata.h"
#include "include/macros.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

// advance lexer to the next character in its source.
void lexer_advance(lexer_T* lex) {
    if(lex->i < lex->src_size && lex->c != '\0') {
        lex->i++;
        lex->c = lex->src[lex->i];
    }
}

token_T* lexer_advance_with(lexer_T* lex, token_T* tk) {
    lexer_advance(lex);
    return tk;
}

token_T* lexer_advance_current(lexer_T* lex, int type) {
    char* val = calloc(2, sizeof(char));
    val[0] = lex->c;
    val[1] = '\0';

    token_T* token = init_token(val, type);
    lexer_advance(lex);

    return token;
}

char lexer_peek(lexer_T* lex, int offset) {
    return lex->src[MIN(lex->i + offset, lex->src_size)];
}

void lexer_skip_whitespace(lexer_T* lex) {
    while (lex->c == '\r'   // carriage return 
        || lex->c == '\n'   // newline 
        || lex->c == '\t'   // tab
        || lex->c == ' ') 
        lexer_advance(lex); // skip
}

token_T* lexer_parse_id(lexer_T* lex) {
    char* val = calloc(1, sizeof(char));

    while (isalpha(lex->c)) {
        val = realloc(val, (strlen(val) + 2) * sizeof(char));
        strcat(val, (char[]){lex->c, 0});
        lexer_advance(lex);
    }

    return init_token(val, TOK_IDENTIFIER);
}

// for now, can only lex int
token_T* lexer_parse_number(lexer_T* lex) {
    char* val = calloc(1, sizeof(char));

    while (isdigit(lex->c)) {
        val = realloc(val, (strlen(val) + 2) * sizeof(char));
        strcat(val, (char[]){lex->c, 0});
        lexer_advance(lex);
    }

    return init_token(val, TOK_INT);
}

token_T* lexer_next_token(lexer_T* lex) {
    while (lex->c != '\0') {
        lexer_skip_whitespace(lex);

        // check non-one character tokens
        if(isalpha(lex->c))
            return lexer_advance_with(lex, lexer_parse_id(lex));
        else if (isdigit(lex->c))
            return lexer_advance_with(lex, lexer_parse_number(lex));

        // check one character tokens
        switch (lex->c) {
        case '(': return lexer_advance_current(lex, TOK_LPAREN);
        case ')': return lexer_advance_current(lex, TOK_RPAREN);
        case '{': return lexer_advance_current(lex, TOK_LBRACE);
        case '}': return lexer_advance_current(lex, TOK_RBRACE);
        case '[': return lexer_advance_current(lex, TOK_LBRACK);
        case ']': return lexer_advance_current(lex, TOK_LBRACK);
        case ':': return lexer_advance_current(lex, TOK_COLON);
        case ';': return lexer_advance_current(lex, TOK_SEMICOLON);
        default: {
            printf("[LEXER]: Unexpected character: %c\n", lex->c);
            exit(1);
            break;
            }
        }
    }
    
    return init_token(0, TOK_AND);
}


// initilize lexer with a source.
// TODO: dont need dfa src
lexer_T* init_lexer(char *src, const char *dfa_src) {
    lexer_T *lex = malloc(sizeof(lexer_T));

    lex->src = src;
    lex->src_size = strlen(src);
    lex->i = 0;
    lex->c = src[lex->i];    
    lex->automata = init_lexer_automata(LEXER_DFA_PATH, LEXER_DFA_STATES_PATH);

    return lex;
}
