/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server
*/

#include "server.h"

void init_client_list(server_t *my_server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        my_server->client_list[i].username = NULL;
        my_server->client_list[i].password = NULL;
        my_server->client_list[i].is_log = false;
        my_server->client_list[i].socket = 0;
        my_server->client_list[i].data_socket = 0;
        my_server->client_list[i].data_port = 0;
        my_server->client_list[i].data_ip = NULL;
        my_server->client_list[i].mode = NONE;
        my_server->client_list[i].fileName = malloc(sizeof(char) * 100);
        memset(my_server->client_list[i].fileName, '\0', 100);
    }
}

void init_server_struct(server_t *my_server)
{
    int ret = 0;

    SERVER_SOCKET = socket(AF_INET, SOCK_STREAM, 0);
    socket_error(SERVER_SOCKET);
    my_server->control_addr.sin_family = AF_INET;
    my_server->control_addr.sin_addr.s_addr = INADDR_ANY;
    my_server->control_addr.sin_port = htons(my_server->port);
    htons_error(my_server);
    ret = bind(SERVER_SOCKET, (SOCKADDR_t *)
    &my_server->control_addr, sizeof(my_server->control_addr));
    bind_error(ret);
    ret = listen(SERVER_SOCKET, MAX_CLIENTS);
    listen_error(ret);
    my_server->select_value = 0;
    FD_ZERO(&RFD);
    FD_ZERO(&AFD);
    FD_SET(SERVER_SOCKET, &RFD);
}

void set_client_socket2(server_t *my_server, int index)
{
    if (CLIENT_SOCKET > my_server->limit) {
        my_server->limit = CLIENT_SOCKET;
    }
}

void set_client_socket(server_t *my_server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (my_server->client_list[i].socket > 0) {
            FD_SET(my_server->client_list[i].socket, &AFD);
            set_client_socket2(my_server, i);
        }
    }
}
