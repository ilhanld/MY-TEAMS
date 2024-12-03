/*
** EPITECH PROJECT, 2024
** check_client_logged.c
** File description:
** check_client_logged
*/

#include "server.h"

int check_client_logged(server_t *my_server, char *username)
{
    if (username == NULL) {
        return 84;
    }
    puts(username);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (my_server->client_list[i].username != NULL
        && strcmp(my_server->client_list[i].username, username) == 0) {
            return UNSUCCESS;
        }
    }
    return SUCCESS;
}
