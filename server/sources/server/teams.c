/*
** EPITECH PROJECT, 2019
** teams.c
** File description:
** Team source code file.
*/

#include "server.h"
#include "client.h"
#include "logger.h"
#include "egg.h"
#include "events.h"

int egg_cmp(const void *entry, const void *other)
{
    const egg_t *egg = entry;
    const egg_t *new = other;

    return (egg->position.x == new->position.x &&
            egg->position.y == new->position.y &&
            egg->can_eclose == new->can_eclose);
}

int add_ia_to_team_bis(server_t *server, ia_t *client, team_t *team)
{
    pos_t pos = { rand() % (server->width - 1), rand() % (server->height - 1) };
    egg_t *egg = get_cmp_list(team->eggs, is_eclosable, NULL);

    if (!count_unused_slots(team, server->client_per_team))
        return (-1);
    if (len_list(team->clients) < (size_t) server->client_per_team) {
        debugl("Use standard slot.\n");
        client->position = pos;
        insert_head_list(team->clients, (void *) client);
        event_new_player(client, server);
        return (count_unused_slots(team, server->client_per_team) + 1);
    } else if (egg) {
        debugl("Use egg slot.\n");
        pop_cmp_list(team->eggs, egg_cmp, egg);
        client->position = egg->position;
        insert_head_list(team->clients, (void *) client);
        free(egg);
        event_player_connected_egg(client, server);
        return (count_eggs(team) + 1);
    }
    return (-1);
}

int add_ia_to_team(server_t *server, ia_t *client, const char *team)
{
    char *back = strchr(team, '\n');
    team_t *found_team = 0x0;

    if (back)
        *back = 0;
    for (int i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, team) == 0) {
            found_team = server->teams[i];
            debugl("Team %s found!\n", team);
            break;
        }
    }
    if (found_team) {
        return add_ia_to_team_bis(server, client, found_team);
    }
    infol("Not such team %s.\n", team);
    return -1;
}

void remove_client_from_team(team_t *team, ia_t *client, server_t *server)
{
    pop_cmp_list(team->clients, client_cmp, (void *) &client->id);
}

team_t *get_ia_team(ia_t *client, server_t *server)
{
    debugl("Getting client's %d team.\n");
    for (int i = 0; server->teams[i]; ++i) {
        if (get_cmp_list(server->teams[i]->clients, client_cmp, &client->id))
            return server->teams[i];
    }
    errorl("Player has no team.\n");
    return NULL;
}
