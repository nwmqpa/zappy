/*
** EPITECH PROJECT, 2019
** map.h
** File description:
** Map header file.
*/

#pragma once

#include "client.h"

/*
** Contain an inventory and player's id of those placed on them.
**
*/
typedef struct tile_s {
    inventory_t inventory;
    int *player_ids;
    unsigned int nb_player;
} tile_t;

void set_tile(tile_t *new);
void add_player(tile_t *tile, int id);
void remove_player(tile_t *tile, int id);

/*
** Contain map dimension.
** and an array of tile.
*/
typedef struct map_s {
    unsigned int width;
    unsigned int height;
    tile_t *tiles;
} map_t;

map_t *create_map(unsigned int width, unsigned int height);
tile_t *get_tile_map(map_t *map, unsigned int x, unsigned int y);
int move_client_map(map_t *map, client_t *client);
char *get_map_reponse(map_t *map);
