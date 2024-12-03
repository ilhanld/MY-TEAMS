/*
** EPITECH PROJECT, 2024
** loop_sever2.c
** File description:
** loop_server2
*/

#include "server.h"

char *construct_file_path(char *dir_name)
{
    int size;
    char *filePath;

    size = strlen("./BDD/User/") + strlen(dir_name) + 1;
    filePath = malloc(sizeof(char) * size);
    memset(filePath, '\0', size);
    strcpy(filePath, "./BDD/User/");
    strcat(filePath, dir_name);
    return filePath;
}

void process_file(char *filePath)
{
    change_file_data(filePath, "1", 3);
    free(filePath);
}

void check_bdd(void)
{
    DIR *d;
    struct dirent *dir;
    char *path = NULL;
    char *filePath;

    d = opendir("./BDD/User/");
    if (!d)
        return;
    dir = readdir(d);
    while (dir != NULL) {
        path = dir->d_name;
        if (strlen(path) > 4 && !strcmp(path + strlen(path) - 4, ".txt")) {
            filePath = construct_file_path(dir->d_name);
            process_file(filePath);
        }
        dir = readdir(d);
    }
    closedir(d);
}

void do_handler(int sig)
{
    if (sig >= 0) {
        check_bdd();
        exit(0);
    }
    return;
}

void sig_handler(void)
{
    struct sigaction act;

    act.sa_handler = do_handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
}
