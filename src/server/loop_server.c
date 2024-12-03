/*
** EPITECH PROJECT, 2024
** loop_sever.c
** File description:
** loop_server
*/

#include "server.h"

int starting_server(server_t *my_server)
{
    init_server_struct(my_server);
    my_server->client_list = malloc(sizeof(client_t) * MAX_CLIENTS);
    init_client_list(my_server);
    if (create_bdd() == 1)
        load_save();
    sig_handler();
    my_server->limit = SERVER_SOCKET;
    while (1) {
        AFD = RFD;
        set_client_socket(my_server);
        my_server->select_value = select(my_server->limit + 1,
            &AFD, NULL, NULL, NULL);
        select_error(my_server->select_value);
        handle_new_connection(my_server);
        handle_client_data(my_server);
    }
    return 0;
}
