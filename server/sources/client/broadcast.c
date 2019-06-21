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
    const struct {
        server_t *server;
        const char *text;
        ia_t *sender;
    } *datas = data;
    ia_t *client = (ia_t *) ptr;
    int tile = 0;

    if (client->position.x == datas->sender->position.x &&
            client->position.y == datas->sender->position.y)
        tile = 0;
    else
        tile = calculate_tile(client->position, datas->sender->position);
    dprintf(client->id, "message %d, %s", tile, datas->text);
}

static void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    ia_t *client = get_cmp_list(server->clients, client_cmp, &local_id);
    struct {
        server_t *server;
        const char *text;
        ia_t *sender;
    } data = {
        server,
        text,
        client
    };

    map(server->clients, send_text, &data);
}

char *broadcast(ia_t *client, server_t *server, const char *text)
{
    send_to_clients(server, text + 1, client->id);
    return strdup("ok");
}
