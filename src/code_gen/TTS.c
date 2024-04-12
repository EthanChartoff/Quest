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