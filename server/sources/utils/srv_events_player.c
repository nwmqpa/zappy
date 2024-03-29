/*
** EPITECH PROJECT, 2019
** srv_events_player.c
** File description:
** Server event player source code.
*/

#include "events.h"
#include "logger.h"

void event_egg_layed(ia_t *client, server_t *server)
{
    srv_player_egg_layed_t *payload = malloc(sizeof(srv_player_egg_layed_t));

    payload->player_num = client->id;
    payload->egg_num = client->id;
    payload->x = client->position.x;
    payload->y = client->position.y;
    add_event(server, SRV_EGG_LAYED, payload);
    debugl("Adding SRV_EGG_LAYING to event queue.\n");
}

void event_new_player(ia_t *client, server_t *server)
{
    srv_new_player_connect_t *pld = malloc(sizeof(srv_new_player_connect_t));
    team_t *team = get_ia_team(client, server);

    pld->x = client->position.x;
    pld->y = client->position.y;
    pld->player_num = client->id;
    pld->level = client->level;
    pld->orientation = client->direction;
    memcpy(pld->team_name, team->name, strlen(team->name));
    add_event(server, SRV_NEW_PLAYER_CONNECT, pld);
    debugl("Adding SRV_NEW_PLAYER_CONNECT_LEN to event queue\n");
}

void event_player_death(ia_t *client, server_t *server)
{
    srv_player_death_t *pld = malloc(sizeof(srv_player_death_t));

    pld->player_num = client->id;
    add_event(server, SRV_PLAYER_DEATH, pld);
    debugl("Adding SRV_PLAYER_DEATH to event queue.\n");
}

void event_player_connected_egg(ia_t *client, server_t *server)
{
    srv_player_egg_connection_t *pld =
        malloc(sizeof(srv_player_egg_connection_t));

    pld->egg_num = client->id;
    add_event(server, SRV_NEW_PLAYER_CONNECT, pld);
    add_event(server, SRV_PLAYER_CONNECT_EGG, pld);
    debugl("Adding SRV_PLAYER_CONNECT_EGG to event queue.\n");
}

void event_player_pos(ia_t *client, server_t *server)
{
    srv_player_pos_t *pld = malloc(sizeof(srv_player_pos_t));

    pld->orientation = client->direction;
    pld->player_num = client->id;
    pld->x = client->position.x;
    pld->y = client->position.y;
    add_event(server, SRV_PLAYER_POSITION, pld);
    debugl("Adding SRV_PLAYER_POS to event queue.\n");
}
