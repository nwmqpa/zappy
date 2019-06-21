/*
** EPITECH PROJECT, 2019
** special_function.c
** File description:
** Special functions
*/

#include "incante.h"
#include "events.h"

int prepare_special_command(ia_t *client, server_t *server)
{
    if (strncmp(client->to_exec, "Incantation", 11) == 0) {
        if (prepare_incante(client, server) == 0) {
            free(client->to_exec);
            client->to_exec = NULL;
        } else {
            tile_t *tile = get_tile_map(server->map, client->position.x,
                    client->position.y);
            event_incantation_start(client, server, tile->player_ids,
                    tile->nb_player);
        }
        return 1;
    }
    return 0;
}
