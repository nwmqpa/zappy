/*
** EPITECH PROJECT, 2019
** client.h
** File description:
** client header file.
*/

#pragma once

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
    command_queue_t *commands;
    unsigned int level;
    unsigned int direction;
    pos_t position;
    inventory_t inventory;
} client_t;

#endif /* CLIENT_H_ */
