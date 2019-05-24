/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** Main map file.
*/

#include "map.h"

map_t *create_map(unsigned int width, unsigned int height)
{
    map_t *new = malloc(sizeof(map_t));
    unsigned int total = width * height;

    new->width = width;
    new->height = height;
    new->tiles = calloc(sizeof(tile_t), total);
    for (unsigned int i = 0; i < total; ++i)
         set_tile(&new->tiles[i]);
    return new;
}


inline tile_t *get_tile_map(map_t *map, unsigned int x, unsigned int y)
{
    return &map->tiles[(y * map->width) + x];
}
