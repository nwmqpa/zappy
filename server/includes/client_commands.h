/*
** EPITECH PROJECT, 2019
** client_commands.h
** File description:
** Client commands header.
*/

#pragma once

#include "stdio.h"
#include "server.h"
#include "client.h"

typedef char * (*cmd_func) (ia_t *, server_t *);
typedef char * (*cmd_param_func) (ia_t *, server_t *, const char *);

typedef struct command_s {
    char *name;
    cmd_func function;
    int len;
    double cooldown;
} command_t;

typedef struct command_param_s {
    char *name;
    cmd_param_func function;
    int len;
    double cooldown;
} command_param_t;

/// Get cooldown.
double get_cooldown(const char *cmd);

/// Prepare commands like `Fork` and `Incantation`.
int prepare_special_command(ia_t *client, server_t *server);

/// Set the ai cooldown.
int prepare_command(ia_t *client, server_t *server);

/// Process the command.
char *process_command(ia_t *client, server_t *server);

/// Move client with the server.
void move_client(ia_t *client, server_t *server, pos_t new, pos_t size);

/// Remove player from the server.
int kill_player(ia_t *client, server_t *server);

/// Moving command
///  response:   ok
///  time limit: 7/f
char *forward(ia_t *client, server_t *server);
char *left(ia_t *client, server_t *server);
char *right(ia_t *client, server_t *server);

/// Look command
///  response:   [player, tile1-content, tile2-content, ...]
///  time limit: 7/f
char *look(ia_t *client, server_t *server);

/// Inventory command
///  response:   [linemate X, demeraute Y, ..., phiras Z]
///      -> where `X` `Y` `Z` number possesed by the player.
///  time limit: 1/f
char *inventory(ia_t *client, server_t *server);

/// Broadcast [text] command
///  response:   ok
///  time limit: 7/f
char *broadcast(ia_t *client, server_t *server, const char *text);

/// Fork command
///  response:   ok
///  time limit: 42/f
char *fork_client(ia_t *client, server_t *server);

/// Eject command
///  response:   ok/ko
///  time limit: 7/f
char *eject(ia_t *client, server_t *server);

/// Get command
///  response:   ok/ko
///  time limit: 7/f
char *take(ia_t *client, server_t *server, const char *object);

/// Set command
///  response:   ok/ko
///  time limit: 7/f
char *set(ia_t *client, server_t *server, const char *object);

/// Incantation command
///  response:   Elevation underway\nCurrent level: X/ko
///      -> where X is the client->level
///  time limit: 300/f
char *incante(ia_t *client, server_t *server);

/// Connect nbr command.
///  response:   `Value`
///      -> The nbr of available slots in client's team.
///  time limit: 0
char *connect_nbr(ia_t *client, server_t *server);


typedef struct {
    pos_t pos;
    float distance;
} pos_distance_t;

int calculate_tile(server_t *server, pos_t s, pos_t c);
