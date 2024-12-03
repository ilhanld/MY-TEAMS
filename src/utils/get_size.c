/*
** EPITECH PROJECT, 2024
** is_number.c
** File description:
** is_number
*/

#include "utils.h"

int get_size_array(char **array)
{
    int i;

    if (array == NULL)
        return 0;
    for (i = 0; array[i] != NULL; i++);
    return i;
}

void free_tab(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}
