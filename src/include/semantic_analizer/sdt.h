#include "../../utils/DS/include/generic_set.h"

typedef struct SDT_STRUCT {
    set_T *definitions;
} sdt_T;

sdt_T *init_sdt(set_T *definitions);