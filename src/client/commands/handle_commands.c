/*
** EPITECH PROJECT, 2024
** handle_command.c
** File description:
** handle_commands
*/

#include "../client.h"


int check_commands(client_t *client)
{
    if (strcmp(client->in_buffer, "/help\0") == 0)
        return help();
    send(client->sock, client->in_buffer, strlen(client->in_buffer), 0);
    send(client->sock, "\n", 1, 0);
    return SUCCESS;
}
