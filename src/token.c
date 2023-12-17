#include <stdlib.h>
#include "include/token.h"

token_T* init_token(char* value, int type) {
    token_T* tk = calloc(1, sizeof(token_T));
    tk->value = value;
    tk->type = type;

    return tk;
}