/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** Main map file.
*/

#include "events.h"
#include "config.h"
#include "server.h"
#include "logger.h"

map_t *create_map(unsigned int width, unsigned int height)
{
    map_t *new = malloc(sizeof(map_t));
    unsigned int total = width * height;

    new->width = width;
    new->height = height;
    new->tiles = calloc(sizeof(tile_t), total);
    new->time_respawn =  TIME_RESPAWN;
    for (unsigned int i = 0; i < total; ++i)
        set_tile(&new->tiles[i]);
    return new;
}

static void randomise_tile(tile_t *tile)
{
    tile->inventory.inv.linemate = rand() % LINEMATE_SPAWN_RATE;
    tile->inventory.inv.deraumere = rand() % DERAUMERE_SPAWN_RATE;
    tile->inventory.inv.sibur = rand() % SIBUR_SPAWN_RATE;
    tile->inventory.inv.mendiane = rand() % MENDIANE_SPAWN_RATE;
    tile->inventory.inv.phiras = rand() % PHIRAS_SPAWN_RATE;
    tile->inventory.inv.thystame = rand() % THYSTAME_SPAWN_RATE;
    tile->inventory.inv.food = rand() % FOOD_SPAWN_RATE;
}

void respawn_ressources(map_t *map, server_t *server)
{
    tile_t *tmp = NULL;

    for (unsigned int x = 0; x < map->width; ++x) {
        for (unsigned int y = 0; y < map->height; ++y) {
            tmp = get_tile_map(map, x, y);
            randomise_tile(tmp);
            event_tile_content(x, y, server);
        }
    }
}

tile_t *get_tile_map(map_t *map, int x, int y)
{
    if (x < 0)
        x = map->width + x;
    if (y < 0)
        y = map->height + y;
    pos_t xy = {
        x % map->width,
        y % map->height
    };
    return &map->tiles[(xy.y * map->width) + xy.x];
}

tile_t *get_random_tile(map_t *map, unsigned int max_x, unsigned max_y)
{
    unsigned int x = rand() % max_x;
    unsigned int y = rand() % max_y;

    debugl("Getting tile randomly to %d %d.\n", x, y);
    return get_tile_map(map, x, y);
}
