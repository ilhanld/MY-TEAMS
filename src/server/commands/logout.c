/*
** EPITECH PROJECT, 2024
** logout.c
** File description:
** logout
*/

#include "../server.h"

int logout(server_t *my_server, int index, char **arg_cmd)
{
    if (get_size_array(arg_cmd) != 1)
        return invalid_args(my_server, index);
    if (my_server->client_list[index].is_log == true) {
        my_server->client_list[index].is_log = false;
        server_event_user_logged_out(my_server->client_list[index].uuid);
        send_to_client(CLIENT_SOCKET, "505", "Sucessfuly logout\n");
        logout_usr(my_server->client_list[index].fileName);
        my_server->client_list[index].username = NULL;
        free(CLIENT_BUFFER);
        CLIENT_BUFFER = malloc(sizeof(char) * MAX_BUFFER);
        memset(CLIENT_BUFFER, 0, MAX_BUFFER);
        shutdown(CLIENT_SOCKET, SHUT_RDWR);
        CLIENT_SOCKET = 0;
    } else {
        send_to_client(CLIENT_SOCKET, "100",
            "You must be logged in to use this command.\n");
    }
    return SUCCESS;
}

int logout_usr(char *fileName)
{
    int pathLength = strlen("./BDD/User/") + strlen(fileName)
        + strlen(".txt") + 1;
    char *filePath = malloc(pathLength);

    if (filePath == NULL) {
        return -1;
    }
    strcpy(filePath, "./BDD/User/");
    strcat(filePath, fileName);
    strcat(filePath, ".txt");
    change_file_data(filePath, "0", 3);
    free(filePath);
    return 0;
}
