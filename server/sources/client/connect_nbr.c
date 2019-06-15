/*
** EPITECH PROJECT, 2019
** connect_nbr.c
** File description:
** Command that give available slots in the team of the player.
*/

#include "client_commands.h"
#include "logger.h"

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
    char *ret = NULL;
    team_t *player_team = get_client_team(client, server);

    asprintf(&ret, "%d",
            count_unused_slots(player_team, server->client_per_team));
    return ret;
}
