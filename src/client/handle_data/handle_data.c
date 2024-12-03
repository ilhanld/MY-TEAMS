/*
** EPITECH PROJECT, 2024
** handle_data.c
** File description:
** handle_data
*/

#include "../client.h"


void handle_data_ext(client_t *client)
{
    if (strncmp(client->buffer, "100", 3) == 0) {
        client_error_unauthorized();
        return;
    }
    if (strncmp(client->buffer, "101", 3) == 0) {
        unknow_usr(client);
        return;
    }
    if (strncmp(client->buffer, "350", 3) == 0) {
        all_info_usr(client);
        return;
    }
    if (strncmp(client->buffer, "300", 3) == 0) {
        info_of_usr(client);
        return;
    }
}

void handle_data(client_t *client)
{
    if (strncmp(client->buffer, "505", 3) == 0) {
        logout_client(client);
        return;
    }
    if (strncmp(client->buffer, "500", 3) == 0) {
        login_client(client);
        return;
    }
    if (strncmp(client->buffer, "410", 3) == 0) {
        recv_msg_client(client);
        return;
    }
    handle_data_ext(client);
    return;
}
