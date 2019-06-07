/*
** EPITECH PROJECT, 2019
** connect_nbr.c
** File description:
** Command that give available slots in the team of the player.
*/

#include "client_commands.h"
#include "logger.h"


static int is_id_in_team(size_t id, team_t *team, int nb_client)
{
    for (int i = 0; i < nb_client; ++i)
        if (id == team->clients[i])
            return 1;
    return 0;
}

static int count_unused_slots(team_t *team, int nb_client)
{
    int nbr = 0;

    for (int i = 0; i < nb_client; ++i)
        if (team->clients[i] == 0 || team->clients[i] == -1)
            nbr++;
    return nbr;
}

char *connect_nbr(client_t *client, server_t *server)
{
    debugl("Connect nbr command.\n");
    team_t *player_team = NULL;
    char *ret = NULL;

    debugl("Getting client's %d team.\n");
    for (int i = 0; server->teams[i] && player_team == NULL; ++i) {
        if (is_id_in_team(client->id, server->teams[i],
                    server->client_per_team)) {
            player_team = server->teams[i];
            debugl("Team found %s.\n", player_team->name);
        }
    }
    asprintf(&ret, "%d",
            count_unused_slots(player_team, server->client_per_team));
    return ret;
}
