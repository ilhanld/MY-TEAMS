/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main client
*/

#include "client.h"

void setup_client(client_t *client)
{
    struct sockaddr_in serv_addr;

    client->sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(client->port);
    if (client->sock < 0) {
        printf("\n Socket creation error \n");
        exit(84);
    }
    if (inet_pton(AF_INET, client->ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(84);
    }
    if (connect(client->sock, (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        exit(84);
    }
    fcntl(client->sock, F_SETFL, O_NONBLOCK);
}

void start_client(client_t *client)
{
    setup_client(client);
    while (1) {
        loop(client);
    }
}

void prepare_fds(client_t *client, int *value)
{
    FD_ZERO(&client->readfds);
    FD_SET(client->sock, &client->readfds);
    FD_SET(STDIN_FILENO, &client->readfds);
    *value = select(client->sock + 1, &client->readfds, NULL, NULL, NULL);
}

void handle_io(client_t *client, int value)
{
    char buffer[MAX_BUFFER];

    memset(buffer, 0, MAX_BUFFER);
    if (FD_ISSET(STDIN_FILENO, &client->readfds)) {
        send_data(client);
        return;
    }
    value = recv(client->sock, buffer, 1, 0);
    strcat(client->buffer, buffer);
    if (!check_buffer(client->buffer)) {
        return;
    }
    if (value > 0) {
        handle_data(client);
        memset(client->buffer, 0, MAX_BUFFER * 2);
    }
}

void loop(client_t *client)
{
    int value;

    prepare_fds(client, &value);
    if (value <= 0)
        return;
    handle_io(client, value);
}
