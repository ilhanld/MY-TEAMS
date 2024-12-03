/*
** EPITECH PROJECT, 2024
** handle_data.c
** File description:
** handle_data
*/

#include "../client.h"

int info_of_usr(client_t *client)
{
    char **arg_cmd = my_strtok_to_word_array(client->buffer, "\t\n\r;");

    if (get_size_array(arg_cmd) != 4)
        return UNSUCCESS;
    client_print_user(arg_cmd[1], arg_cmd[2], atoi(arg_cmd[3]));
    return SUCCESS;
}
