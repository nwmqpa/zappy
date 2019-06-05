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
    server_t *server = calloc(sizeof(server_t), 1);

    server->width = x;
    server->height = y;
    server->client_per_team = 10;
    server->map = create_map(x, y);
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

Test(commands, look_level2_direction) {
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
    client->position.x = 1;
    client->position.y = 1;
    get_tile_map(server->map, 1, 1)->inventory.inv.linemate = 1;
    get_tile_map(server->map, 0, 0)->inventory.inv.deraumere = 2;
    get_tile_map(server->map, 1, 0)->inventory.inv.food = 3;
    get_tile_map(server->map, 2, 0)->inventory.inv.phiras = 4;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[linemate:1,deraumere:2,food:3,phiras:4]");
}

Test(commands, eject_basic) {
    server_t *server = setup_server(10, 10);
    client_t *client0 = client_create(3);
    client0->position = (pos_t){0, 4};
    client_t *client1 = client_create(4);
    client1->position = (pos_t){2, 2};
    client1->direction = RIGHT;
    client_t *client2 = client_create(5);
    client2->position = (pos_t){2, 2};
    client1->direction = TOP;
    client_t *client3 = client_create(6);
    client3->position = (pos_t){2, 2};
    client1->direction = LEFT;

    server->clients = create_list();
    append_list(server->clients, client0);
    append_list(server->clients, client1);
    append_list(server->clients, client2);
    append_list(server->clients, client3);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            tile_t *tile = get_tile_map(server->map, x, y);
            for (int i = 0; i < INVENTORY_SIZE; ++i)
                tile->inventory.inv_arr[i] = 0;
        }
    }
    get_tile_map(server->map, 1, 1)->inventory.inv.linemate = 1;
    get_tile_map(server->map, 0, 0)->inventory.inv.deraumere = 2;
    get_tile_map(server->map, 1, 0)->inventory.inv.food = 3;
    get_tile_map(server->map, 2, 0)->inventory.inv.phiras = 4;
    char *ret = look(client, server);
    cr_assert_str_eq(ret, "[linemate:1,deraumere:2,food:3,phiras:4]");
}
