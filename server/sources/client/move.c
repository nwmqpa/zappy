/*
** EPITECH PROJECT, 2019
** forward.c
** File description:
** Forward command.
*/

#include "client_commands.h"

char *forward(client_t *client, server_t *server)
{
    pos_t size = {
        .x = server->width,
        .y = server->height
    };

    client->cooldown = 7;
    switch (client->direction) {
    case LEFT:
        move_client(client, -1, 0, size);
        break;
    case RIGHT:
        move_client(client, 1, 0, size);
        break;
    case UP:
        move_client(client, 0, 1, size);
        break;
    case DOWN:
        move_client(client, 0, -1, size);
    }
    return "ok";
}

char *left(client_t *client, server_t *server)
{
    pos_t size = {
        .x = server->width,
        .y = server->height
    };

    client->cooldown = 7;
    switch (client->direction) {
    case LEFT:
        move_client(client, 0, -1, size);
        break;
    case RIGHT:
        move_client(client, 0, 1, size);
        break;
    case UP:
        move_client(client, -1, 0, size);
        break;
    case DOWN:
        move_client(client, 1, 0, size);
    }
    return "ok";
}

char *right(client_t *client, server_t *server)
{
    pos_t size = {
        .x = server->width,
        .y = server->height
    };

    client->cooldown = 7;
    switch (client->direction) {
    case LEFT:
        move_client(client, 0, 1, size);
        break;
    case RIGHT:
        move_client(client, 0, -1, size);
        break;
    case UP:
        move_client(client, 1, 0, size);
        break;
    case DOWN:
        move_client(client, -1, 0, size);
    }
    return "ok";
}
