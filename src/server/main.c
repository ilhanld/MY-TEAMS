/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main server
*/

#include "server.h"

int main(int ac, char **av)
{
    if (ac != 2) {
        printf("Usage: %s <port>\n", av[0]);
        return 84;
    }
    if (strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\t port is the port \
        number on which the server socket listens\n");
        return 0;
    }
    teams_server(av[1]);
    return 0;
}

int parsing(server_t *my_server)
{
    if (my_server->port < 1024 || my_server->port > 65535) {
        fprintf(stderr, "Error: Use a valid port (1024 - 65535).\n");
        return ERROR;
    }
    return SUCCESS;
}

int teams_server(char *port_str)
{
    server_t *my_server = malloc(sizeof(server_t));

    my_server->port = atoi(port_str);
    if (parsing(my_server) == ERROR) {
        return ERROR;
    }
    return starting_server(my_server);
}
