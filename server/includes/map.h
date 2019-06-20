/*
** EPITECH PROJECT, 2019
** map.h
** File description:
** Map header file.
*/

#pragma once

#include "client.h"
#include "utils.h"

#define TIME_RESPAWN 100

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
    double time_respawn;
} map_t;

char *tile_to_string(const tile_t *tile);
map_t *create_map(unsigned int width, unsigned int height);
tile_t *get_tile_map(map_t *map, int x, int y);
int move_client_map(map_t *map, ia_t *client);
char *get_reponse_string(map_t *map);
tile_t *get_random_tile(map_t *map, unsigned int max_x, unsigned max_y);
void respawn_ressources(map_t *map);
