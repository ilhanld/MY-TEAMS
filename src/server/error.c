/*
** EPITECH PROJECT, 2024
** error.c
** File description:
** error
*/

#include "server.h"

void socket_error(int server_socket)
{
    if (server_socket < 0) {
        perror("socket()");
        exit(84);
    }
}

void htons_error(server_t *my_server)
{
    if (htons(my_server->port) == 0) {
        perror("htons()");
        exit(84);
    }
}

void bind_error(int bind)
{
    if (bind < 0) {
        perror("bind()");
        exit(84);
    }
}

void listen_error(int listen)
{
    if (listen < 0) {
        perror("listen()");
        exit(84);
    }
}

void select_error(int select_value)
{
    if ((select_value < 0) && (errno != EINTR)) {
        perror("select()");
        exit(84);
    }
}
