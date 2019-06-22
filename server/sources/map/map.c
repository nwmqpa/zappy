/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** Main map file.
*/

#include "map.h"
#include "logger.h"

static const unsigned int MAX_RAND_FILL = 2;

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
    tile->inventory.inv.linemate += rand() % MAX_RAND_FILL;
    tile->inventory.inv.deraumere += rand() % MAX_RAND_FILL;
    tile->inventory.inv.sibur += rand() % MAX_RAND_FILL;
    tile->inventory.inv.mendiane += rand() % MAX_RAND_FILL;
    tile->inventory.inv.phiras += rand() % MAX_RAND_FILL;
    tile->inventory.inv.thystame += rand() % MAX_RAND_FILL;
    tile->inventory.inv.food += rand() % MAX_RAND_FILL;
}

void respawn_ressources(map_t *map)
{
    tile_t *tmp = NULL;

    for (unsigned int x = 0; x < map->width; ++x) {
        for (unsigned int y = 0; y < map->height; ++y) {
            tmp = get_tile_map(map, x, y);
            randomise_tile(tmp);
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
