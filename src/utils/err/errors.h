#ifndef ERR
#define ERR(name, msg)
#endif

ERR(UNKNOWN, "Unknown error happened\n")
ERR(OPEN_FILE, "Error while opening file, terminating\n")
ERR(WRT_FILE, "Error while writing file, terminating\n")
ERR(ALLOC, "Error while allocating memory, terminating\n")
ERR(PARSER_ACTION, "Error parsing, specifically in action table\n")

#undef ERR