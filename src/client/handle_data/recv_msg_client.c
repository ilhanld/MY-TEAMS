/*
** EPITECH PROJECT, 2024
** handle_data.c
** File description:
** handle_data
*/

#include "../client.h"

int recv_msg_client(client_t *client)
{
    char **arg_cmd = my_strtok_to_word_array(client->buffer, "\t\n\r;");

    if (get_size_array(arg_cmd) != 3)
        return UNSUCCESS;
    client_event_private_message_received(arg_cmd[1], arg_cmd[2]);
    return SUCCESS;
}
