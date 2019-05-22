/*
** EPITECH PROJECT, 2019
** zappy.c
** File description:
** zappy source file main loop.
*/

#include "zappy.h"
#include "logger.h"

static int on_connect(int socket, void *data)
{

}

static int on_delete(int socket, void *data)
{

}

static int on_delete(int socket, void *data)
{

}

int zappy_server(server_t *server)
{
    infol("Launching `Zappy` runtime server.\n");
    while (42) {
        if (dispatch() == -1) {
            infol("Quitting server after an error.\n");
            return 84;
        }
    }
    return 0;
}
