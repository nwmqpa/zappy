/*
** EPITECH PROJECT, 2019
** incantation_2.c
** File description:
** Incante
*/

#include "incante.h"

void do_incante(tile_t *tile, server_t *server, int level, ia_t *client)
{
    int need_to_up = DATA_INCANT[level].nb_player - 1;

    client->level += 1;
    if (level == 2)
        return;
    for (unsigned int i = 0; i < tile->nb_player && need_to_up > 0; ++i) {
        int id = tile->player_ids[i];
        ia_t *client = get_cmp_list(server->clients, client_cmp, &id);
        if (client != NULL) {
            client->level += 1;
            need_to_up--;
        }
    }
}

static int are_players_ok(server_t *server, tile_t *tile, unsigned int level)
{
    int nb_player_level = tile->nb_player;

    for (unsigned int i = 0; i < tile->nb_player; ++i) {
        int id = tile->player_ids[i];
        ia_t *client = get_cmp_list(server->clients, client_cmp, &id);
        if (client->level != level)
            nb_player_level--;
    }
    if (DATA_INCANT[level].nb_player < nb_player_level) {
        infol("Not enough player on tile to incante.\n");
        return 0;
    }
    return 1;
}

static int are_stuff_ok(tile_t *tile, int level)
{
    for (int i = 0; i < 6; ++i) {
        if (tile->inventory.inv_arr[i] < DATA_INCANT[level].needed[i]) {
            infol("Not enough stuff on tile to incant.\n");
            return 0;
        }
    }
    return 1;
}

int is_incant_possible(ia_t *client, server_t *server, tile_t *tile)
{
    if (!are_players_ok(server, tile, client->level))
        return 0;
    if (!are_stuff_ok(tile, client->level + 1))
        return 0;
    return 1;
}
