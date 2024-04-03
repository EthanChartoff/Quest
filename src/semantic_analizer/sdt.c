#include "../include/semantic_analizer/sdt.h"
#include "../include/semantic_analizer/definitions.h"
#include "../utils/err/err.h"
#include <stdio.h>
#include <stdlib.h>


static sdt_T *match_parser_sdt_rules(rule_T **rules, size_t n_rules, semantic_rule_T **srs, size_t n_sr) {
    int i, j, flag;
    semantic_rule_T **definitions = calloc(n_rules, sizeof(semantic_rule_T *));
    if(!definitions)
        thrw(ALLOC_ERR);

    for(i = 0; i < n_rules; ++i) {
        definitions[i] = calloc(1, sizeof(semantic_rule_T));
        definitions[i]->rule = rules[i];
        flag = 0;

        for(j = 0; j < n_sr; ++j) {
            if(!flag && !rule_cmp(srs[j]->rule, definitions[i]->rule)) {
                definitions[i]->definition = srs[j]->definition;
                flag = 1;
            }
        }
    }

    return init_sdt(definitions, n_rules);
}

sdt_T *init_sdt(semantic_rule_T **definitions, size_t n_defenitions) {
    sdt_T *sdt = malloc(sizeof(sdt_T));

    sdt->definitions = definitions;
    sdt->n_defenitions = n_defenitions;

    return sdt;
}

sdt_T *init_default_sdt(rule_T **rules, size_t n_rules) {
    semantic_rule_T **srs = malloc(sizeof(semantic_rule_T *) * 3);

    // srs[0] = init_sementic_rule(rules[5], definition_math_expression_operation);
    srs[0] = init_sementic_rule(rules[10], definition_assignment);
    // srs[2] = init_sementic_rule(rules[9], definition_conditional);
    srs[1] = init_sementic_rule(rules[15], definition_statement_list_statement);
    srs[2] = init_sementic_rule(rules[14], definition_statement_list_statement_list);

    // srs[4] = init_sementic_rule(rules[7], definition_semantic_block);


    return match_parser_sdt_rules(rules, n_rules, srs, 3);
}
