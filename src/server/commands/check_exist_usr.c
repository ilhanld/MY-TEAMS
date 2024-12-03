/*
** EPITECH PROJECT, 2024
** check_exist_usr.c
** File description:
** check_exist_usr
*/

#include "../server.h"

char *create_tmp_filename(char *fileName)
{
    char *tmp_fileName;

    tmp_fileName = strdup(fileName);
    strcat(tmp_fileName, ".txt");
    return tmp_fileName;
}

char *create_fullpath(char *path)
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

void update_client(server_t *my_server, int index, char **tmp)
{
    my_server->client_list[index].username = strdup(tmp[1]);
    strcpy(my_server->client_list[index].uuid, tmp[0]);
    if (atoi(tmp[2]) == 0)
        my_server->client_list[index].is_log = false;
    else
        my_server->client_list[index].is_log = true;
}

int read_file_usr(server_t *my_server, int index, char *tmp_fl, char *path)
{
    char **tmp;
    char *fullpath;
    char *tmp_path;

    tmp_path = strdup(path);
    delete_uuid(tmp_path, 37);
    if (strcmp(tmp_fl, tmp_path) == 0) {
        fullpath = create_fullpath(path);
        tmp = read_file(fullpath);
        update_client(my_server, index, tmp);
        free(fullpath);
        return SUCCESS;
    }
    return UNSUCCESS;
}

int check_exist_usr(server_t *my_server, int index, char *fileName)
{
    DIR *d;
    struct dirent *dir;
    char *path = NULL;
    char *tmp_fileName;

    tmp_fileName = create_tmp_filename(fileName);
    d = open_directory("BDD/User/");
    dir = readdir(d);
    while ((dir) != NULL) {
        path = dir->d_name;
        if (read_file_usr(my_server, index, tmp_fileName, path) == SUCCESS)
            return SUCCESS;
        dir = readdir(d);
    }
    closedir(d);
    return UNSUCCESS;
}
