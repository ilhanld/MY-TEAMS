/*
** EPITECH PROJECT, 2024
** invalid_args.c
** File description:
** invalid_args
*/

#include "server.h"

int invalid_args(server_t *my_server, int index)
{
    send_to_client(CLIENT_SOCKET, "600",
        "Invalid argument. See /help.\n");
    return UNSUCCESS;
}
