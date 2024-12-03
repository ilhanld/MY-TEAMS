/*
** EPITECH PROJECT, 2024
** handle_new_client.c
** File description:
** handle_new_client
*/

#include "server.h"

void create_new_client(server_t *my_server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (my_server->client_list[i].socket == 0) {
            my_server->client_list[i].socket = my_server->used_socket;
            my_server->client_list[i].buffer = malloc(sizeof(char)
                * MAX_BUFFER);
            memset(my_server->client_list[i].buffer, 0, MAX_BUFFER);
            printf("new client : %d\n", my_server->client_list[i].socket);
            break;
        }
    }
}

void handle_new_connection(server_t *my_server)
{
    socklen_t client_addr_len = sizeof(my_server->client_addr);

    if (FD_ISSET(SERVER_SOCKET, &AFD)) {
        my_server->used_socket = accept(SERVER_SOCKET, C_ADDR, C_ADDRL);
        if (my_server->used_socket < 0) {
            perror("accept failed");
            exit(84);
        }
        create_new_client(my_server);
    }
}
