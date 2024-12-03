/*
** EPITECH PROJECT, 2024
** send.c
** File description:
** send
*/

#include "server.h"

void send_to_client(int client_socket, char *code, char *MSG)
{
    write(client_socket, code, strlen(code));
    write(client_socket, " ", 1);
    write(client_socket, MSG, strlen(MSG));
}
