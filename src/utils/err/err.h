#ifndef QUEST_ERR
#define QUEST_ERR

typedef enum ERROR_TYPES_ENUM {
    OPEN_FILE_ERR = 1,
    WRT_FILE_ERR,
    ALLOC_ERR,
    HASHSET_RESIZE_ERR,

    PARSER_ACTION_ERROR
} err_E;

void thrw(int err);

#endif