/*
** EPITECH PROJECT, 2024
** load_save.c
** File description:
** load_save
*/

#include "server.h"

int load_save(void)
{
    DIR *d;
    struct dirent *dir;
    char *path = NULL;
    char *fullpath;
    char **tmp;

    d = open_directory("BDD/User/");
    dir = readdir(d);
    while ((dir) != NULL) {
        path = dir->d_name;
        if (strlen(path) > 4 && !strcmp(path + strlen(path) - 4, ".txt")) {
            fullpath = create_fullpath(path);
            tmp = read_file(fullpath);
            server_event_user_loaded(tmp[1], tmp[0]);
            free(fullpath);
        }
        dir = readdir(d);
    }
    closedir(d);
    return SUCCESS;
}
