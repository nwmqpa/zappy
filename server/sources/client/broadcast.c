/*
** EPITECH PROJECT, 2019
** broadcast.c
** File description:
** Broadcast command file.
*/

#include "client_commands.h"

static int abs_modulo(int data, int num)
{
    int ret = data;

    if (data < 0) {
        while (ret < 0)
            ret += num;
        return (ret);
    }
    if (data > num) {
        while (ret >= num)
            ret -= num;
        return (ret);
    }
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

    if (client->id == datas->sender->id)
        return;
    if (client->position.x == datas->sender->position.x &&
            client->position.y == datas->sender->position.y)
        tile = 0;
    else {
        tile = calculate_tile(datas->server,
        client->position, datas->sender->position);
        tile -= (client->direction - 2) * 2;
        tile = abs_modulo(tile, 9);
    }
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
