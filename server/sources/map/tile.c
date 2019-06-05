/*
** EPITECH PROJECT, 2019
** tile.c
** File description:
** Tile functions.
*/

#include <string.h>
#include "map.h"

static const unsigned int MAX_RAND_TILE = 20;

static const char *RESOURCES_NAME[] = {
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "food"
};

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
    tile->nb_player++;
    free(tile->player_ids);
    tile->player_ids = new;
}

static void update_meta(size_t *total_len, int *nb_elem, int value)
{
    *total_len += value;
    (*nb_elem)++;
}

char *tile_to_string(const tile_t *tile)
{
    char *res = NULL;
    char *stock[8] = {0};
    int value;
    size_t total_len = 0;
    int nb_elem = 0;

    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        value = tile->inventory.inv_arr[i];
        if (value > 0) {
            asprintf(&stock[i], "%s:%d", RESOURCES_NAME[i], value);
            update_meta(&total_len, &nb_elem, strlen(stock[i]) + 1);
        }
    }
    if (tile->nb_player > 0) {
        asprintf(&stock[7], "player:%d", tile->nb_player);
        update_meta(&total_len, &nb_elem, strlen(stock[7]) + 1);
    }
    res = calloc(sizeof(char), total_len);
    join_str(res, (const char **) stock, ' ', nb_elem);
    return res;
}

void remove_player(tile_t *tile, int id)
{
    for (unsigned int i = 0; i < tile->nb_player; ++i) {
        if (tile->player_ids[i] == id) {
            tile->player_ids[i] = -1;
            tile->nb_player--;
            return;
        }
    }
}
