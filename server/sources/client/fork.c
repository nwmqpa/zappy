/*
** EPITECH PROJECT, 2019
** fork.c
** File description:
** Fork command file.
*/

#include "client_commands.h"
#include "logger.h"
#include "egg.h"
#include "events.h"

static void add_to_queue(client_t *client, server_t *server)
{
    srv_player_egg_layed_t *payload = malloc(sizeof(srv_player_egg_layed_t));

    payload->player_num = client->id;
    payload->egg_num = time(NULL);
    payload->x = client->position.x;
    payload->y = client->position.y;
    add_event(server, SRV_EGG_LAYING, payload);
    debugl("Adding SRV_EGG_LAYING to event queue.");
}

char *fork_client(client_t *client, server_t *server)
{
    team_t *team = get_client_team(client, server);
    client_t *tmp = client_create(-2);
    egg_t *new;

    if (add_client_to_team(server, tmp, team->name) == 0) {
        errorl("Cannot fork no more space in team %s.\n", team->name);
        return strdup("ko");
    }
    new = egg_create(client->position.x, client->position.y);
    add_to_queue(client, server);
    append_list(server->eggs, new);
    return strdup("ok");
}
