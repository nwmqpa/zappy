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

static const int INVENTORY_SIZE = 7;

/*
** Define a client inventory
** each of it's field is a props gatherable on the map.
*/
struct inventory_s {
    unsigned int linemate;
    unsigned int deraumere;
    unsigned int sibur;
    unsigned int mendiane;
    unsigned int phiras;
    unsigned int thystame;
    unsigned int food;
};

typedef union inventory_u {
    struct inventory_s inv;
    unsigned int inv_arr[7];
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
** -> cooldown: Time that left to before launching the new incante.
** -> to_send: When cooldown is over this will be send to the player.
*/
typedef struct client_s {
    int id;
    list_t *commands;
    unsigned int level;
    unsigned int direction;
    pos_t position;
    inventory_t inventory;
    int cooldown;
    char *to_send;
} client_t;

client_t *client_create(int id);
void client_delete(client_t *client);

int add_command(client_t *client, char *command);
size_t len_command(client_t *client);

void print_client(const client_t *client);
void print_client_list(const void *data);
void move_client(client_t *client, int x, int y, pos_t size);
