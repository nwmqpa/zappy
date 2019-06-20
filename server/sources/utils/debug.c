/*
** EPITECH PROJECT, 2019
** debug.c
** File description:
** Debug functions.
*/

#include "server.h"
#include "egg.h"

void get_info_player(void *player, const void *nothing)
{
    ia_t *client = player;

    print_client(client);
}

void get_players_status(server_t *server)
{
    map(server->clients, get_info_player, NULL);
    map(server->eggs, get_info_egg, NULL);
}

void get_map_status(server_t *server)
{
    tile_t *tile = NULL;

    for (int y = server->height; y >= 0; --y) {
        printf("%2d | ", y);
        for (unsigned int x = 0; x < server->width; ++x) {
            tile = get_tile_map(server->map, x, y);
            printf("[%d]", tile->nb_player);
        }
        putchar('\n');
    }
    putchar('\n');
}

void get_teams_status(server_t *server)
{
    int nb_client = 0;
    int value_c = 0;

    for (int i = 0; server->teams[i]; ++i) {
        for (int y = 0; y < server->client_per_team; ++y) {
            value_c = server->teams[i]->clients[y];
            nb_client = (value_c != 0 && value_c != -2 && value_c != -1)
                ? nb_client + 1 : nb_client;
        }
        printf("There is %d clients in team: %s.\n", nb_client,
                server->teams[i]->name);
        nb_client = 0;
    }
}
