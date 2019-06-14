/*
** EPITECH PROJECT, 2019
** eject.c
** File description:
** Ejection command file.
*/

#include "client_commands.h"
#include "logger.h"

static void eject_client(client_t *client, map_t *map, pos_t pos)
{
    switch (client->direction) {
    case LEFT:
        client->position.x = ((pos.x - 1) < 0) ? ((int) map->width - 1) : (pos.x - 1);
        break;
    case RIGHT:
        client->position.x = (pos.x + 1) % map->width;
        break;
    case UP:
        client->position.y = (pos.y + 1) % map->height;
        break;
    case DOWN:
        client->position.y = ((pos.y - 1) < 0) ? ((int) map->height - 1) : (pos.y - 1);
    }
    debugl("Player: %d moved to %d %d\n", client->direction,
            client->position.x, client->position.y);
    add_player(get_tile_map(map, client->position.x, client->position.y), client->id);
}

char *eject(client_t *client, server_t *server)
{
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    int client_id;
    client_t *client_ptr = NULL;
    unsigned int nb_player = tile->nb_player;

    client->cooldown = 7;
    for (unsigned int i = 0; i < nb_player; i++) {
        client_id = tile->player_ids[i];
        if (client_id == client->id)
            continue;
        remove_player(tile, client_id);
        client_ptr = get_list(server->clients, i);
        for (int i = 0; client_ptr != NULL && client_ptr->id != client_id; ++i)
            client_ptr = get_list(server->clients, i);
        eject_client(client_ptr, server->map, client->position);
    }
    return "ok";
}
