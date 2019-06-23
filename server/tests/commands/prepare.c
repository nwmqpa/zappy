/*
** EPITECH PROJECT, 2019
** prepare.c
** File description:
** Preparation
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
    return server;
}

Test(command_functions, get_cooldown)
{
    cr_assert_eq(get_cooldown("Steak"), -1);
    cr_assert_eq(get_cooldown("Take"), 7.0);
    cr_assert_eq(get_cooldown("Connect_nbr"), 0.0);
    cr_assert_eq(get_cooldown("Fork"), 42.0);
    cr_assert_eq(get_cooldown(NULL), -1);
}

Test(command_functions, prepare_command)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(1);

    add_command(client, "Fork");
    cr_assert_eq(prepare_command(client, server), 0);
    client->cooldown = 42.0;
    cr_assert_str_eq(client->to_exec, "Fork");
    char *data = get_list(client->commands, 0);
    cr_assert_eq(data, NULL);
}

Test(command_functions, prepare_command_bad)
{
    server_t *server = setup_server(10, 10);
    ia_t *client = client_create(1);

    add_command(client, strdup("Fock"));
    cr_assert_eq(prepare_command(client, server), -1);
    client->cooldown = 0.0;
    cr_assert_eq(client->to_exec, NULL);
    char *data = get_list(client->commands, 0);
    cr_assert_eq(data, NULL);
}
