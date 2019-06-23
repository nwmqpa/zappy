/*
** EPITECH PROJECT, 2019
** client_api.c
** File description:
** client API
*/

#include <criterion/criterion.h>
#include "client_commands.h"

static server_t *setup_server(int x, int y)
{
    server_t *server = calloc(sizeof(server_t), 1);

    server->width = x;
    server->height = y;
    server->client_per_team = 10;
    server->map = create_map(x, y);
    server->events = create_list();
    return server;
}

Test(client_api, move_client)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(4);
    client->position = (pos_t){0, 0};
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    add_player(tile, client->id);

    move_client(client, server, (pos_t){5, 5}, (pos_t){ 10, 10});
    cr_assert_eq(client->position.x, 5, "It's %d.", client->position.x);
    cr_assert_eq(client->position.y, 5);
}

Test(client_api, move_client_2)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(4);
    client->position = (pos_t){9, 9};
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    add_player(tile, client->id);

    move_client(client, server, (pos_t){5, 0}, (pos_t){ 10, 10});
    cr_assert_eq(client->position.x, 4, "It's %d.", client->position.x);
    cr_assert_eq(client->position.y, 9, "It's %d.", client->position.y);
}

Test(client_api, move_client_3)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(4);
    client->position = (pos_t){0, 0};
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    add_player(tile, client->id);

    move_client(client, server, (pos_t){-1, 0}, (pos_t){ 10, 10});
    cr_assert_eq(client->position.x, 9, "It's %d.", client->position.x);
    cr_assert_eq(client->position.y, 0, "It's %d.", client->position.y);
}

Test(client_api, move_client_4)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(4);
    client->position = (pos_t){0, 0};
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);
    add_player(tile, client->id);

    move_client(NULL, server, (pos_t){-1, 123}, (pos_t){ 10, 10});
    cr_assert_eq(client->position.x, 0, "It's %d.", client->position.x);
    cr_assert_eq(client->position.y, 0, "It's %d.", client->position.y);
}
