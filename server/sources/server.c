/*
** EPITECH PROJECT, 2019
** create_server.c
** File description:
** Create socket for the server.
*/

#include "server.h"
#include "logger.h"

static void fill_addr(short port, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}

server_t *create_server(options_t *options)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        fatall("Malloc failed quitting Zappy!\n");
        exit(84);
    }
    server->listener_client = create_client_listener(options);
    server->listener_graphic = create_graphic_listener(options);
    if (server->listener_client == -1 || server->listener_client == -1) {
        free(server);
        return NULL;
    }
    server->teams = create_teams(options);
    return server;
}
