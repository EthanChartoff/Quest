#ifndef QUEST_ERR
#define QUEST_ERR

#define PROG "qc"

#define ERR_MSG() printf("%s: error: in file: %s line: %d\n", prog, status.fname, status.linec);
#define PERROR_PROG(err) fprintf(stderr, "%s: %s", PROG, err)

typedef enum ERROR_TYPES_ENUM {
    #define ERR(name, msg) name##_ERR,
    #include "errors.h"
    #undef ERR
    N_ERRS
} err_E;

void thrw(int err);

#endif