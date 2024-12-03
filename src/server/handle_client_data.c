/*
** EPITECH PROJECT, 2024
** handle_client_data.c
** File description:
** handle_client_data
*/

#include "server.h"

void clear_buffer(server_t *my_server, int index)
{
    if (CLIENT_BUFFER[strlen(CLIENT_BUFFER) - 1] == '\n') {
        CLIENT_BUFFER[strlen((CLIENT_BUFFER)) - 1] = '\0';
    }
}

void read_data(server_t *my_server, int index)
{
    int recv_value;
    char buffer[MAX_BUFFER] = {0};

    recv_value = recv(CLIENT_SOCKET, buffer, MAX_BUFFER - 1, 0);
    if (recv_value <= 0) {
        return;
    }
    process_data(my_server, index, buffer);
}

void process_data(server_t *my_server, int index, char *buffer)
{
    char *line = strtok(buffer, "\n");

    while (line != NULL) {
        if (strlen(line) > 0) {
            strcpy(CLIENT_BUFFER, line);
            clear_buffer(my_server, index);
            puts(CLIENT_BUFFER);
            check_commands(my_server, index, CLIENT_BUFFER);
        }
        line = strtok(NULL, "\n");
    }
    if (CLIENT_BUFFER != NULL) {
        free(CLIENT_BUFFER);
    }
    CLIENT_BUFFER = malloc(sizeof(char) * MAX_BUFFER);
    memset(CLIENT_BUFFER, 0, MAX_BUFFER);
}

void handle_client_data(server_t *my_server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(my_server->client_list[i].socket, &AFD)) {
            read_data(my_server, i);
        }
    }
}
