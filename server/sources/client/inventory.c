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

    asprintf(&inv, "[ linemate %d, deraumere %d, sibur %d, mendiane %d,"
            " phiras %d, thystame %d, food %d ]",
            client->inventory.inv.linemate,
            client->inventory.inv.deraumere,
            client->inventory.inv.sibur,
            client->inventory.inv.mendiane,
            client->inventory.inv.phiras,
            client->inventory.inv.thystame,
            client->inventory.inv.food);
    return inv;
}
