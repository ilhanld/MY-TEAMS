/*
** EPITECH PROJECT, 2024
** send_data.c
** File description:
** send_data
*/

#include "client.h"

void send_data(client_t *client)
{
    char buffer[MAX_BUFFER] = {0};

    if (read(0, buffer, 1) > 0)
        strcat(client->in_buffer, buffer);
    if (!check_buffer(client->in_buffer))
        return;
    if (strlen(client->in_buffer) > 0)
        client->in_buffer[strlen(client->in_buffer) - 1] = '\0';
    check_commands(client);
    memset(client->in_buffer, 0, MAX_BUFFER);
}
