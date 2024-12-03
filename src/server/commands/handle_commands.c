/*
** EPITECH PROJECT, 2024
** handle_command.c
** File description:
** handle_commands
*/

#include "../server.h"

void check_commands(server_t *my_server, int index, char *cmd)
{
    char **arg_cmd;

    if (cmd == NULL || strcmp(cmd, "\r\n") == 0) {
        return;
    }
    arg_cmd = my_strtok_to_word_array(cmd, "  \t\n\r");
    if (arg_cmd[0] == NULL) {
        return;
    }
    if (exec_commands(my_server, index, arg_cmd) != SUCCESS) {
        send_to_client(CLIENT_SOCKET, "500", MSG500);
        return;
    }
}

int exec_commands(server_t *my_server, int index, char **arg_cmd)
{
    if (arg_cmd == NULL || arg_cmd[0] == NULL) {
        return UNSUCCESS;
    }
    if (strncmp(arg_cmd[0], "/login", 6) == 0)
        return login(my_server, index, arg_cmd);
    if (strncmp(arg_cmd[0], "/logout", 7) == 0)
        return logout(my_server, index, arg_cmd);
    if (strncmp(arg_cmd[0], "/users", 6) == 0)
        return users(my_server, index, arg_cmd);
    if (strncmp(arg_cmd[0], "/user", 5) == 0)
        return user(my_server, index, arg_cmd);
    if (strncmp(arg_cmd[0], "/send", 5) == 0)
        return send_cl(my_server, index, arg_cmd);
    if (strncmp(arg_cmd[0], "/create", 7) == 0)
        return create(my_server, index, arg_cmd);
    return UNSUCCESS;
}
