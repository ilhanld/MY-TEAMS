/*
** EPITECH PROJECT, 2024
** my_strtok_to_word_array.c
** File description:
** my_strtok_to_word_array
*/

#include "utils.h"

char **my_strtok_to_word_array(char *cmd, char *tok)
{
    size_t size = 1;
    char **tab = malloc(sizeof(char *) * (size + 1));
    char *tmp = strtok(cmd, tok);
    size_t i = 0;

    while (tmp != NULL) {
        tab[i] = strdup(tmp);
        tmp = strtok(NULL, tok);
        i++;
        if (i == size) {
            size++;
            tab = realloc(tab, sizeof(char *) * size + 1);
        }
    }
    tab[i] = NULL;
    return tab;
}
