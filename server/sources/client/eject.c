/*
** EPITECH PROJECT, 2019
** eject.c
** File description:
** Ejection command file.
*/

#include "client_commands.h"

static void eject_client(client_t *client, map_t *map, pos_t pos)
{
    switch (client->direction) {
    case LEFT:
        client->position.x = client->position.x - 1;
        if (client->position.x < 0)
            client->position.x = map->width - 1;
        break;
    case RIGHT:
        client->position.x = (client->position.x + 1) % map->width;
        break;
    case UP:
        client->position.y = (client->position.y + 1) % map->height;
        break;
    case DOWN:
        client->position.y = (client->position.y - 1);
        if (client->position.y < 0)
            client->position.y = map->height - 1;
    }
    add_player(get_tile_map(map, client->position.x, client->position.y), client->id);
}

// Take all player on the same tile and eject them in their direction.
char *eject(client_t *client, server_t *server)
{
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    int client_id;
    client_t *client_ptr;

    client->cooldown = 7;
    for (unsigned int i = 0; i < tile->nb_player; i++) {
        client_id = tile->player_ids[i];
        remove_player(tile, client_id);
        for (int i = 0; client && client->id != (size_t) client_id; ++i)
            client_ptr = get_list(server->clients, i);
        eject_client(client_ptr, server->map, client->position);
    }
    return "ok";
}
