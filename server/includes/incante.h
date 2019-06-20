/*
** EPITECH PROJECT, 2019
** incante.h
** File description:
** Header incante.
*/

#include "logger.h"
#include "client_commands.h"

static const struct {
    unsigned int level;
    int nb_player;
    unsigned int needed[7];
} DATA_INCANT[10] = {
    {
        0,
        0,
        { 0, 0, 0, 0, 0, 0 }
    },
    {
        2,
        1,
        { 1, 0, 0, 0, 0, 0 },
    },
    {
        3,
        2,
        { 1, 1, 1, 0, 0, 0 }
    },
    {
        4,
        2,
        { 2, 0, 1, 0, 2, 0 }
    },
    {
        5,
        4,
        { 1, 1, 2, 0, 1, 0 }
    },
    {
        6,
        4,
        { 1, 2, 1, 3, 0, 0 }
    },
    {
        7,
        6,
        { 1, 2, 3, 0, 1, 0 }
    },
    {
        8,
        6,
        { 2, 2, 2, 2, 2, 1 }
    }
};

void do_incante(tile_t *tile, server_t *server, int level, ia_t *client);
int is_incant_possible(ia_t *client, server_t *server, tile_t *tile);
int prepare_incante(ia_t *client, server_t *server);
char *incante(ia_t *client, server_t *server);
