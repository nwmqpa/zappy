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
    egg_t *new;

    new = egg_create(client->position.x, client->position.y);
    event_egg_layed(client, server);
    append_list(team->eggs, new);
    return strdup("ok");
}
