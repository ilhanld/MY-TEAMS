/*
** EPITECH PROJECT, 2024
** login_client.c
** File description:
** login_client
*/

#include "../client.h"

int login_client(client_t *client)
{
    char **arg_cmd = my_strtok_to_word_array(client->buffer, "\t\n\r;");

    if (get_size_array(arg_cmd) != 3)
        return UNSUCCESS;
    strcpy(client->uuid, arg_cmd[1]);
    strcpy(client->username, arg_cmd[2]);
    puts(arg_cmd[0]);
    client_event_logged_in(client->uuid, client->username);
    return SUCCESS;
}
