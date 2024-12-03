/*
** EPITECH PROJECT, 2024
** logout_client.c
** File description:
** logout_client
*/

#include "../client.h"

int logout_client(client_t *client)
{
    printf("%s", client->buffer);
    client_event_logged_out(client->uuid, client->username);
    close(client->sock);
    free(client->buffer);
    free(client);
    exit(0);
}
