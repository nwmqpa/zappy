/*
** EPITECH PROJECT, 2019
** srv_events_player.c
** File description:
** Server event player source code.
*/

#include "logger.h"
#include "events.h"
#include "server.h"
#include "protocols.h"

void event_tile_content(int x, int y, server_t *server)
{
    srv_tile_content_t *pld = malloc(sizeof(srv_tile_content_t));
    tile_t *tile = get_tile_map(server->map, x, y);

    pld->x = x;
    pld->y = y;
    pld->q0 = tile->inventory.inv.food;
    pld->q1 = tile->inventory.inv.linemate;
    pld->q2 = tile->inventory.inv.deraumere;
    pld->q3 = tile->inventory.inv.sibur;
    pld->q4 = tile->inventory.inv.mendiane;
    pld->q5 = tile->inventory.inv.phiras;
    pld->q6 = tile->inventory.inv.thystame;
    pld->players = tile->nb_player;
    add_event(server, SRV_TILE_CONTENT, pld);
    debugl("Adding SRV_TILE_CONTENT to event queue.\n");
}
