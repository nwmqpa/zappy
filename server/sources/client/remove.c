/*
** EPITECH PROJECT, 2019
** remove.c
** File description:
** Remove client.
*/

#include "client.h"
#include "server.h"
#include "events.h"

void kill_player(ia_t *client, server_t *server)
{
    team_t *team = get_ia_team(client, server);
    tile_t *tile = get_tile_map(server->map, client->position.x,
            client->position.y);

    pop_cmp_list(server->clients, client_cmp, (void *) &client->id);
    remove_player(tile, client->id);
    remove_client_from_team(team, client, server);
    client_delete(client);
    event_player_death(client, server);
}
