/*
** EPITECH PROJECT, 2024
** login.c
** File description:
** login
*/

#include "../server.h"

int validate_login(server_t *my_server, int index, char **arg_cmd, char *un)
{
    if (get_size_array(arg_cmd) != 2)
        return invalid_args(my_server, index);
    if (my_server->client_list[index].is_log == true) {
        send_to_client(CLIENT_SOCKET, "501", "You are already logged in.\n");
        return UNSUCCESS;
    }
    if (strlen(un) > MAX_NAME_LENGTH) {
        send_to_client(CLIENT_SOCKET, "502", "Invalid Username.\n");
        return UNSUCCESS;
    }
    return SUCCESS;
}

void login_ext(server_t *my_server, int index, char *parse_usernm, uuid_t uuid)
{
    if (check_exist_usr(my_server, index, parse_usernm) == UNSUCCESS) {
        my_server->client_list[index].username = strdup(parse_usernm);
        uuid_generate_random(uuid);
        uuid_unparse_lower(uuid, my_server->client_list[index].uuid);
        server_event_user_created(my_server->client_list[index].uuid,
        my_server->client_list[index].username);
    }
    strcpy(my_server->client_list[index].fileName,
    my_server->client_list[index].uuid);
    strcat(my_server->client_list[index].fileName, "_");
    strcat(my_server->client_list[index].fileName,
    my_server->client_list[index].username);
    my_server->client_list[index].is_log = true;
    create_new_usr(my_server, index, my_server->client_list[index].fileName);
    login_ok(my_server, index, CLIENT_UUID);
}

int login(server_t *my_server, int index, char **arg_cmd)
{
    uuid_t uuid;
    char *parsed_usernme;

    if (arg_cmd[1] == NULL) {
        send_to_client(CLIENT_SOCKET, "600",
            "Invalid argument. See /help.\n");
        return UNSUCCESS;
    }
    parsed_usernme = parse_arg_cmd(arg_cmd[1]);
    if (parsed_usernme == NULL) {
        send_to_client(CLIENT_SOCKET, "600",
            "Invalid argument. UUID must be enclosed in quotes.\n");
        return UNSUCCESS;
    }
    if (validate_login(my_server, index, arg_cmd, parsed_usernme) == UNSUCCESS)
        return UNSUCCESS;
    login_ext(my_server, index, parsed_usernme, uuid);
    free(parsed_usernme);
    return SUCCESS;
}

void login_ok(server_t *my_server, int index, char *uuid)
{
    server_event_user_logged_in(my_server->client_list[index].uuid);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (strcmp(uuid, my_server->client_list[i].uuid) == 0) {
            send_to_client(my_server->client_list[i].socket,
                "500", "Sucessfuly logged in.;");
            write(my_server->client_list[i].socket,
                my_server->client_list[index].uuid,
            strlen(my_server->client_list[index].uuid));
            write(my_server->client_list[i].socket, ";", 2);
            write(my_server->client_list[i].socket,
                my_server->client_list[index].username,
            strlen(my_server->client_list[index].username));
            write(my_server->client_list[i].socket, "\n", 1);
        }
    }
}

int create_new_usr(server_t *my_server, int index, char *fileName)
{
    int pathLength = strlen("./BDD/User/") + strlen(fileName)
        + strlen(".txt") + 1;
    char *filePath = malloc(pathLength);

    if (filePath == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return UNSUCCESS;
    }
    strcpy(filePath, "./BDD/User/");
    strcat(filePath, fileName);
    if (strcmp(&fileName[strlen(fileName) - 4], ".txt") != 0) {
        strcat(filePath, ".txt");
    }
    create_file(filePath);
    write_file(filePath, my_server->client_list[index].uuid);
    write_file(filePath, my_server->client_list[index].username);
    write_file(filePath, "1");
    free(filePath);
    return SUCCESS;
}
