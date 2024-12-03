/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main client
*/
#include "client.h"

int main(int ac, char **av)
{
    char *ip = av[1];
    int port = atoi(av[2]);
    client_t *client;

    if (ac != 3) {
        printf("Usage: %s <ip> <port>\n", av[0]);
        return 84;
    }
    if (strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n\tip is the server ip address \
        on which the server socket listens\n\tport is the port number on \
        which the server socket listens\n");
        return 0;
    }
    client = malloc(sizeof(client_t));
    init_struct(client, ip, port);
    start_client(client);
    return 0;
}

void init_struct(client_t *client, char *ip, int socket)
{
    client->sock = socket;
    client->port = socket;
    client->ip = ip;
    client->buffer = malloc(sizeof(char) * MAX_BUFFER * 2);
    client->username = malloc(sizeof(char) * MAX_NAME_LENGTH);
    client->uuid = malloc(sizeof(char) * 40);
    memset(client->username, '\0', MAX_NAME_LENGTH);
    memset(client->uuid, '\0', 40);
    memset(client->buffer, 0, MAX_BUFFER * 2);
    memset(client->in_buffer, 0, MAX_BUFFER);
}
