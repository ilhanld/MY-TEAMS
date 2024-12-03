/*
** EPITECH PROJECT, 2024
** user.c
** File description:
** user
*/

#include "../server.h"

int user(server_t *my_server, int index, char **arg_cmd)
{
    char *uid;

    if (get_size_array(arg_cmd) != 2)
        return invalid_args(my_server, index);
    if (parse_arg_cmd(arg_cmd[1]) == NULL)
        return invalid_args(my_server, index);
    uid = strdup(parse_arg_cmd(arg_cmd[1]));
    if (uid == NULL || handle_directory(my_server, index, uid) == UNSUCCESS) {
        send_to_client(CLIENT_SOCKET, "101", "User doesn't exist.");
        write(CLIENT_SOCKET, ";", 1);
        write(CLIENT_SOCKET, uid, strlen(uid));
        write(CLIENT_SOCKET, "\n", 1);
        free(uid);
        return UNSUCCESS;
    }
    free(uid);
    return SUCCESS;
}

char *construct_fullpath(char *path)
{
    int size;
    char *fullpath;

    size = strlen("BDD/User/") + strlen(path) + 1;
    fullpath = malloc(sizeof(char) * size);
    memset(fullpath, '\0', size);
    strcpy(fullpath, "BDD/User/");
    strcat(fullpath, path);
    return fullpath;
}

int write_to_client(char **tmp, server_t *my_server, int index)
{
    if (get_size_array(tmp) >= 3) {
        send_to_client(CLIENT_SOCKET, "300", "Info of user;");
        write(CLIENT_SOCKET, tmp[1], strlen(tmp[1]));
        write(CLIENT_SOCKET, ";", 1);
        write(CLIENT_SOCKET, tmp[0], strlen(tmp[0]));
        write(CLIENT_SOCKET, ";", 1);
        write(CLIENT_SOCKET, tmp[2], 1);
        write(CLIENT_SOCKET, "\n", 1);
        return SUCCESS;
    }
    return UNSUCCESS;
}

int find_file_in_directory(DIR *d, char *fileName, char **path)
{
    struct dirent *dir;

    dir = readdir(d);
    while (dir != NULL) {
        *path = dir->d_name;
        if (strncmp(fileName, *path, 36) == 0) {
            return SUCCESS;
        }
        dir = readdir(d);
    }
    return UNSUCCESS;
}

int handle_directory(server_t *my_server, int index, char *fileName)
{
    char *path = NULL;
    char *fullpath;
    char **tmp;
    DIR *d;

    d = open_directory("BDD/User/");
    if (find_file_in_directory(d, fileName, &path) == SUCCESS) {
        fullpath = construct_fullpath(path);
        puts(fullpath);
        tmp = read_file(fullpath);
        write_to_client(tmp, my_server, index);
        free(fullpath);
        closedir(d);
        return SUCCESS;
    }
    closedir(d);
    return UNSUCCESS;
}
