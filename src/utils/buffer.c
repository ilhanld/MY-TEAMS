/*
** EPITECH PROJECT, 2024
** buffer.c
** File description:
** buffer
*/

#include "utils.h"

int check_buffer(char *buffer)
{
    int len = strlen(buffer);

    if (len < 2)
        return 0;
    if (buffer[len - 1] == '\0')
        return 0;
    if (buffer[len - 1] != '\n')
        return 0;
    return 1;
}
