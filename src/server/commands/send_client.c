/*
** EPITECH PROJECT, 2024
** send_cl.c
** File description:
** send_cl
*/

#include "../server.h"

int find_uuid(char *uuid_search, server_t *my_server, int index)
{
    for (int i = 0; i < MAX_CLIENT_TEAMS; i++) {
        if (strcmp(my_server->client_list[i].uuid, uuid_search) == 0) {
            return i;
        }
    }
    send_to_client(CLIENT_SOCKET, "101", "User doesn't exist.");
    write(CLIENT_SOCKET, ";", 1);
    write(CLIENT_SOCKET, uuid_search, strlen(uuid_search));
    write(CLIENT_SOCKET, "\n", 1);
    return 168;
}

void client_send_message(server_t *my_server, int cs, int index, char *MSG)
{
    send_to_client(cs, "410", "you have recieve a message.;");
    write(cs, CLIENT_UUID, strlen(CLIENT_UUID));
    write(cs, ";", 1);
    write(cs, MSG, strlen(MSG));
    write(cs, "\n", 1);
}

bool validate_send_cl(server_t *my_server, int index, int i_ds)
{
    if (my_server->client_list[index].is_log == false) {
        send_to_client(CLIENT_SOCKET, "100",
            "You must be logged in to use this command.\n");
        return false;
    }
    if (i_ds == 168) {
        return false;
    }
    return true;
}

void send_messages(server_t *my_server, int index, int index_d, char *message)
{
    int sock_dst = my_server->client_list[index_d].socket;

    server_event_private_message_sended(my_server->client_list[index].uuid,
    my_server->client_list[index_d].uuid, message);
    send_to_client(CLIENT_SOCKET, "400", "your message has been sent.\n");
    client_send_message(my_server, sock_dst, index, message);
}

int send_cl(server_t *my_server, int index, char **arg_cmd)
{
    int index_dst;
    char *message;

    if (get_size_array(arg_cmd) != 3)
        return invalid_args(my_server, index);
    if (parse_arg_cmd(arg_cmd[1]) == NULL
    || parse_arg_cmd(arg_cmd[2]) == NULL)
        return invalid_args(my_server, index);
    arg_cmd[1] = strdup(parse_arg_cmd(arg_cmd[1]));
    arg_cmd[2] = strdup(parse_arg_cmd(arg_cmd[2]));
    index_dst = find_uuid(arg_cmd[1], my_server, index);
    if (validate_send_cl(my_server, index, index_dst) == false)
        return UNSUCCESS;
    message = strdup(arg_cmd[2]);
    send_messages(my_server, index, index_dst, message);
    free(message);
    return SUCCESS;
}
