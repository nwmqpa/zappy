/*
** EPITECH PROJECT, 2019
** teams.c
** File description:
** Team source code file.
*/

#include "server.h"
#include "client.h"
#include "logger.h"

static int check_free_space(team_t *team, int max_client, int new_client)
{
    int ret = 0;

    debugl("max_client = %d\n", max_client);
    for (int i = 0; i < max_client; ++i) {
        if (team->clients[i] == 0 && ret == 0) {
            ret++;
            team->clients[i] = new_client;
        } else if (team->clients[i] == 0) {
            ret++;
        }
        debugl("team->clients[%d] = %d\n", i, team->clients[i]);
    }
    return ret;
}

int add_client_to_team(server_t *server, client_t *client, const char *team)
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