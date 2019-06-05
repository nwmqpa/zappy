/*
** EPITECH PROJECT, 2019
** object.c
** File description:
** Take an object or put it on the ground.
*/

#include "client_commands.h"
#include "map.h"
#include "logger.h"

const char * const OBJECTS[] = {
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "food"
};

int get_inventory_idx(const char *elem)
{
    for (int i = 0; i < 7; ++i)
        if (strcmp(OBJECTS[i], elem) == 0)
            return i;
    debugl("Invalid element %s.\n", elem);
    return -1;
}

char *take(client_t *client, server_t *server, const char *object)
{
    int idx = get_inventory_idx(object);
    tile_t *tile = get_tile_map(server->map, client->position.x,
           client->position.y);

    if (idx == -1) {
        return "ko\n";
    } else if (tile->inventory.inv_arr[idx] > 0) {
        tile->inventory.inv_arr[idx] -= 1;
        client->inventory.inv_arr[idx] += 1;
    }
    return "ok\n";
}

char *set(client_t *client, server_t *server, const char *object)
{
    int idx = get_inventory_idx(object);
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    if (idx == -1) {
        return "ko\n";
    } else if (client->inventory.inv_arr[idx] > 0) {
        client->inventory.inv_arr[idx] -= 1;
        tile->inventory.inv_arr[idx] += 1;
    }
    return "ok\n";
}
