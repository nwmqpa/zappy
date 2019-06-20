/*
** EPITECH PROJECT, 2019
** incantation.c
** File description:
** Incantation command.
*/

#include "incante.h"
#include "events.h"

int prepare_incante(ia_t *client, server_t *server)
{
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    if (!is_incant_possible(client, server, tile)) {
        dprintf(client->id, "ko\n");
        return 0;
    }
    client->cooldown = 300.0;
    for (int i = 0; i < 6; ++i)
        tile->inventory.inv_arr[i] -= DATA_INCANT[client->level + 1].needed[i];
    dprintf(client->id, "Elevation underway\n");
    return 1;
}

char *incante(ia_t *client, server_t *server)
{
    char *output = NULL;
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    infol("Beginning incantation of level %d.\n", client->level + 1);
    do_incante(tile, server, client->level + 1, client);
    event_incantation_end(client, server, 1);
    asprintf(&output, "Current level: %d", client->level);
    return output;
}
