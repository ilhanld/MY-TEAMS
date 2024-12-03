/*
** EPITECH PROJECT, 2024
** write_file.c
** File description:
** write_file
*/

#include "utils.h"

int write_file(char *filePath, char *content)
{
    FILE *fd = fopen(filePath, "a");

    if (fd == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fd.\n");
        return 1;
    }
    fprintf(fd, "%s\n", content);
    fclose(fd);
    return 0;
}

int change_file_data(char *filePath, char *content, int line_number)
{
    FILE *fd = fopen(filePath, "r+");
    char buffer[2048];
    int current_line = 0;

    while (fgets(buffer, sizeof(buffer), fd)) {
        current_line++;
        if (current_line == line_number) {
            fseek(fd, -strlen(buffer), SEEK_CUR);
            fprintf(fd, "%s\n", content);
            fclose(fd);
            return 0;
        }
    }
    fprintf(stderr, "La ligne spécifiée n'existe pas dans le fichier.\n");
    fclose(fd);
    return 1;
}

int is_file_empty(char *filePath)
{
    FILE *fd = fopen(filePath, "r");
    long size;

    if (fd == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fclose(fd);
    if (size == 0) {
        return 0;
    } else {
        return 1;
    }
}
