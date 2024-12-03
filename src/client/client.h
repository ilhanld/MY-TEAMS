/*
** EPITECH PROJECT, 2024
** client.c
** File description:
** client
*/
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>

#include "../utils/utils.h"
#include "../../libs/myteams/logging_client.h"

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

    #define H0 "\t/help\n"
    #define H1 "\t/login [user_name]\n"
    #define H2 "\t/logout\n"
    #define H3 "\t/users\n"
    #define H4 "\t/user [user_uuid]\n"
    #define H5 "\t/send [user_uuid] [message_body]\n"
    #define H6 "\t/messages [user_uuid]\n"
    #define H7 "\t/subscribe [team_uuid]\n"
    #define H8 "\t/subscribed ?[team_uuid]\n"
    #define H9 "\t/unsubscribe [team_uuid]\n"
    #define H10 "\t/use ?[team_uuid] ?[channel_uuid] ?[thread_uuid]\n"
    #define H11 "\t/create\n"
    #define H12 "\t/list\n"
    #define H13 "\t/info\n"

typedef struct client {
    char *ip;
    int port;
    int sock;
    char *buffer;
    char in_buffer[MAX_BUFFER];
    fd_set readfds;

    char *username;
    char *uuid;
} client_t;

typedef struct message {
    char *message;
    char sender_name;
    char *receiver_name;
    time_t timestamp;
} message_t;

typedef struct user {
    char *username;
    char *uuid;
    message_t message;
} user_t;

typedef struct conv {
    user_t user;
} conv_t;

void start_client(client_t *client);
void setup_client(client_t *client);
void init_struct(client_t *client, char *ip, int socket);

int check_buffer(char *buffer);

void loop(client_t *client);

void send_data(client_t *client);

void handle_data(client_t *client);

int check_commands(client_t *client);
int help(void);

int logout_client(client_t *client);

int login_client(client_t *client);

int recv_msg_client(client_t *client);

int unknow_usr(client_t *client);

int all_info_usr(client_t *client);

int info_of_usr(client_t *client);

#endif
