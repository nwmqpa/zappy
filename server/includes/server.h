/*
** EPITECH PROJECT, 2019
** server.h
** File description:
** server header file.
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include "client.h"
#include "options.h"
#include "generic_list.h"
#include "map.h"

typedef struct team_s {
    char *name;
    int *clients;
} team_t;

typedef struct server_s {
    unsigned int width;
    unsigned int height;
    int epoll_fd_client;
    int epoll_fd_graphic;
    int socket_client;
    int socket_graphic;
    team_t **teams;
    list_t *clients;
    int client_per_team;
    map_t *map;
} server_t;

// Create server and initiliaze it from options.
server_t *create_server(options_t *options);

int create_client_listener(options_t *options);
int create_graphic_listener(options_t *options);

int add_client_to_team(server_t *server, client_t *client, const char *team);

void print_server(server_t *server);

#endif /* SERVER_H_ */
