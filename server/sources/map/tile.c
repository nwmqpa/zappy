/*
** EPITECH PROJECT, 2019
** tile.c
** File description:
** Tile functions.
*/

#include "map.h"

static const unsigned int MAX_RAND_TILE = 20;

void set_tile(tile_t *new)
{
    new->inventory.inv.linemate = rand() % MAX_RAND_TILE;
    new->inventory.inv.deraumere = rand() % MAX_RAND_TILE;
    new->inventory.inv.sibur = rand() % MAX_RAND_TILE;
    new->inventory.inv.mendiane = rand() % MAX_RAND_TILE;
    new->inventory.inv.phiras = rand() % MAX_RAND_TILE;
    new->inventory.inv.thystame = rand() % MAX_RAND_TILE;
    new->inventory.inv.food = rand() % MAX_RAND_TILE;
}

void add_player(tile_t *tile, int id)
{
    int *new = malloc(sizeof(int) * tile->nb_player + 1);

    for (unsigned int i = 0; i < tile->nb_player; ++i)
        new[i] = tile->player_ids[i];
    new[tile->nb_player] = id;
    tile->nb_player += 1;
    free(tile->player_ids);
    tile->player_ids = new;
}

void remove_player(tile_t *tile, int id)
{
    for (unsigned int i = 0; i < tile->nb_player; ++i) {
        if (tile->player_ids[i] == id) {
            tile->player_ids[i] = -1;
            return;
        }
    }
}
