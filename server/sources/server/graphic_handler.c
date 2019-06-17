/*
** EPITECH PROJECT, 2019
** graphic_handler.c
** File description:
** Graphic function dispatched.
*/

#include "logger.h"
#include "server.h"
#include "protocols_graphic.h"

static int graph_cmp(const void *rhs, const void *lhs)
{
    int sock = *(int *) rhs;
    int test = *(int *) lhs;

    return sock == test;
}

int on_connect_graphic(int socket, void *data)
{
    server_t *server = data;
    int *new = malloc(sizeof(int));

    debugl("New graphic client connected.\n");
    *new = socket;
    append_list(server->graphic_clients, new);
    return 0;
}

int on_delete_graphic(int socket, void *data)
{
    server_t *server = data;

    debugl("A graphic client just disconnect.\n");
    int *sock = pop_cmp_list(server->graphic_clients, graph_cmp,
            (void *) &socket);
    dprintf(*sock, "GoodBye.\n");
    //close(*sock);
    return 0;
}

int on_active_graphic(int socket, void *data)
{
    server_t *server = (server_t *) data;

    debugl("Graphic client sent a message.\n");
    return handle_packet(socket, server);
}
