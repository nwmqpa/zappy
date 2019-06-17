/*
** EPITECH PROJECT, 2019
** graphic_handler.c
** File description:
** Graphic function dispatched.
*/

#include "logger.h"
#include "protocols_graphic.h"

int on_connect_graphic(int socket, void *data)
{
    debugl("New graphic client connected.\n");
    return 0;
}

int on_delete_graphic(int socket, void *data)
{
    debugl("A graphic client just disconnect.\n");
    return 0;
}

int on_active_graphic(int socket, void *data)
{
    server_t *server = (server_t *) data;

    debugl("Graphic client sent a message.\n");
    handle_packet(socket, server);
    return 0;
}
