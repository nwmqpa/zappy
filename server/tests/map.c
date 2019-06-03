/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** Map test.
*/

#include <criterion/criterion.h>
#include "map.h"

Test(map, map_basic)
{
    map_t *map = create_map(10, 20);

    cr_assert(map != NULL);
}

Test(map, map_tile)
{
    map_t *map = create_map(1, 20);
    tile_t *tile = get_tile_map(map, 0, 0);

    cr_assert(tile != NULL);
}

Test(map, map_response)
{
    map_t *map = create_map(1, 20);
    tile_t *tile = get_tile_map(map, 0, 0);

    cr_assert(tile != NULL);

    tile->inventory.linemate = 0;
    tile->inventory.deraumere = 0;
    tile->inventory.sibur = 0;
    tile->inventory.mendiane = 0;
    tile->inventory.phiras = 0;
    tile->inventory.thystame = 0;
    tile->inventory.food = 0;

    tile = get_tile_map(map, 0, 0);

    cr_assert(tile->inventory.linemate == 0);
    cr_assert(tile->inventory.phiras == 0);
    cr_assert(tile->inventory.thystame == 0);
    cr_assert(tile->inventory.food == 0);
    cr_assert(tile->inventory.sibur == 0);
}

Test(map, add_player)
{
    map_t *map = create_map(1, 20);
    tile_t *tile = get_tile_map(map, 0, 16);

    add_player(tile, 2);
    add_player(tile, 3);

    cr_assert(tile->player_ids[0] == 2);
    cr_assert(tile->player_ids[1] == 3);
}
