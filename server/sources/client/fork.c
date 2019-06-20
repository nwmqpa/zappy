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
    event_egg_layed(client, server);
    append_list(server->eggs, new);
    return strdup("ok");
}
