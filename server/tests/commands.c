/*
** EPITECH PROJECT, 2019
** commands.c
** File description:
** Commands unit test.
*/

#include <criterion/criterion.h>
#include "client_commands.h"

server_t *setup_server(int x, int y)
{
    char *test[] = {"name1", "name2", "name4", "name5", NULL};

    server_t *server = create_server(&(options_t){
            .port = 1234,
            .width = x,
            .height = y,
            .name = test,
            .client_nb = 10,
            .freq = 100
    });

    return server;
}

Test(commands, look_level3_with_only_food) {
    server_t *server = setup_server(4, 4);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
            tile->inventory.inv.food = 1;
        }
    }
    get_tile_map(server->map, 0, 0)->inventory.inv.linemate = 120;
    client_t *client = client_create(3);
    client->level = 3;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[linemate:120 food:1,food:1,food:1,food:1,food:1,food:1,food:1,food:1,food:1]");
}

Test(commands, look_level2_with_some_things) {
    server_t *server = setup_server(4, 4);
    client_t *client = client_create(3);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
        }
    }
    client->level = 2;
    client->direction = 3;
    get_tile_map(server->map, 0, 0)->inventory.inv.linemate = 42;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[linemate:42,,,]");
}
