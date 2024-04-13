//===--= TTS.h =------------------------------------------------------===
//
// the header for the tree translation scheme
//
//===-----------------------------------------------------------------===

#ifndef QUEST_TTS_H
#define QUEST_TTS_H

#include "translation_rule.h"
typedef struct TREE_TRANSLATION_SCHEME_STRUCT {
    translation_rule_T **tok_translation;
    size_t n_tok;
    translation_rule_T **non_term_translation;
    size_t n_non_term;
} tts_T;

tts_T *init_tts(translation_rule_T **tok_translation, size_t n_tok, translation_rule_T **non_term_translation, size_t n_non_term);
tts_T *create_tts(translation_rule_T **tok_translation, size_t n_tok, translation_rule_T **non_term_translation, size_t n_non_term);

#endif /* QUEST_TTS_H */