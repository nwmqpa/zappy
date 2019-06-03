/*
** EPITECH PROJECT, 2019
** look.c
** File description:
** Look around command file.
*/

#include "client_commands.h"

char *get_vision_content(server_t *server, unsigned int level,
        unsigned int direction, pos_t position)
{
    // TODO: Implement.
    return "[tile1, tile2, tile3]";
}

char *look(client_t *client, server_t *server)
{
    client->cooldown = 7;
    return get_vision_content(server, client->level, client->direction,
            client->position);
}
