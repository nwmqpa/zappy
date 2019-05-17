/*
** EPITECH PROJECT, 2019
** zappy.c
** File description:
** zappy source file main loop.
*/

#include "zappy.h"
#include "logger.h"

int zappy_server(server_t *server)
{
    infol("Launching Zappy server.\n");
    print_server(server);
    return 0;
}
