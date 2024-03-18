#ifndef QUEST_SLR_H
#define QUEST_SLR_H

#include "../../utils/DS/include/generic_set.h"
#include "action_table.h"
#include "goto_table.h"
#include "grammer.h"

typedef struct SLR_STRUCT {
    set_T **lr0_cc;         // cannonical collection of all lr0 items. the reason its an array of items is because its more efficient and easy to work with.
    size_t lr0_cc_size;     // size of cc
    action_tbl_T *action;   // action table 
    goto_tbl_T **go_to;     // goto table
    grammer_T *grammer;     // grammer of the
} slr_T;

int init_slr_tables(set_T *lr0, grammer_T *gram);

#endif