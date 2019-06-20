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

char *fork_client(ia_t *client, server_t *server)
{
    team_t *team = get_ia_team(client, server);
    ia_t *tmp = client_create(-2);
    egg_t *new;

    if (add_ia_to_team(server, tmp, team->name) == 0) {
        errorl("Cannot fork no more space in team %s.\n", team->name);
        return strdup("ko");
    }
    new = egg_create(client->position.x, client->position.y);
    event_egg_layed(client, server);
    append_list(server->eggs, new);
    return strdup("ok");
}
