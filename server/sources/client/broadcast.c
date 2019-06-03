/*
** EPITECH PROJECT, 2019
** broadcast.c
** File description:
** Broadcast command file.
*/

#include "client_commands.h"

// TODO: Calculate the tile.
static void send_text(void *ptr, const void *data)
{
    const server_t *server = (server_t *) data;
    const char *text = (char *) data + 1;
    client_t *client = (client_t *) ptr;
    int tile = 1;

    dprintf(client->id, "message %d, %s\n", tile, text);
}

static void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    int tile = 0;
    const void *data[2] = {0};

    data[0] = server;
    data[1] = text;
    map(server->clients, send_text, data);
}

char *broadcast(client_t *client, server_t *server, const char *text)
{
    client->cooldown = 7;
    send_to_clients(server, text, client->id);
    return "ok";
}
