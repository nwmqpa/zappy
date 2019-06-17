/*
** EPITECH PROJECT, 2019
** create_server.c
** File description:
** Create socket for the server.
*/

#include <sys/epoll.h>
#include "server.h"
#include "logger.h"
#include "client.h"
#include "protocols_graphic.h"

static void add_fd(server_t *server)
{
    struct epoll_event event = {0};

    event.events = EPOLLIN;
    event.data.fd = server->socket_client;
    if (epoll_ctl(server->epoll_fd_client, EPOLL_CTL_ADD, server->socket_client, &event)) {
        errorl("Failed to add file descriptor to epoll_fd\n");
        close(server->socket_client);
    }
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = server->socket_graphic;
    if (epoll_ctl(server->epoll_fd_graphic, EPOLL_CTL_ADD, server->socket_graphic, &event)) {
        errorl("Failed to add file descriptor to epoll_fd\n");
        close(server->socket_graphic);
    }
}

static void setup_teams(server_t *server, options_t *options)
{
    int size = 0;
    int i = 0;

    while (options->name[size++]);
    server->teams = malloc(sizeof(team_t *) * size + 2);
    for (; options->name[i]; ++i) {
        server->teams[i] = malloc(sizeof(team_t));
        server->teams[i]->name = options->name[i];
        server->teams[i]->clients = calloc(sizeof(int), options->client_nb);
    }
    server->teams[i] = NULL;
}

static void setup_network(server_t *server, options_t *options)
{
    debugl("Setup of network.\n");
    server->socket_client = create_client_listener(options);
    server->socket_graphic = create_graphic_listener(options);
    server->epoll_fd_client = epoll_create1(0);
    server->epoll_fd_graphic = epoll_create1(0);
    if (server->socket_client == -1 || server->socket_graphic == -1 ||
    server->epoll_fd_client == -1 || server->epoll_fd_graphic == -1) {
        fatall("Cannot connect, quitting Zappy!\n");
        free(server);
        exit(84);
    }
}

server_t *create_server(options_t *options)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        fatall("Malloc failed quitting Zappy!\n");
        exit(84);
    }
    setup_network(server, options);
    server->clients = create_list();
    server->graphic_clients = create_list();
    server->width = options->width;
    server->height = options->height;
    server->freq = options->freq;
    server->client_per_team = options->client_nb;
    server->map = create_map(server->width, server->height);
    memset(&server->reg, 0, sizeof(phr_t));
    register_all_handlers(server);
    add_fd(server);
    setup_teams(server, options);
    return server;
}
