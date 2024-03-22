#include "../include/parser/bnf.h"
#include "../utils/err/err.h"
#include "../include/macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void replace_char(char *str, char to_replace, char replace_with) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_replace) {
            str[i] = replace_with;
        }
    }
}

static void handle_left(char *left, FILE *dest, FILE *xlat_dest) {
    replace_char(left, '-', '_');

    fprintf(dest, "NON_TERM(%s, \"%s\")\n", left, left);

    fprintf(xlat_dest, 
        "symbol_T *%s =  init_symbol_non_terminal(init_non_terminal(\"%s\", NON_TERM_%s));\n", 
        left, 
        left, 
        left);
    fprintf(xlat_dest, "set_add(rules, %s);\n", left);
}

static void handle_right(char *left, char *right) {
    
}

void bnf_make_non_terminals(char *src, char *dest) {
    FILE *fp_src, *fp_dest, *fp_xlat;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 1;
    char* buffer;

    // initialize values
    fp_src = fopen(src, "r");
    if(!fp_src)
        thrw(OPEN_FILE_ERR);

    fp_dest = fopen(dest, "w");
    if(!fp_dest)
        thrw(OPEN_FILE_ERR);

    fp_xlat = fopen(PARSER_BNF_XLAT, "w");
    if(!fp_xlat)
        thrw(OPEN_FILE_ERR);

    buffer = malloc(sizeof(char));
    if(!buffer)
        thrw(ALLOC_ERR);
    buffer[0] = '\0';

    // header
    fprintf(fp_dest, "%s\n", PARSER_NON_TERMINALS_HEADER);
    fprintf(fp_xlat, "set_T *rules = set_init(rule_cmp_generic);");


    while (read != -1 && (read = getline(&line, &len, fp_src) != -1)) {
        if(strlen(line) > 1) {
            handle_left(strtok(line, " ::="), fp_dest, fp_xlat);
            
            // handle right
            // handle_right(buffer, strtok(NULL, "") + 4);
            while ((read = getline(&line, &len, fp_src) != -1) && strlen(line) > 1) {
                // strtok(line, "|");
                // handle_right(buffer, strtok(NULL, "") + 1);
            }
        }
    }

    // footer
    fprintf(fp_dest, "%s", PARSER_NON_TERMINALS_FOOTER);


    fclose(fp_src);
    if(line)
        free(line);
}
