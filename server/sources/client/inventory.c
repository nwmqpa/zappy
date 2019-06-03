/*
** EPITECH PROJECT, 2019
** inventory.c
** File description:
** Inventory command file.
*/

#include "client_commands.h"

char *inventory(client_t *client, server_t *server)
{
    char *inv = NULL;

    client->cooldown = 1;
    asprintf(&inv, "[linemate %d, deraumere %d, sibur %d, mendiane %d,"
            " phiras %d, thystame %d, food %d]",
            client->inventory.linemate,
            client->inventory.deraumere,
            client->inventory.sibur,
            client->inventory.mendiane,
            client->inventory.phiras,
            client->inventory.thystame,
            client->inventory.food);
    return inv;
}
