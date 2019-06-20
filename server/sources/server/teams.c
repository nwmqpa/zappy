/*
** EPITECH PROJECT, 2019
** teams.c
** File description:
** Team source code file.
*/

#include "server.h"
#include "client.h"
#include "logger.h"

int check_free_space(team_t *team, int max_client, int new_client)
{
    int ret = 0;
    int not_added = 1;

    for (int i = 0; i < max_client; ++i) {
        if (team->clients[i] == 0 && not_added) {
            team->clients[i] = new_client;
            not_added = 0;
            ret++;
        } else if (team->clients[i] == 0 ) {
            ret++;
        }
        debugl("team->clients[%d] = %d\n", i, team->clients[i]);
    }
    return ret;
}

int add_ia_to_team(server_t *server, ia_t *client, const char *team)
{
    char *back = strchr(team, '\n');

    if (back)
        *back = 0;
    for (int i = 0; server->teams[i]; i++) {
        if (strcmp(server->teams[i]->name, team) == 0) {
            debugl("Team %s found!\n", team);
            return check_free_space(server->teams[i], server->client_per_team,
                    client->id);
        }
    }
    infol("Not such team %s.\n", team);
    return -1;
}

void remove_client_from_team(team_t *team, ia_t *client, server_t *server)
{
    for (int i = 0; server->client_per_team; ++i) {
        if (client->id == team->clients[i]) {
            team->clients[i] = -1;
            return;
        }
    }
}

static int is_id_in_team(int id, team_t *team, int nb_client)
{
    for (int i = 0; i < nb_client; ++i)
        if (id == team->clients[i])
            return 1;
    return 0;
}

team_t *get_ia_team(ia_t *client, server_t *server)
{
    debugl("Getting client's %d team.\n");
    for (int i = 0; server->teams[i]; ++i) {
        if (is_id_in_team(client->id, server->teams[i],
                    server->client_per_team)) {
            return server->teams[i];
        }
    }
    errorl("Player has no team.\n");
    return NULL;
}
