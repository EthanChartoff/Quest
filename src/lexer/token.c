#include "../include/lexer/token.h"
#include "../include/macros.h"
#include <stdlib.h>
#include <string.h>

token_T* init_token(char* value, int type) {
    token_T* tk = calloc(1, sizeof(token_T));
    tk->value = value;
    tk->type = type;

    return tk;
}

int token_cmp(const token_T *tok1, const token_T *tok2) {
    int delta;

    delta = tok1->type - tok2->type;
    IF_SIGN(delta);

    delta = strcmp(tok1->value, tok2->value);
    IF_SIGN(delta);

    return 0;
}

int token_cmp_generic(const void *tok1, const void *tok2) {
    return token_cmp((token_T *) tok1, (token_T *) tok2);
}