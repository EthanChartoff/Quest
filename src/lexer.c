//===--- The Quest Language: Lexer -------------------===
//
// The lexer of the compiler.
//
//
// WORK IN PROGRESS
//
//===------------------------------------------------===

#include "include/lexer.h"
#include "include/macros.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


static short** init_dfa(const char *dfa_src) {
    short **dfa;
    FILE *dfa_file = fopen(dfa_src, "r");
    int rows = 0, cols = 0, i, j, k;

    // handle file not opening
    if(dfa_file == NULL) {
        perror("Error opening dfa file");
        exit(EXIT_FAILURE);
    }

    while(fscanf(dfa_file, "%d, ", &cols) == 1)
        rows++;
    fseek(dfa_file, 0, SEEK_SET);

    dfa = (short**)malloc(rows * sizeof(short*));
    for(i = 0; i < rows; ++i) 
        dfa[i] = (short*)malloc(cols * sizeof(short));

    for(i = 0; i < rows; ++i) {
        for(j = 0; j < cols; ++j) {
            if(fscanf(dfa_file, "%hd", &dfa[i][j]) != 1) {
                perror("Error reading from file");
                fclose(dfa_file);

                for(k = 0; k < rows; ++k)
                    free(dfa[k]);
                free(dfa);

                exit(1);
            }
        }
    }

    fclose(dfa_file);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", dfa[i][j]);
        }
        // printf("\n");
    }
    return dfa;
}

// initilize lexer with a source.
lexer_T* init_lexer(char *src, const char *dfa_src) {
    lexer_T *lex = calloc(1, sizeof(lexer_T));

    lex->src = src;
    lex->src_size = strlen(src);
    lex->i = 0;
    lex->c = src[lex->i];    
    lex->dfa =  init_dfa(dfa_src);

    return lex;
}

// // advance lexer to the next character in its source.
// void lexer_advance(lexer_T* lex) {
//     if(lex->i < lex->src_size && lex->c != '\0') {
//         lex->i++;
//         lex->c = lex->src[lex->i];
//     }
// }

// token_T* lexer_advance_with(lexer_T* lex, token_T* tk) {
//     lexer_advance(lex);
//     return tk;
// }

// token_T* lexer_advance_current(lexer_T* lex, int type) {
//     char* val = calloc(2, sizeof(char));
//     val[0] = lex->c;
//     val[1] = '\0';

//     token_T* token = init_token(val, type);
//     lexer_advance(lex);

//     return token;
// }

// char lexer_peek(lexer_T* lex, int offset) {
//     return lex->src[MIN(lex->i + offset, lex->src_size)];
// }

// void lexer_skip_whitespace(lexer_T* lex) {
//     while (lex->c == '\r'   // carriage return 
//         || lex->c == '\n'   // newline 
//         || lex->c == '\t'   // tab
//         || lex->c == ' ') 
//         lexer_advance(lex); // skip
// }

// token_T* lexer_parse_id(lexer_T* lex) {
//     char* val = calloc(1, sizeof(char));

//     while (isalpha(lex->c)) {
//         val = realloc(val, (strlen(val) + 2) * sizeof(char));
//         strcat(val, (char[]){lex->c, 0});
//         lexer_advance(lex);
//     }

//     return init_token(val, TK_ID);
// }

// // for now, can only lex int
// token_T* lexer_parse_number(lexer_T* lex) {
//     char* val = calloc(1, sizeof(char));

//     while (isdigit(lex->c)) {
//         val = realloc(val, (strlen(val) + 2) * sizeof(char));
//         strcat(val, (char[]){lex->c, 0});
//         lexer_advance(lex);
//     }

//     return init_token(val, TK_INT);
// }

// token_T* lexer_next_token(lexer_T* lex) {
//     while (lex->c != '\0') {
//         lexer_skip_whitespace(lex);

//         // check non-one character tokens
//         if(isalpha(lex->c))
//             return lexer_advance_with(lex, lexer_parse_id(lex));
//         else if (isdigit(lex->c))
//             return lexer_advance_with(lex, lexer_parse_number(lex));

//         // check one character tokens
//         switch (lex->c) {
//         case '(': return lexer_advance_current(lex, TK_LPAREN);
//         case ')': return lexer_advance_current(lex, TK_RPAREN);
//         case '{': return lexer_advance_current(lex, TK_LBRACE);
//         case '}': return lexer_advance_current(lex, TK_RBRACE);
//         case '[': return lexer_advance_current(lex, TK_LSBRACKET);
//         case ']': return lexer_advance_current(lex, TK_RSBRACKET);
//         case ':': return lexer_advance_current(lex, TK_COLON);
//         case ';': return lexer_advance_current(lex, TK_SEMICOLON);
//         default: {
//             printf("[LEXER]: Unexpected character: %c\n", lex->c);
//             exit(1);
//             break;
//             }
//         }
//     }
    
//     return init_token(0, TK_EOF);
// }