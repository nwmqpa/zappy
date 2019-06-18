/*
** EPITECH PROJECT, 2019
** tile.c
** File description:
** Tile functions.
*/

#include <string.h>
#include "map.h"
#include "logger.h"

static const unsigned int MAX_RAND_TILE = 3;

static const char *RESOURCES_NAME[] = {
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    "food",
    NULL
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
    int *new = malloc(sizeof(int) * (tile->nb_player + 1));

    debugl("Adding client %d there is %d players.\n", id, tile->nb_player);
    for (unsigned int i = 0; i < tile->nb_player; ++i)
        new[i] = tile->player_ids[i];
    new[tile->nb_player] = id;
    tile->nb_player++;
    free(tile->player_ids);
    tile->player_ids = new;
}

static void insert_inventory(char **res, const inventory_t *inv)
{
    char *tmp = NULL;

    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        if (inv->inv_arr[i] == 0)
            continue;
        for (unsigned int y = 0; y < inv->inv_arr[i]; ++y) {
            asprintf(&tmp, "%s%s ", *res ? *res : " ", RESOURCES_NAME[i]);
            free(*res);
            *res = tmp;
            tmp = NULL;
        }
    }
}

char *tile_to_string(const tile_t *tile)
{
    char *res = NULL;
    char *tmp = NULL;

    for (unsigned int i = 0; i < tile->nb_player; ++i) {
        if (tile->player_ids[i] != 0 && tile->player_ids[i] != -1 &&
                tile->player_ids[i] != -2) {
            tmp = res;
            asprintf(&res, "%s%s", tmp ? tmp : " ", "player ");
            free(tmp);
            tmp = NULL;
        }
    }
    insert_inventory(&res, &tile->inventory);
    return res ? res : "";
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
