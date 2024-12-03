/*
** EPITECH PROJECT, 2024
** unknow_usr.c
** File description:
** unknow_usr
*/

#include "../client.h"

int unknow_usr(client_t *client)
{
    char **arg_cmd = my_strtok_to_word_array(client->buffer, "\t\n\r;");

    if (get_size_array(arg_cmd) != 2)
        return UNSUCCESS;
    client_error_unknown_user(arg_cmd[1]);
    return SUCCESS;
}
