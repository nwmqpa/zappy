/*
** EPITECH PROJECT, 2019
** srv_events_misc.c
** File description:
** Event server miscelanous.
*/

#include "logger.h"
#include "protocols.h"
#include "events.h"

void event_incantation(ia_t *client, server_t *server, int *players, int nb)
{
    srv_start_incantation_t *pld = malloc(sizeof(srv_start_incantation_t));

    pld->x = client->position.x;
    pld->y = client->position.y;
    pld->level = client->level;
    memcpy(pld->players, players, sizeof(int) * nb);
    add_event(server, SRV_INCANTATION_START, pld);
    debugl("Adding SRV_INCANTATION_START to event queue.\n");
}
