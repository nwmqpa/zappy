/*
** EPITECH PROJECT, 2019
** srv_events_misc.c
** File description:
** Event server miscelanous.
*/

#include "logger.h"
#include "protocols.h"
#include "events.h"
#include "egg.h"

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

void event_egg_hatching(server_t *server, egg_t *egg)
{
    srv_player_egg_hatching_t *payload =
        malloc(sizeof(srv_player_egg_hatching_t));

    payload->egg_num = egg->id;
    add_event(server, SRV_EGG_HATCHING, payload);
    debugl("Adding SRV_EGG_HATCHING to event queue.\n");
}
