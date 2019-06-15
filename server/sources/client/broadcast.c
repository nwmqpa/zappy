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
    const char *text = (char *) data + 1;
    client_t *client = (client_t *) ptr;
    int tile = 1;

    dprintf(client->id, "message %d, %s", tile, text);
}

static void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    const void *data[2] = {0};

    data[0] = server;
    data[1] = text;
    map(server->clients, send_text, data);
}

char *broadcast(client_t *client, server_t *server, const char *text)
{
    send_to_clients(server, text, client->id);
    return strdup("ok");
}