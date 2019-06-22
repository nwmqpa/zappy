/*
** EPITECH PROJECT, 2019
** egg.h
** File description:
** Egg header file.
*/

#pragma once

#include "client.h"
#include "server.h"

/// Represent an egg inside the game.
/// time_left -> Time before eclosion.
/// id -> internal id.
/// pos_t -> postion in the map.
typedef struct egg_s {
    double time_left;
    pos_t position;
    int can_eclose;
} egg_t;

/// Create an egg.
egg_t *egg_create(int x, int y);

/// Create egg eclosion. And return the client_id to connect with.
ia_t *egg_eclose(egg_t *egg, int fd);

/// Handle time for egg to eclose.
void eclosion_handler(void *elem, const void *data);

/// Print egg.
void get_info_egg(void *player, const void *nothing);

/// Return -1 if their is not egg eclosable or
/// if their is no team slot for eggs.
int check_for_eggs(team_t *team, server_t *server);

/// Check if the egg can hatch.
int is_eclosable(const void *elem, const void *data);

/// Count the number of eggs in a team.
int count_eggs(team_t *team);
