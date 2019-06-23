/*
** EPITECH PROJECT, 2019
** srv_events_misc.c
** File description:
** Event server miscelanous.
*/

#include "logger.h"
#include "protocols.h"
#include "events.h"

void event_incantation_start(ia_t *client, server_t *server, int *plr, int nb)
{
    srv_start_incantation_t *pld = malloc(sizeof(srv_start_incantation_t));

    pld->x = client->position.x;
    pld->y = client->position.y;
    pld->level = client->level;
    memcpy(pld->players, plr, sizeof(int) * nb);
    add_event(server, SRV_INCANTATION_START, pld);
    debugl("Adding SRV_INCANTATION_START to event queue.\n");
}

void event_incantation_end(ia_t *client, server_t *server, int result)
{
    srv_end_incantation_t *pld = malloc(sizeof(srv_end_incantation_t));

    pld->x = client->position.x;
    pld->y = client->position.y;
    pld->result = result;
    add_event(server, SRV_INCANTATION_END, pld);
    debugl("Adding SRV_INCANTATION_END to event queue.\n");
}

void event_end_game(const char *winning_team, server_t *server)
{
    srv_end_game_t *pld = malloc(sizeof(srv_end_game_t));

    memcpy(pld->winning_team, winning_team, strlen(winning_team));
    add_event(server, SRV_END_GAME, pld);
    debugl("Adding SRV_END_GAME to event queue.\n");
}
