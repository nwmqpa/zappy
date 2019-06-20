/*
** EPITECH PROJECT, 2019
** connect_nbr.c
** File description:
** Command that give available slots in the team of the player.
*/

#include <sys/queue.h>
#include "egg.h"
#include "client_commands.h"
#include "logger.h"

int count_eggs(team_t *team)
{
    entry_t *entry;
    int nbr = 0;

    LIST_FOREACH(entry, &team->eggs->head, next) {
        if (((egg_t *) entry)->can_eclose)
            nbr++;
    }
    return nbr;
}

int count_unused_slots(team_t *team, int nb_client)
{
    int nbr = nb_client - len_list(team->clients);

    return nbr + count_eggs(team);
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
