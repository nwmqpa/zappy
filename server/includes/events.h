/*
** EPITECH PROJECT, 2019
** events.h
** File description:
** Graphic event that are handled.
*/

#pragma once

#include "server.h"
#include "generic_list.h"

/// events are for graphic client.
/// It's for things like `new_player` or `player_death`
/// that the graphic client cannot ask for.
typedef struct event_s {
    int id;
    void *payload;
} event_t;

int add_event(server_t *server, int id, void *payload);
void handle_events(server_t *server);

void event_egg_layed(ia_t *client, server_t *server);
void event_new_player(ia_t *client, server_t *server);
void event_player_death(ia_t *client, server_t *server);
void event_player_connected_egg(ia_t *client, server_t *server);
void event_end_game(const char *winning_team, server_t *server);
void event_player_pos(ia_t *client, server_t *server);
void event_incantation_end(ia_t *client, server_t *server, int result);
void event_incantation_start(ia_t *client, server_t *server, int *plr, int nb);
