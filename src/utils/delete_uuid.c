/*
** EPITECH PROJECT, 2024
** delete_uuid.c
** File description:
** is_number
*/

#include "utils.h"


void delete_uuid(char *str, int n)
{
    int len = strlen(str);

    if (n >= len) {
        return;
    } else {
        memmove(str, str + n, len - n + 1);
    }
}
