/*
** EPITECH PROJECT, 2019
** forward.c
** File description:
** Forward command.
*/

#include "client_commands.h"

char *forward(ia_t *client, server_t *server)
{
    pos_t size = {server->width, server->height};

    switch (client->direction) {
    case LEFT:
        move_client(client, server, (pos_t){-1, 0}, size);
        break;
    case RIGHT:
        move_client(client, server, (pos_t){1, 0}, size);
        break;
    case UP:
        move_client(client, server, (pos_t){0, 1}, size);
        break;
    case DOWN:
        move_client(client, server, (pos_t){0, -1}, size);
    }
    return strdup("ok");
}

char *left(ia_t *client, server_t *server)
{
    switch (client->direction) {
    case LEFT:
        client->direction = DOWN;
        break;
    case RIGHT:
        client->direction = UP;
        break;
    case UP:
        client->direction = LEFT;
        break;
    case DOWN:
        client->direction = RIGHT;
    }
    return strdup("ok");
}

char *right(ia_t *client, server_t *server)
{
    switch (client->direction) {
    case LEFT:
        client->direction = UP;
        break;
    case RIGHT:
        client->direction = DOWN;
        break;
    case UP:
        client->direction = RIGHT;
        break;
    case DOWN:
        client->direction = LEFT;
    }
    return strdup("ok");
}
