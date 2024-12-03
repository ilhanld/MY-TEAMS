/*
** EPITECH PROJECT, 2024
** create_bdd.c
** File description:
** create_bdd
*/

#include "utils.h"

int create_bdd(void)
{
    if (check_dir_exist("./BDD") == 0) {
        return 1;
    }
    mkdir("./BDD", 0777);
    mkdir("./BDD/User", 0777);
    mkdir("./BDD/Team", 0777);
    return 0;
}

int create_dir(char *dirPath)
{
    if (check_dir_exist(dirPath) == 0)
        return 1;
    mkdir(dirPath, 0777);
    return 0;
}

int check_dir_exist(char *dirPath)
{
    struct stat st;

    if (stat(dirPath, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 0;
    }
    return 1;
}
