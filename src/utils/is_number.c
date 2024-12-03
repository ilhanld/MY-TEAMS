/*
** EPITECH PROJECT, 2024
** is_number.c
** File description:
** is_number
*/

#include "utils.h"

int is_number(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
    }
    return 0;
}
