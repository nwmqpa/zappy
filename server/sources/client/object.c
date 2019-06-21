/*
** EPITECH PROJECT, 2019
** object.c
** File description:
** Take an object or put it on the ground.
*/

#include "client_commands.h"
#include "map.h"
#include "logger.h"

static const struct {
    char *name;
    int len;
} OBJECTS[] = {
    {"linemate", 8},
    {"deraumere", 9},
    {"sibur", 5},
    {"mendiane", 8},
    {"phiras", 6},
    {"thystame", 8},
    {"food", 4}
};

int get_inventory_idx(const char *elem)
{
    for (int i = 0; i < 7; ++i)
        if (strncmp(OBJECTS[i].name, elem, OBJECTS[i].len) == 0)
            return i;
    debugl("Invalid element %s.\n", elem);
    return -1;
}

char *take(ia_t *client, server_t *server, const char *object)
{
    int idx = get_inventory_idx(object + 1);
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    if (idx == -1) {
        return strdup("ko\n");
    } else if (tile->inventory.inv_arr[idx] > 0) {
        tile->inventory.inv_arr[idx] -= 1;
        client->inventory.inv_arr[idx] += 1;
    }
    return strdup("ok\n");
}

char *set(ia_t *client, server_t *server, const char *object)
{
    int idx = get_inventory_idx(object + 1);
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    if (idx == -1) {
        return strdup("ko\n");
    } else if (client->inventory.inv_arr[idx] > 0) {
        client->inventory.inv_arr[idx] -= 1;
        tile->inventory.inv_arr[idx] += 1;
    }
    return strdup("ok\n");
}
