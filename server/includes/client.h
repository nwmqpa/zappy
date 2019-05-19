/*
** EPITECH PROJECT, 2019
** client.h
** File description:
** client header file.
*/

#pragma once

#include <stdlib.h>
#include "generic_list.h"

/*
** Define directions that can have a player.
*/
enum DIRECTION {
    LEFT    = 0,
    RIGHT   = 1,
    UP      = 2,
    DOWN    = 3
};

/*
** Define a client inventory
** each of it's field is a props gatherable on the map.
*/
typedef struct inventory_s {
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
    unsigned int food;
} inventory_t;

/*
** Define a position in 2 dimensions.
*/
typedef struct pos_s {
    int x;
    int y;
} pos_t;

/*
** Define a client, another program that connect to the server and
** interact with it in a logical way.
**
** The client have a lots of informations:
** -> id: The unique number representing it.
** -> commands: A queue of 10 commands that the server should answer in order.
** -> inventory: A set of objects that the player have.
** -> level: The number of time the player have evolved.
** -> direction: Where the player is facing.
** -> position: [x, y] position defining on which tile the player is positioned.
*/
typedef struct client_s {
    size_t id;
    list_t *commands;
    unsigned int level;
    unsigned int direction;
    pos_t position;
    inventory_t inventory;
} client_t;

client_t *client_create(size_t id);

void add_command(client_t *client, char *command);
int process_command(client_t *client);
size_t len_command(client_t *client);

void print_client(const client_t *client);
void print_client_list(const void *data);

/*
** Client commands.
*/

/*
** Moving command
**  response:   ok
**  time limit: 7/f
*/
char *forward(client_t *client);
char *left(client_t *client);
char *right(client_t *client);

/*
** Look command
**  response:   [player, tile1-content, tile2-content, ...]
**  time limit: 7/f
*/
char *look(client_t *client);

/*
** Inventory command
**  response:   [linemate X, demeraute Y, ..., phiras Z]
**      -> where `X` `Y` `Z` number possesed by the player.
**  time limit: 1/f
*/
char *inventory(client_t *client);

/*
** Broadcast [text] command
**  response:   ok
**  time limit: 7/f
*/
char *broadcast(client_t *client, const char *text);

/*
** Fork command
**  response:   ok
**  time limit: 42/f
*/
char *fork_client();

/*
** Eject command
**  response:   ok/ko
**  time limit: 7/f
*/
char *eject();

/*
** Map interaction command
**  response:   ok/ko
**  time limit: 7/f
*/
char *take(client_t *client);
char *set(client_t *client);

/*
** Incantation command
**  response:   Elevation underway\nCurrent level: X/ko
**      -> where X is the client->level
**  time limit: 300/f
*/
char *incante(client_t *client);
