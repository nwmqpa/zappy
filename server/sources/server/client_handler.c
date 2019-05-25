/*
** EPITECH PROJECT, 2019
** client_handler.c
** File description:
** Client handler function callback.
*/

#include "logger.h"

int on_connect_client(int socket, void *data)
{
    debugl("Client connect handler.\n");
    return 0;
}

int on_delete_client(int socket, void *data)
{
    debugl("Client delete handler.\n");
    return 0;
}

int on_active_client(int socket, void *data)
{
    debugl("Client active handler.\n");
    return 0;
}
