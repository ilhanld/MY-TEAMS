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
#include <signal.h>
#include <regex.h>

#include <netdb.h>
#include <pwd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <netinet/in.h>

#include <arpa/inet.h>
#include <uuid/uuid.h>


#include "../../libs/myteams/logging_server.h"
#include "../utils/utils.h"

#ifndef SERVER_H_
    #define SERVER_H_

    #define ERROR 84
    #define UNSUCCESS 1
    #define SUCCESS 0

    #define MAX_CLIENTS 100
    #define MAX_NAME_LENGTH 32
    #define MAX_BUFFER 512
    #define MAX_CLIENT_TEAMS 100
    #define MAX_TEAM_CHANNELS 100

    #define MSG120 "Service ready in nnn minutes."
    #define MSG125 "Data connection already open, transfer starting."
    #define MSG150 "File status okay, about to open data connection."
    #define MSG200 "Command okay."
    #define MSG214 "Help message."
    #define MSG220 "Service ready for new user."
    #define MSG221 "Service closing control connection."
    #define MSG226 "Closing data connection."
    #define MSG227 "Entering Passive Mode."
    #define MSG230 "User logged in, proceed."
    #define MSG250 "Requested file action okay, completed."
    #define MSG257 "PATHNAME created."
    #define MSG331 "User name okay, need password."
    #define MSG332 "Need account for login."
    #define MSG500 "Syntax error, command unrecognized.\n"
    #define MSG530_1 "Please login with USER and PASS."
    #define MSG530_2 "User already logged in."
    #define MSGxxx "Error (RFC compliant)"
    #define MSG501 "Invalid arguments.\n"
    #define MSG389 "UUID does not exist.\n"

    #define CLIENT_PATH my_server->client_list[index].path
    #define CLIENT_SOCKET my_server->client_list[index].socket
    #define CLIENT_BUFFER my_server->client_list[index].buffer
    #define CLIENT_USERNAME my_server->client_list[index].usermane
    #define CLIENT_UUID my_server->client_list[index].uuid

    #define SERVER_SOCKET my_server->server_socket
    #define C_ADDR (struct sockaddr *)&my_server->client_addr
    #define C_ADDRL &client_addr_len

    #define AFD my_server->actual_file_descriptor
    #define RFD my_server->read_file_descriptor

/* STRUCT DEF*/

typedef struct sockaddr_in SOCKADDR_IN_t;
typedef struct sockaddr SOCKADDR_t;
typedef struct in_addr IN_ADDR_t;
typedef struct passwd passwd_t;

enum mode {
    NONE,
    ACTIVE,
    PASSIVE
};

typedef struct client_t {
    char *username;
    char *password;

    bool is_log;

    int socket;

    char uuid[40];
    char *fileName;

    char *path;

    char *buffer;

    int data_socket;
    int data_port;
    char *data_ip;
    SOCKADDR_IN_t data_addr;

    enum mode mode;
} client_t;

typedef struct server_s {
    int port;
    char *path;
    int server_socket;

    int used_socket;
    int limit;

    SOCKADDR_IN_t control_addr;
    SOCKADDR_IN_t client_addr;

    fd_set read_file_descriptor;
    fd_set actual_file_descriptor;
    fd_set writefds;

    client_t *client_list;

    int select_value;
} server_t;

/* END STRUCT DEF */

/* main.c DEF */

int teams_server(char *port_str);
int parsing(server_t *my_server);
void process_data(server_t *my_server, int index, char *buffer);

/* END main.c DEF*/

/* server.c DEF */

void init_client_list(server_t *my_server);
void init_server_struct(server_t *my_server);
int starting_server(server_t *my_server);
void set_client_socket(server_t *my_server);
void set_client_socket2(server_t *my_server, int index);
char **read_user_file(char *fullpath);

/* END server.c DEF */


/* handle_client_data.c DEF */

void read_data(server_t *my_server, int index);
void handle_client_data(server_t *my_server);

/* END handle_client_data.c DEF */

/* handle_new_client.c DEF */

void create_new_client(server_t *my_server);
void handle_new_connection(server_t *my_server);

/* END handle_new_client.c DEF */

/* send.c DEF */

void send_to_client(int client_socket, char *code, char *MSG);

/* END send.c DEF */

/* error.c DEF */

void socket_error(int server_socket);
void htons_error(server_t *my_server);
void bind_error(int bind);
void listen_error(int listen);
void select_error(int select_value);

/* END error.c DEF */

/* check_client_logged.c DEF */

int check_client_logged(server_t *my_server, char *username);

/* END check_client_logged.c DEF */

/* load_save.c DEF */

int load_save(void);

int check_exist_usr(server_t *my_server, int index, char *fileName);
int handle_directory(server_t *my_server, int index, char *fileName);

/* END load_save.c DEF */

/*  DEF client_send_message.c */

int find_uuid(char *uuid_search, server_t *my_server, int index);
void client_send_message(server_t *my_server, int cs, int index, char *MSG);

/*  END clien_send_message.c */


/* DEF parser_arg.c */

regex_t compile_regex(char *pattern);
int execute_regex(regex_t *regex, char *str, regmatch_t *matches);
char *extract_match(char *str, regmatch_t *matches);
char *parse_arg_cmd(char *arg_cmd);

/* END parser_arg.c */


/* ---- COMMANDS ---- */

/* handle_commands.c DEF */

void check_commands(server_t *my_server, int index, char *cmd);
int exec_commands(server_t *my_server, int index, char **arg_cmd);

/* END handle_commands.c DEF */

/* login.c DEF */

int login(server_t *my_server, int index, char **arg_cmd);
int create_new_usr(server_t *my_server, int index, char *fileName);
void login_ok(server_t *my_server, int index, char *uuid);
char *create_fullpath(char *path);
int validate_login(server_t *my_server, int index, char **arg_cmd, char *un);

/* END login.c DEF */

/* logout.c DEF */

int logout(server_t *my_server, int index, char **arg_cmd);
int logout_usr(char *fileName);

/* END logout.c DEF */

/* users.c DEF */

int users(server_t *my_server, int index, char **arg_cmd);
int process_files(server_t *my_server, int index);
int write_to_client(char **tmp, server_t *my_server, int index);

/*END users.c DEF*/

/* USER [uuid] user.c DEF */

int user(server_t *my_server, int index, char **arg_cmd);

/* END user.c DEF */

/* SEND COMMANDS send_client.c */

int find_uuid(char *uuid_search, server_t *my_server, int index);
void client_send_message(server_t *my_server, int cs, int index, char *MSG);
bool validate_send_cl(server_t *my_server, int index, int i_ds);
void send_messages(server_t *my_server, int index, int index_d, char *message);
int send_cl(server_t *my_server, int index, char **arg_cmd);

/*  END send_client.c*/

/* Create COMMANDS create.c*/

int create(server_t *my_server, int index, char **arg_cmd);
int check_exist_team(char *dirName);
int new_team(char *dirName, char *description);

/*  END CREATE COMMANDS create.c */

/* sig_handler.c DEF */

void sig_handler(void);

/* END sig_handler.c DEF */

int invalid_args(server_t *my_server, int index);

/* ---- END COMMANDS ---- */

#endif
