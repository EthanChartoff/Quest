#include "../include/code_gen/TTS.h"
#include "../utils/err/err.h"

#include <stdlib.h>

tts_T *init_tts(translation_rule_T **tok_translation, size_t n_tok, translation_rule_T **non_term_translation, size_t n_non_term) {
    tts_T *tts = malloc(sizeof(tts_T));
    if(!tts)
        thrw(ALLOC_ERR);

    tts->tok_translation = tok_translation;
    tts->n_tok = n_tok;
    tts->non_term_translation = non_term_translation;
    tts->n_non_term = n_non_term;
    
    return tts;
}

tts_T *create_tts(translation_rule_T **tok_translation, size_t n_tok, translation_rule_T **non_term_translation, size_t n_non_term) {
    int i;
    tts_T *tts = malloc(sizeof(tts_T));
    if(!tts)
        thrw(ALLOC_ERR);

    tts->n_tok = n_tok;
    tts->n_non_term = n_non_term;

    tts->tok_translation = calloc(n_tok, sizeof(translation_rule_T *));
    if(!tts->tok_translation)
        thrw(ALLOC_ERR);

    tts->non_term_translation = calloc(n_non_term, sizeof(translation_rule_T *));
    if(!tts->non_term_translation)
        thrw(ALLOC_ERR);

    for(i = 0; i < n_tok; ++i)
        tts->tok_translation[tok_translation[i]->symbol->symbol->terminal->type] = tok_translation[i];

    for(i = 0; i < n_non_term; ++i)
        tts->non_term_translation[non_term_translation[i]->symbol->symbol->non_terminal->type] = non_term_translation[i];

    return tts;
}
