/*
** EPITECH PROJECT, 2019
** client_commands.h
** File description:
** Client commands header.
*/

#pragma once

#include "server.h"
#include "client.h"

typedef char * (*cmd_func) (client_t *, server_t *);
typedef char * (*cmd_param_func) (client_t *, server_t *, const char *);

typedef struct command_s {
    char *name;
    cmd_func function;
    int len;
} command_t;

typedef struct command_param_s {
    char *name;
    cmd_param_func function;
    int len;
} command_param_t;

/*
** Moving command
**  response:   ok
**  time limit: 7/f
*/
char *forward(client_t *client, server_t *server);
char *left(client_t *client, server_t *server);
char *right(client_t *client, server_t *server);

/*
** Look command
**  response:   [player, tile1-content, tile2-content, ...]
**  time limit: 7/f
*/
char *look(client_t *client, server_t *server);

/*
** Inventory command
**  response:   [linemate X, demeraute Y, ..., phiras Z]
**      -> where `X` `Y` `Z` number possesed by the player.
**  time limit: 1/f
*/
char *inventory(client_t *client, server_t *server);

/*
** Broadcast [text] command
**  response:   ok
**  time limit: 7/f
*/
char *broadcast(client_t *client, server_t *server, const char *text);

/*
** Fork command
**  response:   ok
**  time limit: 42/f
*/
char *fork_client(client_t *client, server_t *server);

/*
** Eject command
**  response:   ok/ko
**  time limit: 7/f
*/
char *eject(client_t *client, server_t *server);

/*
** Map interaction command
**  response:   ok/ko
**  time limit: 7/f
*/
char *take(client_t *client, server_t *server, const char *object);
char *set(client_t *client, server_t *server, const char *object);

/*
** Incantation command
**  response:   Elevation underway\nCurrent level: X/ko
**      -> where X is the client->level
**  time limit: 300/f
*/
char *incante(client_t *client, server_t *server);
