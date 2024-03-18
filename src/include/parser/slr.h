#ifndef QUEST_SLR_H
#define QUEST_SLR_H

#include "../../utils/DS/include/generic_set.h"

typedef struct SLR_STRUCT {
    set_T **lr0_cc;     // cannonical collection of all lr0 items. the reason its an array of items is because its more efficient and easy to work with.
    size_t lr0_cc_size; // size of cc
    char ***action;     // action table 
    char **go_to;       // goto table
} slr_T;

int init_slr_tables(set_T *lr0);

#endif