/*
** EPITECH PROJECT, 2019
** broadcast.c
** File description:
** Broadcast command file.
*/

#include "client_commands.h"

static void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    int tile = 0;
    int y = 4;

    map(server->clients);
    dprintf(local_id, "message %d, %s\n", tile, text);
}

char *broadcast(client_t *client, server_t *server, const char *text)
{
    client->cooldown = 7;
    send_to_clients(server, text, client->id);
    return "ok";
}
