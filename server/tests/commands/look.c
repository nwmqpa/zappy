/*
** EPITECH PROJECT, 2019
** commands.c
** File description:
** Commands unit test.
*/

#include <criterion/criterion.h>
#include "client_commands.h"
#include "client.h"

static server_t *setup_server(int x, int y)
{
    server_t *server = calloc(sizeof(server_t), 1);

    server->width = x;
    server->height = y;
    server->client_per_team = 10;
    server->map = create_map(x, y);
    return server;
}

Test(commands, look_level3_with_only_food) {
    server_t *server = setup_server(4, 4);
    ia_t *client = client_create(3);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
            tile->inventory.inv.food = 1;
        }
    }
    tile_t *tile =  get_tile_map(server->map, 0, 0);
    tile->inventory.inv.linemate = 2;
    client->level = 2;
    client->position.x = 0;
    client->position.y = 0;
    client->direction = LEFT;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[ linemate linemate food , food , food , food , food , food , food , food , food ]");
}

Test(commands, look_level2_with_some_things) {
    server_t *server = setup_server(4, 4);
    ia_t *client = client_create(3);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
        }
    }
    client->level = 1;
    client->direction = 3;
    get_tile_map(server->map, 0, 0)->inventory.inv.linemate = 42;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[ linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate linemate ,,,]");
}

Test(commands, look_level2_direction) {
    server_t *server = setup_server(4, 4);
    ia_t *client = client_create(3);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
        }
    }
    client->level = 1;
    client->direction = 3;
    client->position.x = 1;
    client->position.y = 1;
    get_tile_map(server->map, 1, 1)->inventory.inv.linemate = 1;
    get_tile_map(server->map, 0, 0)->inventory.inv.deraumere = 2;
    get_tile_map(server->map, 1, 0)->inventory.inv.food = 3;
    get_tile_map(server->map, 2, 0)->inventory.inv.phiras = 4;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[ linemate , deraumere deraumere , food food food , phiras phiras phiras phiras ]");
}
