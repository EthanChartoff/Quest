#ifndef QUEST_LEXER_DFA_STATE_TYPE_H
#define QUEST_LEXER_DFA_STATE_TYPE_H

typedef enum LEXER_DFA_STATE_TYPE_ENUM {
    DENY,                           // deny state, if lexeme ended in this state its not valid
    CHAR_DENY,                      // first state of char states, if ended here theres no sigle quote to end char
    STRING_DENY,                    // first state of string states
    ACCEPT,                         // accept state, means that its a token
    IDENTIFIER,                     // identifier (token)
    NUMBER,                         // number (token)
    CHAR,                           // char (token)
    STRING,                         // string (token)
    LEXER_DFA_STATE_TYPE_SIZE,      // size of valid state types, if a state is defined as this type theres an error
} lexer_dfa_state_type_T;

#endif