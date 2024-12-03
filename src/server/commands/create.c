/*
** EPITECH PROJECT, 2024
** create.c
** File description:
** create
*/

#include "../server.h"

int create(server_t *my_server, int index, char **arg_cmd)
{
    if (get_size_array(arg_cmd) != 3) {
        send_to_client(CLIENT_SOCKET, "600", "Invalid argument. See /help.\n");
        return SUCCESS;
    }
    if (my_server->client_list[index].is_log == false) {
        send_to_client(CLIENT_SOCKET, "100",
            "You must be logged in to use this command.\n");
        return SUCCESS;
    }
    if (check_exist_team(arg_cmd[1]) == SUCCESS) {
        send_to_client(CLIENT_SOCKET, "801", "This team already exist.\n");
        return SUCCESS;
    }
    new_team(arg_cmd[1], arg_cmd[2]);
    send_to_client(CLIENT_SOCKET, "800", "Team has been created.\n");
    return SUCCESS;
}

int check_exist_team(char *dirName)
{
    DIR *d;
    struct dirent *dir;
    char *path = NULL;

    d = opendir("BDD/Team/");
    if (!d) {
        return 1;
    }
    dir = readdir(d);
    while (dir != NULL) {
        path = dir->d_name;
        if (strcmp(dirName, path) == 0) {
            return SUCCESS;
        }
        dir = readdir(d);
    }
    closedir(d);
    return UNSUCCESS;
}

void create_write_file(char *descPath, char *description, char *dirPath)
{
    create_file(descPath);
    write_file(descPath, description);
    free(dirPath);
}

char *create_descpath(char *dirPath, char *descPath)
{
    strcpy(descPath, dirPath);
    strcat(descPath, "/description.txt");
    return descPath;
}

int new_team(char *dirName, char *description)
{
    int pathLength = strlen("./BDD/Team/") + strlen(dirName);
    char *dirPath = malloc(pathLength);
    char *filePath = malloc(sizeof(char) * 100);
    char *descPath = malloc(sizeof(char) * 100);

    memset(filePath, 0, 100);
    memset(descPath, 0, 100);
    if (dirPath == NULL) {
        return UNSUCCESS;
    }
    strcpy(dirPath, "./BDD/Team/");
    strcat(dirPath, dirName);
    mkdir(dirPath, 0777);
    strcpy(filePath, dirPath);
    strcat(filePath, "/user.txt");
    create_file(filePath);
    write_file(filePath, "ALL USER SUBSCRIBED IN TEAM :");
    descPath = create_descpath(dirPath, descPath);
    create_write_file(descPath, description, dirPath);
    return SUCCESS;
}
