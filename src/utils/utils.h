/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>

#ifndef UTILS_H_
    #define UTILS_H_

/* ---- lib function DEF ---- */

int is_number(const char *str);
char **my_strtok_to_word_array(char *cmd, char *tok);
int get_size_array(char **array);
void free_tab(char **array);

/* create_file.c DEF */

int create_file(char *filePath);
int check_file_exist(char *filePath);

/* END create_file.c DEF */

/* read_file.c DEF */

char **read_file(char *filePath);
DIR* open_directory(char *dir_path);

/* END read_file.c DEF */

/* write_file.c DEF */

int write_file(char *filePath, char *content);
int change_file_data(char *filePath, char *content, int line_number);
int is_file_empty(char *filePath);

/* END write_file.c DEF */

/* create_bdd.c DEF */

int create_bdd(void);
int create_dir(char *dirPath);
int check_dir_exist(char *dirPath);

/* END create_bdd.c DEF */

/*  delete_uuid.c  DEF */

void delete_uuid(char *str, int n);

/*  END delete_uuid.c */

/*  buffer.c  DEF */

int check_buffer(char *buffer);

/*  END buffer.c */

/* ---- END lib function DEF ---- */

#endif /* !UTILS_H_ */
