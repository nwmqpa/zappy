/*
** EPITECH PROJECT, 2019
** create_server.c
** File description:
** Create socket for the server.
*/

#include "server.h"
#include "logger.h"
#include "client.h"

server_t *create_server(options_t *options)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        fatall("Malloc failed quitting Zappy!\n");
        exit(84);
    }
    server->listener_client = create_client_listener(options);
    server->listener_graphic = create_graphic_listener(options);
    server->clients = create_list();
    if (server->listener_client == -1 || server->listener_client == -1) {
        free(server);
        return NULL;
    }
    server->teams = options->name;
    return server;
}

void print_server(server_t *server)
{
    printf("Server {\n"
            "    listener_client: %hd,\n"
            "    listener_graphic: %hd,\n"
            "    teams: [", server->listener_client, server->listener_graphic);
    for (int i = 0; server->teams[i]; ++i)
        printf("%s%s", server->teams[i], server->teams[i + 1] ? ", " : "]\n" );
    printf("}\n");
}
