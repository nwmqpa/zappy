/*
** EPITECH PROJECT, 2019
** zappy.c
** File description:
** zappy source file main loop.
*/

#include "zappy.h"
#include "logger.h"
#include "dispatcher.h"
#include "handlers.h"
#include "client_commands.h"

static void handle_cooldown(client_t *client, server_t *server, int elapsed)
{
    char *to_send = NULL;

    client->cooldown = 0;
    if (client->to_exec) {
        to_send = process_command(client, server);
        dprintf(client->id, "%s\n", to_send);
        free(client->to_exec);
        client->to_exec = NULL;
    } else {
        prepare_command(client);
    }
}

// TODO: Handle client death.
static void handle_player_tick(void *data, const void *params)
{
    struct {
        int elapsed;
        server_t *server;
    } const *parameters = params;
    client_t *client = data;
    int elapsed_time = parameters->elapsed;

    client->cooldown -= elapsed_time;
    client->need_to_eat -= elapsed_time;
    if (client->need_to_eat <= 0 && client->inventory.inv.food == 0) {
        client_delete(client);
    } else if (client->need_to_eat <= 0) {
        client->inventory.inv.food -= 1;
        client->need_to_eat = 126;
    }
    if (client->cooldown <= 0)
        handle_cooldown(client, parameters->server, elapsed_time);
}

void tick_system(server_t *server)
{
    struct {
        int elapsed;
        server_t *server;
    } name = { 1, server };

    map(server->clients, handle_player_tick, &name);
}

static int run_dispatch(dispatcher_t *graphic, dispatcher_t *client,
        server_t *server)
{
    void *graphic_data = NULL;

    while (42) {
        if (dispatch(graphic, graphic_data) == -1 ||
                dispatch(client, server) == -1) {
            infol("Closing server after an error.\n");
            return -1;
        }
        tick_system(server);
    }
    return 0;
}

int zappy_server(server_t *server)
{
    dispatcher_t graphic_disp = {
        .on_active = &on_active_graphic,
        .on_delete = &on_delete_graphic,
        .on_connect = &on_connect_graphic,
        .epoll_fd = server->epoll_fd_graphic,
        .main_socket = server->socket_graphic
    };
    dispatcher_t client_disp = {
        .on_active = &on_active_client,
        .on_delete = &on_delete_client,
        .on_connect = &on_connect_client,
        .epoll_fd = server->epoll_fd_client,
        .main_socket = server->socket_client
    };
    infol("Launching `Zappy` runtime server.\n");
    return run_dispatch(&graphic_disp, &client_disp, server);
}
