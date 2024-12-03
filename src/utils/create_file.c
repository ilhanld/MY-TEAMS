/*
** EPITECH PROJECT, 2024
** create_file.c
** File description:
** create_file
*/

#include "utils.h"

int create_file(char *filePath)
{
    FILE *fd;

    if (check_file_exist(filePath) == 0) {
        if (remove(filePath) != 0) {
            printf("Erreur lors de la suppression du fichier existant.\n");
            return 1;
        }
    }
    fd = fopen(filePath, "r+");
    if (fd == NULL) {
        return 1;
    }
    fclose(fd);
    return 0;
}

int check_file_exist(char *filePath)
{
    FILE *fd = fopen(filePath, "r");

    if (fd != NULL) {
        fclose(fd);
        return 0;
    }
    return 1;
}
