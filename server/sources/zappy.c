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
    }
    return 0;
}

int zappy_server(server_t *server)
{
    dispatcher_t graphic_disp = {
        .actives = {{0}},
        .on_active = &on_active_graphic,
        .on_delete = &on_delete_graphic,
        .on_connect = &on_connect_graphic,
        .listener = server->listener_graphic
    };
    dispatcher_t client_disp = {
        .actives = {{0}},
        .on_active = &on_active_client,
        .on_delete = &on_delete_client,
        .on_connect = &on_connect_client,
        .listener = server->listener_client
    };
    infol("Launching `Zappy` runtime server.\n");
    return run_dispatch(&client_disp, &graphic_disp, server);
}
