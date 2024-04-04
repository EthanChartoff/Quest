#include "../include/parser/bnf.h"
#include "../utils/err/err.h"
#include "../utils/DS/include/generic_set.h"
#include "../include/macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int strcmp_generic(const void *str1, const void *str2) {
    int delta = strcmp(str1, str2);

    return delta ? delta / abs(delta) : delta;
}

static void replace_char(char *str, char to_replace, char replace_with) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_replace) {
            str[i] = replace_with;
        }
    }
}

static void handle_left(char *left, set_T *left_set, FILE *dest) {
    replace_char(left, '-', '_');

    // print dest
    fprintf(dest, "NON_TERM(%s, \"%s\")\n", left, left);

    set_add(left_set, left);
}

static void handle_right(char *left, char *right, FILE *xlat) {
    char *cur_sym = strtok(right, " ");
    char **whole_right;

    while(cur_sym) {
        cur_sym = strtok(NULL, " ");
    }
}

static void print_syms(set_T *s, FILE *xlat) {
    char *cur_left;
    int i;
    set_node_T *cn = s->head;

    fprintf(xlat, "symbol_T *start = init_symbol_non_terminal(init_non_terminal(\"S'\", NON_TERM_start));\n");
    
    for(i = 0; i < s->size; ++i) {
        cur_left = cn->data;

        fprintf(xlat, 
            "symbol_T *%s = init_symbol_non_terminal(init_non_terminal(\"%s\", NON_TERM_%s));\n",
            cur_left,
            cur_left,
            cur_left);

        cn = cn->next;
    }

    fprintf(xlat, "\n");
    fprintf(xlat, "set_add(syms, start);\n");

    cn = s->head;
    for(i = 0; i < s->size; ++i) {
        cur_left = cn->data;

        fprintf(xlat, 
            "set_add(syms, %s);\n",
            cur_left);

        cn = cn->next;
    }
}

void bnf_make_non_terminals(char *src, char *dest) {
    FILE *fp_src, *fp_dest, *fp_xlat;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 1;
    char* buffer;
    set_T *left_set = set_init(strcmp_generic);

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
    fprintf(fp_xlat, "set_T *syms = set_init(symbol_cmp_generic);\n");



    while (read != -1 && (read = getline(&line, &len, fp_src) != -1)) {
        if(strlen(line) > 1) {
            buffer = strdup(strtok(line, " ::="));
            handle_left(buffer, left_set, fp_dest);
            
            // handle right
            // handle_right(buffer, strtok(NULL, "") + 4, fp_xlat);
            while ((read = getline(&line, &len, fp_src) != -1) && strlen(line) > 1) {
                // strtok(line, "|");
                // handle_right(buffer, strtok(NULL, "") + 1, fp_xlat);
            }
        }
    }

    print_syms(left_set, fp_xlat);

    // footer
    fprintf(fp_dest, "%s", PARSER_NON_TERMINALS_FOOTER);


    fclose(fp_src);
    fclose(fp_dest);
    fclose(fp_xlat);
    if(line)
        free(line);
}
