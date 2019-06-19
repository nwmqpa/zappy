/*
** EPITECH PROJECT, 2019
** broadcast.c
** File description:
** Broadcast command file.
*/

#include "client_commands.h"

static int calculate_tile(pos_t sender, pos_t client)
{
    // TODO: Code de thomas (pas opti).
    return 0;
}

static void send_text(void *ptr, const void *data)
{
    const server_t *server = (server_t *) data;
    const char *text = (char *) (data + sizeof(void *));
    const client_t *sender = (client_t *) (data + (sizeof(void *) * 2));
    client_t *client = (client_t *) ptr;
    int tile = 0;

    if (client->position.x == sender->position.x &&
            client->position.y == sender->position.y)
        tile = 0;
    else
        tile = calculate_tile(client->position, sender->position);
    dprintf(client->id, "message %d, %s", tile, text);
}

static void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    const void *data[3] = {0};
    client_t *client = get_cmp_list(server->clients, client_cmp, &local_id);

    data[0] = server;
    data[1] = text;
    data[2] = client;
    map(server->clients, send_text, data);
}

char *broadcast(client_t *client, server_t *server, const char *text)
{
    send_to_clients(server, text, client->id);
    return strdup("ok");
}
