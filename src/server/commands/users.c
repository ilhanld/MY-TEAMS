/*
** EPITECH PROJECT, 2024
** users.c
** File description:
** users
*/

#include "../server.h"

int send_client_all_info(server_t *my_server, int index, char **tmp)
{
    if (get_size_array(tmp) >= 3) {
        send_to_client(CLIENT_SOCKET, "350", "toutes les infos des users;");
        write(CLIENT_SOCKET, tmp[0], strlen(tmp[0]));
        write(CLIENT_SOCKET, ";", 1);
        write(CLIENT_SOCKET, tmp[1], strlen(tmp[1]));
        write(CLIENT_SOCKET, ";", 1);
        write(CLIENT_SOCKET, tmp[2], strlen(tmp[2]));
        write(CLIENT_SOCKET, "\n", 1);
        return SUCCESS;
    }
    return UNSUCCESS;
}

char **process_filed(server_t *my_server, int index, char *path)
{
    char *fullpath;
    char **tmp;

    if (strlen(path) > 4 && !strcmp(path + strlen(path) - 4, ".txt")) {
        fullpath = create_fullpath(path);
        tmp = read_file(fullpath);
        send_client_all_info(my_server, index, tmp);
        free(fullpath);
    }
    return tmp;
}

int process_files(server_t *my_server, int index)
{
    DIR *d;
    struct dirent *dir;
    char *path = NULL;

    d = opendir("BDD/User/");
    if (d) {
        dir = readdir(d);
        while (dir != NULL) {
            path = dir->d_name;
            puts(path);
            process_filed(my_server, index, path);
            dir = readdir(d);
        }
        closedir(d);
    }
    return SUCCESS;
}

bool valid_users_arguments(server_t *my_server, int index, char **arg_cmd)
{
    if (get_size_array(arg_cmd) != 1) {
        send_to_client(my_server->client_list[index].socket, "600",
        "Invalid argument. See /help.\n");
        return false;
    }
    if (my_server->client_list[index].is_log == false) {
        send_to_client(CLIENT_SOCKET, "100",
            "You must be logged in to use this command.\n");
        return false;
    }
    return true;
}

int users(server_t *my_server, int index, char **arg_cmd)
{
    if (valid_users_arguments(my_server, index, arg_cmd) == false) {
        return (SUCCESS);
    }
    process_files(my_server, index);
    return SUCCESS;
}
