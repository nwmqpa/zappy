/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main file of the zappy server.
*/

#include "dispatcher.h"
#include "handlers.h"
#include "options.h"
#include "zappy.h"
#include "logger.h"
#include "server.h"

#ifndef TEST

int main(int argc, char *argv[])
{
    if (argc == 1) {
        dprintf(2, "zappy_server: Too few arguments.\n");
        return 84;
    }
    srandom(time(NULL));
    options_t *options = create_opt(argc, argv);
    server_t *server = NULL;

    if (check_opt(options) == -1) {
        free(options);
        return 84;
    }
    server = create_server(options);
    free(options);
    if (server)
        return zappy_server(server);
    else
        return 84;
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

#endif /* TEST */
