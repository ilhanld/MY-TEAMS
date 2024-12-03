/*
** EPITECH PROJECT, 2024
** error.c
** File description:
** error
*/

#include "server.h"


regex_t compile_regex(char *pattern)
{
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);

    if (reti) {
        exit(1);
    }
    return regex;
}

int execute_regex(regex_t *regex, char *str, regmatch_t *matches)
{
    int reti = regexec(regex, str, 2, matches, 0);

    if (reti == REG_NOMATCH) {
        return -1;
    } else if (reti) {
        return UNSUCCESS;
    }
    return 0;
}

char *extract_match(char *str, regmatch_t *matches)
{
    size_t size = matches[1].rm_eo - matches[1].rm_so;
    char *result = malloc(size + 1);

    if (result == NULL) {
        return NULL;
    }
    strncpy(result, str + matches[1].rm_so, size);
    result[size] = '\0';
    return result;
}

char *parse_arg_cmd(char *arg_cmd)
{
    regex_t regex = compile_regex("\"([^\"]*)\"");
    regmatch_t matches[2];
    char *result;

    if (arg_cmd == NULL) {
        return NULL;
    }
    if (execute_regex(&regex, arg_cmd, matches) == 0) {
        result = extract_match(arg_cmd, matches);
        regfree(&regex);
        return result;
    }
    regfree(&regex);
    return NULL;
}
