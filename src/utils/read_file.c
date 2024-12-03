/*
** EPITECH PROJECT, 2024
** read_file.c
** File description:
** read_file
*/

#include "utils.h"

char **read_file(char *filePath)
{
    int nb_lines = 0;
    char buffer[2048];
    int i;
    char **array;
    FILE *fd;

    fd = fopen(filePath, "r");
    while (fgets(buffer, sizeof(buffer), fd) != NULL)
        nb_lines++;
    rewind(fd);
    array = malloc((nb_lines + 1) * sizeof(char *));
    for (i = 0; fgets(buffer, sizeof(buffer), fd) != NULL; i++) {
        buffer[strcspn(buffer, "\n")] = '\0';
        array[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(array[i], buffer);
    }
    array[i + 1] = NULL;
    rewind(fd);
    fclose(fd);
    return array;
}

DIR* open_directory(char *dir_path)
{
    DIR *d;

    d = opendir(dir_path);
    if (!d) {
        return NULL;
    }
    return d;
}
